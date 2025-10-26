#!/bin/bash

# Variáveis do programa
PROGRAMS=("fannkuch-redux" "n-body")
FLAGS=("-O0" "-O1" "-O2" "-O3" "-Os")
REPS=${1:-10}

# Arrays para armazenar os resultados
declare -A sum_tc
declare -A sum_te
declare -A sizes

# Função que executa um comando, mede o tempo real e retorna apenas o número (em segundos)
measure_time() {
  { time "$@" >/dev/null; } 2>&1 \
    | grep real \
    | awk '{print $2}' \
    | sed 's/.*m//' \
    | sed 's/s//' \
    | tr ',' '.'
}

# Função que retorna o tamanho de um arquivo
measure_size() {
    stat -f "%z %N" $@ \
    | awk '{print $1}'
}

# Função que remove os binários
remove_binaries(){
    for prog in "${PROGRAMS[@]}"; do
        rm -f "${prog}-O"*
    done
}

# Função que "aquece os motores" do processo
discard_first_execution(){
    for prog in "${PROGRAMS[@]}"; do
        gcc -O0 "${prog}.c" -lm -o foo
        rm foo
        break
    done
}


# -------------- FLUXO PRINCIPAL DO PROGRAMA -------------- #
discard_first_execution
remove_binaries

echo "Repetições: $REPS"
for i in $(seq 1 $REPS); do

    echo "# ------- EXECUÇÃO $i ------- #"

    for prog in "${PROGRAMS[@]}"; do
        for flag in "${FLAGS[@]}"; do

            # --- Tempo de Compilação --- #
            tc=$(measure_time gcc-14 $flag "${prog}.c" -lm -o $prog$flag)
            sum_tc["$prog,$flag"]=$(echo "${sum_tc["$prog,$flag"]:-0} + $tc" | bc) # somando ao acumulador
            

            # --- Tempo de execução --- #
            te=$(measure_time ./$prog$flag)
            sum_te["$prog,$flag"]=$(echo "${sum_te["$prog,$flag"]:-0} + $te" | bc) # somando ao acumulador


            # --- Tamanho do Binário --- #
            if [ $i -eq 1 ]; then
                tb=$(measure_size $prog$flag)
                sizes["$prog,$flag"]=$tb 
            fi

            # echo "$prog $flag"
            # echo "Tempo de Compilação:  ${tc} s"
            # echo "Tempo de Execução:    ${te} s"
            # echo "Tamanho do Binário:   ${sizes["$prog,$flag"]} bytes"
            # echo

            # Apaga o binário
            rm $prog$flag
        
        done # Fim for flag
    
    done # Fim for prog
    
    echo
    echo

done # Fim for 1..REPS


# Montando uma tabela para dispor os dados
echo
echo "============================ RESULTADOS ============================"
printf "%-15s %-4s %15s %15s %15s\n" "Programa" "Flag" "TC médio (s)" "TE médio (s)" "Tamanho (bytes)"
printf "%s\n" "--------------------------------------------------------------------"

for prog in "${PROGRAMS[@]}"; do
  for flag in "${FLAGS[@]}"; do
    tc_sum=${sum_tc["$prog,$flag"]:-0}
    te_sum=${sum_te["$prog,$flag"]:-0}
    avg_tc=$(bc <<< "scale=3; $tc_sum / $REPS")
    avg_te=$(bc <<< "scale=3; $te_sum / $REPS")
    size=${sizes["$prog,$flag"]:-0}
    printf "%-15s %-4s %15s %15s %15s\n" "$prog" "$flag" "$avg_tc" "$avg_te" "$size"
  done
done
echo "===================================================================="
