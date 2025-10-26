#!/bin/bash

gcc -o sorting sorting.c -pg
ARG=$1
./sorting "$ARG"
gprof sorting gmon.out > saida_sorting.txt
python3 gprof2dot.py saida_sorting.txt > saida_sorting.dot
dot -Tpng -o grafo.png saida_sorting.dot