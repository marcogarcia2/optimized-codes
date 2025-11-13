import timeit
import cProfile
import pstats
import colorful as cf

import sys
import os
sys.path.append(os.path.dirname(__file__))

NRUNS = 30

### BUSCAS

# Importando a classe Graph e funções de um outro trabalho
from helper_functions import Graph
from buscas import bfs, a_estrela, optimized_a_estrela

# Carrega com os dados de São Carlos
G = Graph("sao_carlos.graphml")
print(cf.bold_red("BUSCAS - GRAFO DA CIDADE DE SÃO CARLOS"))
print(cf.bold_white(f"Número de nós\t\t{len(G.graph.nodes)}"))
print(cf.bold_white(f"Número de arestas\t{len(G.graph.edges)}"))

# Definindo ós que irão participar da busca
start_node = G.get_random_nodes(1)[0]   # inicio da busca
goal_node = G.get_random_nodes(1)       # fim da busca

# Dados sobre a rota
bfs_route = bfs(G.graph, start_node, goal_node)
a_star_route = a_estrela(G.graph, start_node, goal_node)
opt_a_star_route = optimized_a_estrela(G.graph, start_node, goal_node)
print(cf.bold_orange("ROTA BFS\t\t") + cf.bold_white(f'{len(bfs_route)} nós'))
print(cf.bold_orange("ROTA A*\t\t\t") + cf.bold_white(f'{len(a_star_route)} nós'))
print(cf.bold_orange("ROTA A* Optim.\t\t") + cf.bold_white(f'{len(a_star_route)} nós\n'))


### MATRIZES

# Importando funções utilizadas
from matrizes import run_matrix_mult, get_order

# Dados sobre o teste
size = get_order()
print(cf.bold_red("MULTIPLICAÇÃO DE MATRIZES\t"))
print(cf.bold_orange("ORDEM\t\t\t") + cf.bold_white(f"{size}x{size}\n"))


####

# Profiling com cProfile e pstats
print(cf.bold_green("INICIANDO O PERFILAMENTO...\n"))

# Perfilamento com cProfile
cProfile.run('bfs(G.graph, start_node, goal_node)', 'bfs_stats')
cProfile.run('a_estrela(G.graph, start_node, goal_node)', 'astar_stats')
cProfile.run('optimized_a_estrela(G.graph, start_node, goal_node)', 'opt_astar_stats')
cProfile.run('run_matrix_mult(mode=0)', 'matmul_stats')
cProfile.run('run_matrix_mult(mode=1)', 'np_matmul_stats')

algorithms = [
    ('BFS', 'bfs_stats', lambda: bfs(G.graph, start_node, goal_node)),
    ('A*', 'astar_stats', lambda: a_estrela(G.graph, start_node, goal_node)),
    ('A* Otimizado', 'opt_astar_stats', lambda: optimized_a_estrela(G.graph, start_node, goal_node)),
    ('MatMul', 'matmul_stats', lambda: run_matrix_mult(mode=0)),
    ('MatMul Numpy', 'np_matmul_stats', lambda: run_matrix_mult(mode=1)),
]

# Exibindo os resultados de cada algoritmo separadamente
for name, filename, func in algorithms:
    print(cf.bold_green(name))

    # timeit
    n = NRUNS #if name != 'MatMul' else 3
    t = timeit.timeit(func, number=n)
    tm = (t/n) * 1000
    print(cf.bold_white(f"Tempo de {n} execuções\t\t{t:.6f} s"))
    print(cf.bold_white(f"Tempo médio: \t\t\t{tm:.6f} ms"))

    # pstats exibe os resultados do cProfile 
    stats = pstats.Stats(filename)
    stats.strip_dirs().sort_stats('cumulative').print_stats()

    # Limpando os arquivos
    if os.path.exists(filename):
        os.remove(filename)

