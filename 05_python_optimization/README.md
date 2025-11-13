# Otimizações em Python

Esta prática consiste em utilizar os módulos `cProfile`, `pstats`, `timeit` e `functools` para otimizar e perfilar um código em Python, além do uso de bibliotecas já otimizadas. O código utilizado nesta análise foi baseado no repositório [blood_donation_search](https://github.com/marcogarcia2/blood_donation_search).

Foram estudadas as buscas BFS, A* e A* otimizado com as técnicas aprendidas em sala. Além disso, foi investigado o uso da biblioteca **NumPy** para multiplicação de matrizes.

Rode o script com:
```shell
python3 main.py
```


Exemplo de saída do algoritmo:
```
BUSCAS - GRAFO DA CIDADE DE SÃO CARLOS
Número de nós		9042
Número de arestas	22340
ROTA BFS		58 nós
ROTA A*			73 nós
ROTA A* Optim.		73 nós

MULTIPLICAÇÃO DE MATRIZES
ORDEM			256x256

INICIANDO O PERFILAMENTO...

BFS
Tempo de 30 execuções		0.076320 s
Tempo médio: 			2.544007 ms
Thu Nov 13 16:36:11 2025    bfs_stats

         28148 function calls in 0.007 seconds

   Ordered by: cumulative time

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
        1    0.000    0.000    0.007    0.007 {built-in method builtins.exec}
        1    0.000    0.000    0.007    0.007 <string>:1(<module>)
        1    0.004    0.004    0.007    0.007 buscas.py:6(bfs)
     4984    0.001    0.000    0.001    0.000 digraph.py:901(successors)
     6728    0.001    0.000    0.001    0.000 {method 'append' of 'collections.deque' objects}
     4985    0.000    0.000    0.000    0.000 {method 'add' of 'set' objects}
     6463    0.000    0.000    0.000    0.000 {method 'popleft' of 'collections.deque' objects}
     4984    0.000    0.000    0.000    0.000 {built-in method builtins.iter}
        1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}


A*
Tempo de 30 execuções		0.119623 s
Tempo médio: 			3.987435 ms
Thu Nov 13 16:36:11 2025    astar_stats

         73152 function calls in 0.017 seconds

   Ordered by: cumulative time

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
        1    0.000    0.000    0.017    0.017 {built-in method builtins.exec}
        1    0.000    0.000    0.017    0.017 <string>:1(<module>)
        1    0.004    0.004    0.017    0.017 buscas.py:57(a_estrela)
     3681    0.001    0.000    0.010    0.000 {built-in method builtins.min}
     2180    0.000    0.000    0.005    0.000 buscas.py:91(<genexpr>)
     1091    0.002    0.000    0.005    0.000 buscas.py:43(__haversine)
     5182    0.001    0.000    0.003    0.000 buscas.py:82(<genexpr>)
     5182    0.001    0.000    0.002    0.000 <frozen _collections_abc>:916(__iter__)
     2590    0.000    0.000    0.001    0.000 graph.py:498(__getitem__)
     4364    0.001    0.000    0.001    0.000 reportviews.py:190(__getitem__)
     2590    0.001    0.000    0.001    0.000 coreviews.py:103(__getitem__)
     2590    0.001    0.000    0.001    0.000 coreviews.py:81(__getitem__)
     2590    0.001    0.000    0.001    0.000 <frozen _collections_abc>:831(values)
     2590    0.000    0.000    0.001    0.000 coreviews.py:50(__iter__)
      975    0.000    0.000    0.000    0.000 digraph.py:901(successors)
     5180    0.000    0.000    0.000    0.000 coreviews.py:44(__init__)
     2592    0.000    0.000    0.000    0.000 {method 'get' of 'dict' objects}
     4364    0.000    0.000    0.000    0.000 {built-in method builtins.isinstance}
     4364    0.000    0.000    0.000    0.000 {built-in method math.radians}
     3565    0.000    0.000    0.000    0.000 {built-in method builtins.iter}
      976    0.000    0.000    0.000    0.000 {built-in method _heapq.heappop}
     2592    0.000    0.000    0.000    0.000 coreviews.py:53(__getitem__)
     2182    0.000    0.000    0.000    0.000 {built-in method math.cos}
     2182    0.000    0.000    0.000    0.000 {built-in method math.sin}
     2182    0.000    0.000    0.000    0.000 {built-in method math.sqrt}
     2590    0.000    0.000    0.000    0.000 multidigraph.py:861(is_multigraph)
     1091    0.000    0.000    0.000    0.000 {built-in method _heapq.heappush}
     2590    0.000    0.000    0.000    0.000 <frozen _collections_abc>:850(__init__)
     1091    0.000    0.000    0.000    0.000 {built-in method math.atan2}
        2    0.000    0.000    0.000    0.000 buscas.py:66(<genexpr>)
        1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}


A* Otimizado
Tempo de 30 execuções		0.089947 s
Tempo médio: 			2.998246 ms
Thu Nov 13 16:36:11 2025    opt_astar_stats

         50048 function calls in 0.011 seconds

   Ordered by: cumulative time

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
        1    0.000    0.000    0.011    0.011 {built-in method builtins.exec}
        1    0.000    0.000    0.011    0.011 <string>:1(<module>)
        1    0.003    0.003    0.011    0.011 buscas.py:123(optimized_a_estrela)
     3504    0.001    0.000    0.004    0.000 {built-in method builtins.min}
     5182    0.001    0.000    0.003    0.000 buscas.py:148(<genexpr>)
     3565    0.001    0.000    0.002    0.000 <frozen _collections_abc>:897(__iter__)
     5182    0.001    0.000    0.002    0.000 <frozen _collections_abc>:916(__iter__)
     1091    0.000    0.000    0.001    0.000 buscas.py:130(heuristica)
     3565    0.001    0.000    0.001    0.000 coreviews.py:50(__iter__)
     2590    0.001    0.000    0.001    0.000 coreviews.py:81(__getitem__)
     2590    0.001    0.000    0.001    0.000 <frozen _collections_abc>:831(values)
      975    0.000    0.000    0.001    0.000 graph.py:498(__getitem__)
      975    0.000    0.000    0.000    0.000 coreviews.py:103(__getitem__)
      975    0.000    0.000    0.000    0.000 <frozen _collections_abc>:827(items)
     2592    0.000    0.000    0.000    0.000 {method 'get' of 'dict' objects}
     3565    0.000    0.000    0.000    0.000 {built-in method builtins.iter}
     1828    0.000    0.000    0.000    0.000 buscas.py:133(<genexpr>)
     3565    0.000    0.000    0.000    0.000 <frozen _collections_abc>:850(__init__)
     3565    0.000    0.000    0.000    0.000 coreviews.py:44(__init__)
      976    0.000    0.000    0.000    0.000 {built-in method _heapq.heappop}
     2592    0.000    0.000    0.000    0.000 coreviews.py:53(__getitem__)
     1090    0.000    0.000    0.000    0.000 {built-in method _heapq.heappush}
        1    0.000    0.000    0.000    0.000 buscas.py:161(reconstruir_caminho)
        1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}
       73    0.000    0.000    0.000    0.000 {method 'append' of 'list' objects}
        1    0.000    0.000    0.000    0.000 buscas.py:105(register_graph)
        1    0.000    0.000    0.000    0.000 multidigraph.py:861(is_multigraph)
        1    0.000    0.000    0.000    0.000 {built-in method builtins.id}


MatMul
Tempo de 30 execuções		32.851936 s
Tempo médio: 			1095.064529 ms
Thu Nov 13 16:36:12 2025    matmul_stats

         1085252 function calls in 1.277 seconds

   Ordered by: cumulative time

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
        1    0.000    0.000    1.276    1.276 {built-in method builtins.exec}
        1    0.000    0.000    1.276    1.276 <string>:1(<module>)
        1    0.000    0.000    1.276    1.276 matrizes.py:50(run_matrix_mult)
        1    1.103    1.103    1.103    1.103 matrizes.py:32(naive)
        1    0.001    0.001    0.173    0.173 matrizes.py:22(build_matrices)
        2    0.016    0.008    0.173    0.086 matrizes.py:18(create_random_matrix)
   131072    0.022    0.000    0.156    0.000 random.py:336(randint)
   131072    0.058    0.000    0.134    0.000 random.py:295(randrange)
   131072    0.037    0.000    0.056    0.000 random.py:245(_randbelow_with_getrandbits)
   393216    0.020    0.000    0.020    0.000 {built-in method _operator.index}
   131072    0.010    0.000    0.010    0.000 {method 'bit_length' of 'int' objects}
   167735    0.009    0.000    0.009    0.000 {method 'getrandbits' of '_random.Random' objects}
        1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}
        1    0.000    0.000    0.000    0.000 random.py:128(seed)
        1    0.000    0.000    0.000    0.000 {function Random.seed at 0x104873560}
        2    0.000    0.000    0.000    0.000 {built-in method builtins.isinstance}
        1    0.000    0.000    0.000    0.000 {built-in method builtins.len}


MatMul Numpy
Tempo de 30 execuções		1.440883 s
Tempo médio: 			48.029433 ms
Thu Nov 13 16:36:13 2025    np_matmul_stats

         1085255 function calls in 0.189 seconds

   Ordered by: cumulative time

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
        1    0.000    0.000    0.189    0.189 {built-in method builtins.exec}
        1    0.000    0.000    0.189    0.189 <string>:1(<module>)
        1    0.000    0.000    0.189    0.189 matrizes.py:50(run_matrix_mult)
        1    0.001    0.001    0.173    0.173 matrizes.py:22(build_matrices)
        2    0.017    0.008    0.172    0.086 matrizes.py:18(create_random_matrix)
   131072    0.022    0.000    0.155    0.000 random.py:336(randint)
   131072    0.058    0.000    0.133    0.000 random.py:295(randrange)
   131072    0.037    0.000    0.056    0.000 random.py:245(_randbelow_with_getrandbits)
   393216    0.020    0.000    0.020    0.000 {built-in method _operator.index}
        1    0.012    0.012    0.016    0.016 matrizes.py:41(np_matmul)
   131072    0.010    0.000    0.010    0.000 {method 'bit_length' of 'int' objects}
   167735    0.009    0.000    0.009    0.000 {method 'getrandbits' of '_random.Random' objects}
        2    0.003    0.002    0.003    0.002 {built-in method numpy.array}
        1    0.001    0.001    0.001    0.001 {method 'tolist' of 'numpy.ndarray' objects}
        1    0.000    0.000    0.000    0.000 random.py:128(seed)
        1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}
        1    0.000    0.000    0.000    0.000 {function Random.seed at 0x104873560}
        2    0.000    0.000    0.000    0.000 {built-in method builtins.isinstance}
        1    0.000    0.000    0.000    0.000 {built-in method builtins.len}
```