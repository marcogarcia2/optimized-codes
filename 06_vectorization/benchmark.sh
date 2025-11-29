#!/bin/bash

# ============================================================
#  Benchmark para o filtro Gaussiano 2D
# ============================================================

SRC="gauss2d.c"
OUT_BASE="gauss2d"

echo "==> Compilando versões..."
echo ""

# ------------------------------------------------------------
# COMPILAÇÕES
# ------------------------------------------------------------

# 1) Sem otimização — baseline
gcc $SRC -o ${OUT_BASE}_no_opt

# 2) O3 desativando vetorização automática — baseline escalar otimizado
gcc -O3 -fno-tree-vectorize $SRC -o ${OUT_BASE}_O3_scalar

# 3) O3 com vetorização automática do GCC
gcc -O3 $SRC -o ${OUT_BASE}_O3_auto

# 4) O3 com vetorização manual SSE (intrínsecos)
gcc -O3 -mssse3 $SRC -o ${OUT_BASE}_O3_sse

echo "Compilação concluída."
echo "=============================================================="
echo ""

# ------------------------------------------------------------
# EXECUÇÃO DOS BINÁRIOS
# ------------------------------------------------------------

echo "==> Executando versões..."
echo ""

echo "[1] Sem Otimização"
./${OUT_BASE}_no_opt
echo "--------------------------------------------------------------"

echo "[2] O3 (escalar, SEM vetorização automática)"
./${OUT_BASE}_O3_scalar
echo "--------------------------------------------------------------"

echo "[3] O3 (vetorização automática do GCC)"
./${OUT_BASE}_O3_auto
echo "--------------------------------------------------------------"

echo "[4] O3 + SSE (vetorização manual com intrínsecos)"
./${OUT_BASE}_O3_sse
echo "--------------------------------------------------------------"

# ------------------------------------------------------------
# LIMPEZA
# ------------------------------------------------------------

echo "==> Removendo binários..."
rm -f ${OUT_BASE}_no_opt \
      ${OUT_BASE}_O3_scalar \
      ${OUT_BASE}_O3_auto \
      ${OUT_BASE}_O3_sse

echo "Finalizado!"
echo "=============================================================="
