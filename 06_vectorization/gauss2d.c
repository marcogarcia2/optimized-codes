#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <xmmintrin.h>     // SSE

#ifndef N
#define N (1 << 12)         // 4096 x 4096 imagem
#endif

#ifndef REPEAT
#define REPEAT 100
#endif

// Kernel Gaussiano 3x3 (normalizado)
static const float K00 = 0.0625f, K01 = 0.125f, K02 = 0.0625f;
static const float K10 = 0.125f, K11 = 0.250f, K12 = 0.125f;
static const float K20 = 0.0625f, K21 = 0.125f, K22 = 0.0625f;

static double now_sec(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

// ---------------------------------------------------------
// Versão escalar
// ---------------------------------------------------------
void gaussian2d_scalar(const float *in, float *out, int n) {
    int H = n, W = n;

    // bordas copiadas
    for (int i = 0; i < H; i++) {
        out[i*W + 0]   = in[i*W + 0];
        out[i*W + W-1] = in[i*W + W-1];
    }
    for (int j = 0; j < W; j++) {
        out[0*W + j]   = in[0*W + j];
        out[(H-1)*W+j] = in[(H-1)*W + j];
    }

    for (int i = 1; i < H-1; i++) {
        for (int j = 1; j < W-1; j++) {

            float p =
                K00 * in[(i-1)*W + (j-1)] +
                K01 * in[(i-1)*W +  j   ] +
                K02 * in[(i-1)*W + (j+1)] +

                K10 * in[ i   *W + (j-1)] +
                K11 * in[ i   *W +  j   ] +
                K12 * in[ i   *W + (j+1)] +

                K20 * in[(i+1)*W + (j-1)] +
                K21 * in[(i+1)*W +  j   ] +
                K22 * in[(i+1)*W + (j+1)];

            out[i*W + j] = p;
        }
    }
}

// ---------------------------------------------------------
// Versão vetorizada SSE (processa 4 pixels por vez na linha)
// ---------------------------------------------------------
void gaussian2d_sse(const float *in, float *out, int n) {

    int H = n, W = n;

    // cópia das bordas
    for (int i = 0; i < H; i++) {
        out[i*W + 0]   = in[i*W + 0];
        out[i*W + W-1] = in[i*W + W-1];
    }
    for (int j = 0; j < W; j++) {
        out[0*W + j]   = in[0*W + j];
        out[(H-1)*W+j] = in[(H-1)*W + j];
    }

    __m128 k00 = _mm_set1_ps(K00), k01 = _mm_set1_ps(K01), k02 = _mm_set1_ps(K02);
    __m128 k10 = _mm_set1_ps(K10), k11 = _mm_set1_ps(K11), k12 = _mm_set1_ps(K12);
    __m128 k20 = _mm_set1_ps(K20), k21 = _mm_set1_ps(K21), k22 = _mm_set1_ps(K22);

    for (int i = 1; i < H-1; i++) {
        int j = 1;

        for (; j + 3 < W-1; j += 4) {
            const float *row0 = &in[(i-1)*W + j];
            const float *row1 = &in[(i  )*W + j];
            const float *row2 = &in[(i+1)*W + j];

            __m128 r0m1 = _mm_loadu_ps(row0 - 1);
            __m128 r0c  = _mm_loadu_ps(row0);
            __m128 r0p1 = _mm_loadu_ps(row0 + 1);

            __m128 r1m1 = _mm_loadu_ps(row1 - 1);
            __m128 r1c  = _mm_loadu_ps(row1);
            __m128 r1p1 = _mm_loadu_ps(row1 + 1);

            __m128 r2m1 = _mm_loadu_ps(row2 - 1);
            __m128 r2c  = _mm_loadu_ps(row2);
            __m128 r2p1 = _mm_loadu_ps(row2 + 1);

            __m128 acc =
                _mm_add_ps(
                    _mm_add_ps(
                        _mm_add_ps(_mm_mul_ps(r0m1, k00), _mm_mul_ps(r0c, k01)),
                        _mm_mul_ps(r0p1, k02)),
                    _mm_add_ps(
                        _mm_add_ps(_mm_mul_ps(r1m1, k10), _mm_mul_ps(r1c, k11)),
                        _mm_mul_ps(r1p1, k12))
                );

            acc = _mm_add_ps(
                    acc,
                    _mm_add_ps(
                        _mm_add_ps(_mm_mul_ps(r2m1, k20), _mm_mul_ps(r2c, k21)),
                        _mm_mul_ps(r2p1, k22))
                );

            _mm_storeu_ps(&out[i*W + j], acc);
        }

        // resto escalar
        for (; j < W-1; j++) {
            out[i*W + j] =
                K00 * in[(i-1)*W + (j-1)] +
                K01 * in[(i-1)*W +  j   ] +
                K02 * in[(i-1)*W + (j+1)] +

                K10 * in[ i   *W + (j-1)] +
                K11 * in[ i   *W +  j   ] +
                K12 * in[ i   *W + (j+1)] +

                K20 * in[(i+1)*W + (j-1)] +
                K21 * in[(i+1)*W +  j   ] +
                K22 * in[(i+1)*W + (j+1)];
        }
    }
}

// inicialização
void init_random(float *v, int n) {
    for (int i = 0; i < n*n; i++)
        v[i] = (float)rand() / (float)RAND_MAX;
}

float max_abs_diff(const float *a, const float *b, int n) {
    float maxd = 0.0f;
    for (int i = 0; i < n*n; i++) {
        float d = fabsf(a[i] - b[i]);
        if (d > maxd) maxd = d;
    }
    return maxd;
}

int main(void) {
    printf("Imagem %dx%d\n", N, N);
    printf("Repetições = %d\n", REPEAT);

    float *img  = malloc(N*N*sizeof(float));
    float *outS = malloc(N*N*sizeof(float));
    float *outV = malloc(N*N*sizeof(float));

    // Aleatoriza a imagem
    init_random(img, N);

    // Warmup
    gaussian2d_scalar(img, outS, N);
    gaussian2d_sse(img, outV, N);

    // Benchmark: versão escalar
    double t0 = now_sec();
    for (int r=0; r<REPEAT; r++) gaussian2d_scalar(img, outS, N);
    double t1 = now_sec();
    
    // Benchmark: versão vetorizada
    double t2 = now_sec();
    for (int r=0; r<REPEAT; r++) gaussian2d_sse(img, outV, N);
    double t3 = now_sec();

    // Resultados
    printf("\nEscalar:   %.6f s (%.6f por it.)\n", t1 - t0, (t1-t0)/REPEAT);
    printf("SSE:       %.6f s (%.6f por it.)\n", t3 - t2, (t3-t2)/REPEAT);

    printf("Speedup = %.2fx\n", (t1-t0)/(t3-t2));

    printf("Erro máximo: %.6e\n", max_abs_diff(outS, outV, N));

    free(img); free(outS); free(outV);
    return 0;
}
