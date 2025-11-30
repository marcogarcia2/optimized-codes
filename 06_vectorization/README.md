# Vetorização

Esta atividade implementa e compara duas versões de um **filtro Gaussiano 2D** aplicado sobre uma matriz grande (4096×4096).

1. **Versão escalar** — implementação básica em C usando loops convencionais.
2. **Versão vetorizada (SSE)** — usa intrínsecos `SSSE3` para explorar paralelismo SIMD.

O objetivo é analisar o impacto da **vetorização manual** e das **otimizações do compilador** no desempenho de um kernel computacional simples.

Adicionalmente, verificou-se o impacto das seguintes diretivas de compilação sobre ambas as implementações dos kernels:

  * Sem otimizações
  * `-O3 -fno-tree-vectorize` (otimizações sem vetorização automática)
  * `-O3` (otimizações completas do GCC)
  * `-O3 -mssse3` (vetorização manual com intrínsecos SSE)

Para executar o teste, execute em um terminal:

```bash
./benchmark.sh
```

A saída do programa já imprime o tempo total, tempo médio e speedup.
