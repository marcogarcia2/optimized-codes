# Profiling de Algoritmos - Parte 1

Esta prática consiste em utilizar a ferramenta **perf**, um perfilador por amostragem, para coletar diferentes métricas de um programa que implementa diferentes algoritmos de **multiplicação de matrizes**. Instale o perfilador com:

```shell
sudo apt install linux-tools-common
sudo apt install linux-tools-generic
sudo apt install linux-tools-5.15.0-41-generic
```

Compile o código com:

```shell
gcc matmul.c -o matmul
```
Para adquirir as métricas desejadas, consulte este [link](https://www.brendangregg.com/perf.html). Para esta atividade, algumas métricas de cache e de branch foram escolhidas. Execute o binário com:

```shell
sudo perf stat -r 10 -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./matmul X Y
```
Neste comando, deve-se passar os argumentos X e Y referentes ao tipo de alocação de memória e ao algoritmo de multiplicação de matrizes, respectivamente.

--- 
- **0 Y:** Alocação de Memória Estática
- **1 Y:** Alocação de Memória Dinâmica
--- 
- **X 0:** Naive
- **X 1:** Loop Interchange
- **X 2:** Loop Unrolling
- **X 3:** Loop Tiling
--- 

**Exemplo:** Loop Unrolling com Alocação Dinâmica 
```shell
sudo perf stat -r 10 -e ... ./matmul 1 2
```
