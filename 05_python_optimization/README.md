# Otimizações em Python

Esta prática consiste em utilizar os módulos `cProfile`, `pstats`, `timeit` e `functools` para otimizar e perfilar um código em Python. O código utilizado nesta análise foi baseado no repositório [blood_donation_search](https://github.com/marcogarcia2/blood_donation_search).

Foram estudadas as buscas BFS, A* e A* otimizado com as técnicas aprendidas em sala.

Rode o script com:
```shell
python3 main.py
```


Exemplo de saída do algoritmo:
```
GRAFO DA CIDADE DE SÃO CARLOS
Número de nós		9042
Número de arestas	22340

ROTA BFS	 89 nós
ROTA A*		 133 nós
ROTA A* Optim.	 133 nós

INICIANDO O PERFILAMENTO...

BFS
Tempo de 30 execuções		0.160753 s
Tempo médio: 			5.358443 ms
Tue Nov 11 02:09:56 2025    bfs_stats

         48052 function calls in 0.013 seconds

   Ordered by: standard name

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
        1    0.000    0.000    0.013    0.013 <string>:1(<module>)
        1    0.008    0.008    0.013    0.013 buscas.py:6(bfs)
     8513    0.002    0.000    0.003    0.000 digraph.py:901(successors)
        1    0.000    0.000    0.013    0.013 {built-in method builtins.exec}
     8513    0.001    0.000    0.001    0.000 {built-in method builtins.iter}
     8514    0.001    0.000    0.001    0.000 {method 'add' of 'set' objects}
    11289    0.001    0.000    0.001    0.000 {method 'append' of 'collections.deque' objects}
        1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}
    11219    0.001    0.000    0.001    0.000 {method 'popleft' of 'collections.deque' objects}


A*
Tempo de 30 execuções		0.585089 s
Tempo médio: 			19.502965 ms
Tue Nov 11 02:09:57 2025    astar_stats

         315566 function calls in 0.074 seconds

   Ordered by: standard name

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
    11345    0.003    0.000    0.003    0.000 <frozen _collections_abc>:831(values)
    11345    0.001    0.000    0.001    0.000 <frozen _collections_abc>:850(__init__)
    22713    0.005    0.000    0.008    0.000 <frozen _collections_abc>:916(__iter__)
        1    0.000    0.000    0.074    0.074 <string>:1(<module>)
     4563    0.010    0.000    0.019    0.000 buscas.py:43(__haversine)
        1    0.016    0.016    0.074    0.074 buscas.py:57(a_estrela)
        2    0.000    0.000    0.000    0.000 buscas.py:66(<genexpr>)
    22713    0.005    0.000    0.015    0.000 buscas.py:82(<genexpr>)
     9124    0.001    0.000    0.021    0.000 buscas.py:91(<genexpr>)
    11345    0.003    0.000    0.004    0.000 coreviews.py:103(__getitem__)
    22690    0.002    0.000    0.002    0.000 coreviews.py:44(__init__)
    11345    0.002    0.000    0.003    0.000 coreviews.py:50(__iter__)
    11368    0.001    0.000    0.001    0.000 coreviews.py:53(__getitem__)
    11345    0.003    0.000    0.004    0.000 coreviews.py:81(__getitem__)
     4364    0.001    0.000    0.002    0.000 digraph.py:901(successors)
    11345    0.002    0.000    0.006    0.000 graph.py:498(__getitem__)
    11345    0.001    0.000    0.001    0.000 multidigraph.py:861(is_multigraph)
    18252    0.004    0.000    0.005    0.000 reportviews.py:190(__getitem__)
     4365    0.001    0.000    0.001    0.000 {built-in method _heapq.heappop}
     4563    0.001    0.000    0.001    0.000 {built-in method _heapq.heappush}
        1    0.000    0.000    0.074    0.074 {built-in method builtins.exec}
    18252    0.001    0.000    0.001    0.000 {built-in method builtins.isinstance}
    15709    0.001    0.000    0.001    0.000 {built-in method builtins.iter}
    15908    0.005    0.000    0.041    0.000 {built-in method builtins.min}
     4563    0.000    0.000    0.000    0.000 {built-in method math.atan2}
     9126    0.001    0.000    0.001    0.000 {built-in method math.cos}
    18252    0.001    0.000    0.001    0.000 {built-in method math.radians}
     9126    0.001    0.000    0.001    0.000 {built-in method math.sin}
     9126    0.001    0.000    0.001    0.000 {built-in method math.sqrt}
        1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}
    11368    0.001    0.000    0.001    0.000 {method 'get' of 'dict' objects}


A* Otimizado
Tempo de 30 execuções		0.425831 s
Tempo médio: 			14.194358 ms
Tue Nov 11 02:09:57 2025    opt_astar_stats

         218934 function calls in 0.051 seconds

   Ordered by: standard name

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
     4364    0.001    0.000    0.001    0.000 <frozen _collections_abc>:827(items)
    11345    0.003    0.000    0.003    0.000 <frozen _collections_abc>:831(values)
    15709    0.001    0.000    0.001    0.000 <frozen _collections_abc>:850(__init__)
    15709    0.003    0.000    0.008    0.000 <frozen _collections_abc>:897(__iter__)
    22713    0.004    0.000    0.008    0.000 <frozen _collections_abc>:916(__iter__)
        1    0.000    0.000    0.051    0.051 <string>:1(<module>)
        1    0.000    0.000    0.000    0.000 buscas.py:105(register_graph)
        1    0.012    0.012    0.050    0.050 buscas.py:123(optimized_a_estrela)
     4563    0.001    0.000    0.004    0.000 buscas.py:130(heuristica)
     7646    0.001    0.000    0.001    0.000 buscas.py:133(<genexpr>)
    22713    0.005    0.000    0.014    0.000 buscas.py:148(<genexpr>)
        1    0.000    0.000    0.000    0.000 buscas.py:161(reconstruir_caminho)
     4364    0.002    0.000    0.002    0.000 coreviews.py:103(__getitem__)
    15709    0.001    0.000    0.001    0.000 coreviews.py:44(__init__)
    15709    0.002    0.000    0.004    0.000 coreviews.py:50(__iter__)
    11368    0.001    0.000    0.001    0.000 coreviews.py:53(__getitem__)
    11345    0.003    0.000    0.004    0.000 coreviews.py:81(__getitem__)
     4364    0.001    0.000    0.003    0.000 graph.py:498(__getitem__)
        1    0.000    0.000    0.000    0.000 multidigraph.py:861(is_multigraph)
     4365    0.001    0.000    0.001    0.000 {built-in method _heapq.heappop}
     4562    0.001    0.000    0.001    0.000 {built-in method _heapq.heappush}
        1    0.000    0.000    0.051    0.051 {built-in method builtins.exec}
        1    0.000    0.000    0.000    0.000 {built-in method builtins.id}
    15709    0.001    0.000    0.001    0.000 {built-in method builtins.iter}
    15168    0.005    0.000    0.020    0.000 {built-in method builtins.min}
      133    0.000    0.000    0.000    0.000 {method 'append' of 'list' objects}
        1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}
    11368    0.001    0.000    0.001    0.000 {method 'get' of 'dict' objects}
```