import random
import numpy as np

N = 256

# ==========================================================
# Funções auxiliares

def get_order():
    return N

def checksum(C):
    acc = 0
    for i in range (N):
        acc += C[i][i]
    print(f"Checksum: {acc}")

def create_random_matrix():
    """Matriz aleatória (cache não ajuda)"""
    return [[random.randint(1, 100) for _ in range(N)] for _ in range(N)]

def build_matrices():
    random.seed(42)
    A = create_random_matrix()
    B = create_random_matrix()
    C = [[0 for _ in range(N)] for _ in range(N)]
    return A, B, C
# ==========================================================


### Multiplicação Naive, usando listas em Python puro
def naive(A, B, C):
    for i in range(N):
        for j in range(N):
            for k in range(N):
                C[i][j] += A[i][k] * B[k][j]
    return C


### Multiplicação otimizada, usando NumPy
def np_matmul(A, B, C):
    A_np = np.array(A)
    B_np = np.array(B)
    C_np = A_np @ B_np
    return C_np.tolist() 


# ==========================================================
# Função de Benchmark
def run_matrix_mult(mode=0):
    """Executa a multiplicação conforme os parâmetros e tipo de matriz"""
    A, B, C = build_matrices()

    func_map = [naive, np_matmul]
        
    if 0 <= mode < len(func_map):
        C = func_map[mode](A, B, C)
        # checksum(C) # debugging
    else:
        raise ValueError(f"Modo inválido: {mode}")

    return C
# ==========================================================