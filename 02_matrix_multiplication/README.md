# Perf 

```shell
sudo apt install perf
```

```shell
gcc matmul.c -o matmul
```
```shell
sudo perf stat -r 10 -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./matmul X Y
```
Em que X e Y dizem respeito ao tipo de alocação de memória e ao tipo 
