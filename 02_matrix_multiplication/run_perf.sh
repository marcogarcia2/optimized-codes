#!/bin/bash

gcc -o matmul matmul.c

for X in 0 1; do
    for Y in 0 1 2 3; do
    sudo perf stat -r 10 \
    -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses \
    ./matmul "$X" "$Y"
    echo
    done
done

rm matmul

