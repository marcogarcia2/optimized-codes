#include <stdio.h>
#include <stdlib.h>

#define N 512
#define TILE N/16

// Usado somente para debug
void checksum(int **C){
    long long sum = 0;
    for (int i = 0; i < N; i++)
        sum += C[i][i];
    
    printf("CHECKSUM: %d\n", sum);
}

void static_naive(int A[N][N], int B[N][N], int C[N][N]){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            for (int k = 0; k < N; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void static_interchange(int A[N][N], int B[N][N], int C[N][N]){
    for (int i = 0; i < N; i++){
        for (int k = 0; k < N; k++){
            for (int j = 0; j < N; j++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void static_unrolling(int A[N][N], int B[N][N], int C[N][N]){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            for (int k = 0; k < N; k += 2){
                C[i][j] += A[i][k] * B[k][j];
                C[i][j] += A[i][k+1] * B[k+1][j];
            }
        }
    }
}

void static_tiling(int A[N][N], int B[N][N], int C[N][N]){
    for (int x = 0; x < N; x += TILE){
        for (int y = 0; y < N; y += TILE){
            for (int z = 0; z < N; z += TILE){
                for (int i = x; i < x+TILE; i++){
                    for (int j = y; j < y+TILE; j++){
                        for (int k = z; k < z+TILE; k++){
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

void dynamic_naive(int **A, int **B, int **C){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            for (int k = 0; k < N; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void dynamic_interchange(int **A, int **B, int **C){
    for (int i = 0; i < N; i++){
        for (int k = 0; k < N; k++){
            for (int j = 0; j < N; j++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void dynamic_unrolling(int **A, int **B, int **C){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            for (int k = 0; k < N; k += 2){
                C[i][j] += A[i][k] * B[k][j];
                C[i][j] += A[i][k+1] * B[k+1][j];
            }
        }
    }
}

void dynamic_tiling(int **A, int **B, int **C){
    for (int x = 0; x < N; x += TILE){
        for (int y = 0; y < N; y += TILE){
            for (int z = 0; z < N; z += TILE){
                for (int i = x; i < x + TILE; i++){
                    for (int j = y; j < y + TILE; j++){
                        for (int k = z; k < z + TILE; k++){
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

void dynamic_mem(int mode){

    // Allocating Memory
    int **A = (int**)malloc(sizeof(int*) * N);
    int **B = (int**)malloc(sizeof(int*) * N);
    int **C = (int**)malloc(sizeof(int*) * N);
    for (int i = 0; i < N; i++){
        A[i] = (int*)malloc(sizeof(int) * N);
        B[i] = (int*)malloc(sizeof(int) * N);
        C[i] = (int*)malloc(sizeof(int) * N);
    }

    // Starting up the matrix
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            A[i][j] = j;
            B[i][j] = i;
            C[i][j] = 0;
        }
    }

    switch(mode){
        case 0: // Naive
            dynamic_naive(A, B, C);
            break;
        
        case 1: // Interchange
            dynamic_interchange(A, B, C);
            break;
        
        case 2: // Unrolling
            dynamic_unrolling(A, B, C);
            break;
        
        case 3: // Tiling
            dynamic_tiling(A, B, C);
            break;

        default:
            printf("Mode %d not found.\n", mode);
            break;
    }


    for(int i = 0; i < N; i++){
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
}

void static_mem(int mode){

    int A[N][N], B[N][N], C[N][N];
    // Starting up the matrix
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            A[i][j] = j;
            B[i][j] = i;
            C[i][j] = 0;
        }
    }

    // Switch do modo de multiplicação
    switch(mode){
        case 0: // Naive
            static_naive(A, B, C);
            break;
            
        case 1: // Interchange
            static_interchange(A, B, C);
            break;
        
        case 2: // Unrolling
            static_unrolling(A, B, C);
            break;
            
        case 3: // Tiling
            static_tiling(A, B, C);
            break;
        
        default:
            printf("Mode %d not found.", mode);
            break;
    }
}

int main(int argc, char *argv[]){

    // Checking arguments
    if (argc != 3){
        printf("Wrong arguments. Use: %s <allocation> <mode>\n", argv[0]);
        printf("Allocation: 0=static, 1=dynamic\n");
        printf("Mode: 0=naive, 1=interchange, 2=unrolling, 3=tiling\n");
        return 1;
    }

    int allocation = atoi(argv[1]);
    int mode = atoi(argv[2]);
    
    // STATIC OR DYNAMIC MEMORY ALLOCATION
    if (!allocation) static_mem(mode);
    else dynamic_mem(mode);


    return 0;
} 
    