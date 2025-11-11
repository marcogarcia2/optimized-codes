import timeit
import cProfile
import pstats
import colorful as cf

import sys
import os
sys.path.append(os.path.dirname(__file__))

# Importando a classe Graph e funções de um outro trabalho
from helper_functions import Graph
from buscas import bfs, a_estrela, optimized_a_estrela

# Carrega com os dados de São Carlos
G = Graph("sao_carlos.graphml")
print(cf.bold_red("GRAFO DA CIDADE DE SÃO CARLOS"))
print(cf.bold_white(f"Número de nós\t\t{len(G.graph.nodes)}"))
print(cf.bold_white(f"Número de arestas\t{len(G.graph.edges)}\n"))

# Escolhendo os nós que irão participar da busca
start_node = G.get_random_nodes(1)[0]   # inicio da busca
goal_node = G.get_random_nodes(1)       # fim da busca

# Dados sobre a rota
bfs_route = bfs(G.graph, start_node, goal_node)
a_star_route = a_estrela(G.graph, start_node, goal_node)
opt_a_star_route = optimized_a_estrela(G.graph, start_node, goal_node)
print(cf.bold_orange("ROTA BFS\t"), cf.bold_white(f'{len(bfs_route)} nós'))
print(cf.bold_orange("ROTA A*\t\t"), cf.bold_white(f'{len(a_star_route)} nós'))
print(cf.bold_orange("ROTA A* Optim.\t"), cf.bold_white(f'{len(a_star_route)} nós\n'))

####

# Profiling com cProfile e pstats
print(cf.bold_green("INICIANDO O PERFILAMENTO...\n"))
NRUNS = 30

# Perfilamento com cProfile
cProfile.run('bfs(G.graph, start_node, goal_node)', 'bfs_stats')
cProfile.run('a_estrela(G.graph, start_node, goal_node)', 'astar_stats')
cProfile.run('optimized_a_estrela(G.graph, start_node, goal_node)', 'opt_astar_stats')

algorithms = [
    ('BFS', 'bfs_stats', lambda: bfs(G.graph, start_node, goal_node)),
    ('A*', 'astar_stats', lambda: a_estrela(G.graph, start_node, goal_node)),
    ('A* Otimizado', 'opt_astar_stats', lambda: optimized_a_estrela(G.graph, start_node, goal_node))
]

# Exibindo os resultados de cada algoritmo separadamente
for name, filename, func in algorithms:
    print(cf.bold_green(name))

    # timeit
    t = timeit.timeit(func, number=NRUNS)
    tm = (t/30) * 1000
    print(cf.bold_white(f"Tempo de {NRUNS} execuções\t\t{t:.6f} s"))
    print(cf.bold_white(f"Tempo médio: \t\t\t{tm:.6f} ms"))

    # pstats exibe os resultados do cProfile 
    stats = pstats.Stats(filename)
    stats.strip_dirs().sort_stats('cumulative').print_stats()

    # Limpando os arquivos
    if os.path.exists(filename):
        os.remove(filename)

