#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// -------------- MACROS e Funções de CACHE -------------- //
#define KB (1024)
#define MB (1024 * KB)
#define GB (1024 * MB)
#define LARGEST_CACHE_SZ (8 * MB)

// Dummy Buffer para "sujar" a cache
static unsigned char dummy_buffer[LARGEST_CACHE_SZ];

// Função que limpa toda a cache do processador (L3 de 8MB)
void clean_cache(void){
    unsigned long long i;
    for (i = 0; i < LARGEST_CACHE_SZ; i++)
        dummy_buffer[i] += 1;
}

// ---------------- // --------------- // ---------------- //



// -------------- MACROS e Funções de ARRAY -------------- //
#define ARRAY_SZ (4096*1024) 
#define ARRAY_MAX_ELEMENT_VAL (4096*8)
#define MAX_REPS 10

// Função que aloca memória para o array
int *create_array(void){    
    int *array = (int*)malloc(sizeof(int) * ARRAY_SZ);
    return array;
}

// Função que reseta o array sempre com os mesmos valores aleatórios
void reset_array(int *array){
    srand(42); // Garante que o mesmo array seja alocado sempre
    for (int i = 0; i < ARRAY_SZ; i++)
        array[i] = rand() % ARRAY_MAX_ELEMENT_VAL;    
}

// Função que libera a memória do array
void destroy_array(int **array_ref){
    int *array = *array_ref;
    free(array);
    *array_ref = NULL;
}

// Função que checa se o array está ordenado (Usado para debug)
bool check_sorting(const int *array){
    for (int i = 0; i < ARRAY_SZ-1; i++){
        if (array[i] > array[i+1]){
            printf("Array NÃO ordenado.\n");
            return false;
        }
    }
    printf("Array ordenado corretamente!\n");
    return true;
}

// Função para exibir o array (Usado para debug)
void print_array(const int *array){
    for (int i = 0; i < ARRAY_SZ; i++){
        printf("%d, ", array[i]);
    }
    printf("\b\b  \n");
    return;
}

// ---------------- // --------------- // ---------------- //



// -------------- ALGORITMOS DE ORDENAÇÃO --------------- //

// Função para trocar dois elementos do array (usado por quicksort e heapsort)
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

// Função auxiliar do Quick Sort para ordenar e retornar o pivo
int partition(int *array, int left, int right){

    // Escolhendo o último como sendo o pivot
    int pivot = array[right];
    int i = left-1;
    for(int j = left; j < right; j++){
        // Se o elemento j atual é menor que o pivo:
        if (array[j] <= pivot){
            i++; // deve ser mandado para a esquerda do pivo
            swap(&array[i], &array[j]);
        }
    }

    // Colocando o pivo no local correto
    swap(&array[i+1], &array[right]);
    
    // Retorna a posicao do pivo
    return i+1;
}

// Quick Sort
void quick_sort(int *array, int left, int right){
    if (left < right){
        int pi = partition(array, left, right);
        quick_sort(array, left, pi-1);
        quick_sort(array, pi+1, right);
    }
}

// Função auxiliar do Merge Sort para fundir dois sub-arrays
void merge(int *array, int left, int mid, int right){
    // Mergeando dois subarrays, um de left até mid
    // e o outro de mid+1 até right

    // Calculando o tamanho dos subarrays
    int left_size = mid - left + 1;
    int right_size = right - mid;

    int *L = (int*)malloc(sizeof(int) * left_size);
    int *R = (int*)malloc(sizeof(int) * right_size);

    // Copia os valores para os subarrays correspondentes
    for (int i = 0; i < left_size; i++) L[i] = array[left+i];
    for (int j = 0; j < right_size; j++) R[j] = array[mid+j+1];

    // Ordenando os subarrays no array original
    int i = 0, j = 0, k = left;
    while (i < left_size && j < right_size){
        
        if (L[i] < R[j])
            array[k++] = L[i++];
        
        else 
            array[k++] = R[j++];
        
    }

    // termina de copiar os valores faltantes
    while (i < left_size) array[k++] = L[i++];
    while (j < right_size) array[k++] = R[j++];

    destroy_array(&L);
    destroy_array(&R);
}

// Merge Sort
void merge_sort(int *array, int left, int right){
    
    // Caso base: 1 elemento
    if (left >= right)
        return;

    // Meio arredondado para baixo
    int mid = (left) + (right - left) / 2; // evita overflow
    merge_sort(array, left, mid);
    merge_sort(array, mid+1, right);
    merge(array, left, mid, right);
}

// Função auxiliar do Heapify que corrige o array para ter propriedade de max_heap
void heapify(int *array, int n, int i) {
    int largest = i;       // assume que a raiz é o maior
    int left  = 2*i + 1;   // filho esquerdo
    int right = 2*i + 2;   // filho direito

    // se o filho esquerdo é maior que a raiz
    if (left < n && array[left] > array[largest])
        largest = left;

    // se o filho direito é maior que o "maior até agora"
    if (right < n && array[right] > array[largest])
        largest = right;

    // se o maior não é a raiz
    if (largest != i) {
        swap(&array[i], &array[largest]);
        // recursivamente heapifica o sub-árvore afetado
        heapify(array, n, largest);
    }
}

// Heap Sort
void heap_sort(int *array, int size) {
    // Baseado em Max_heap
    for (int i = size/2 - 1; i >= 0; i--)
        heapify(array, size, i); // Constroi o max_heap

    // extrai os maiores elementos do max_heap um por um
    for (int i = size-1; i > 0; i--) {
        swap(&array[0], &array[i]);   // move a raiz para o fim
        heapify(array, i, 0);       // restaura heap no restante
    }
}

// ---------------- // --------------- // ---------------- //



// ------------------------ MAIN ------------------------- //
int main(int argc, char *argv[]){

    if (argc > 2){
        printf("Wrong arguments. Use: ./sorting <num_runs>");
    }

    double times[3];

    clock_t start, end;

    int *array = create_array();

    int num_runs;
    if (argc == 1) num_runs = 1;
    else num_runs = atoi(argv[1]);
    if (num_runs <= 0){
        puts("ERROR! Enter a valid number of runs.");
        exit(0);
    }
    
    for (int rep = 1; rep <= num_runs; rep++){
    
        // Loop sobre os algoritmos de ordenação implementados
        for (int alg = 0; alg < 3; alg++){
            
            // Resetando os valores originais e limpando a cache do processador
            reset_array(array);
            clean_cache();
            
            /*
            Para um array tão grande quanto ARRAY_SZ, o tempo gasto na instrução 
            de salto com switch é irrelevante frente ao tempo total de execução. 
            Para o código ficar mais intuitivo, achei melhor colocar o start antes 
            do switch e o end logo após.
            */
        
        // Iniciando a contagem do tempo 
        start = clock();

            switch(alg){
                case 0:
                    quick_sort(array, 0, ARRAY_SZ-1);
                    break;
                    
                case 1:
                    merge_sort(array, 0, ARRAY_SZ-1);
                    break;
                    
                case 2:
                    heap_sort(array, ARRAY_SZ);
                    break;
                    
                default:
                    break;
            }

            // Fim do tempo
            end = clock();
            
            // Calculando o tempo gasto em segundos
            times[alg] += (double)(end-start)/CLOCKS_PER_SEC;
        }

    }

    // Desalocando a memória do array
    destroy_array(&array);

    printf("------------- Results -------------\n");
    printf("Random array with %d elements:\n", ARRAY_SZ);
    printf("Quick Sort\t %lf s\n", times[0]/num_runs);
    printf("Merge Sort\t %lf s\n", times[1]/num_runs);
    printf("Heap Sort\t %lf s\n", times[2]/num_runs);
    if (num_runs > 1) printf("Runs:\t\t %d\n", num_runs);


    return 0;
}
