# Planejamento de Experimentos

Este diretório contém um roteiro curto em R (`code.R`) para reproduzir um experimento fatorial $2^3$ inspirado em Box, Hunter & Hunter (1978). A atividade tem três objetivos principais:

1. **Construir o planejamento em R**: usando o pacote `FrF2`, geramos a matriz de 8 execuções que combina os fatores `Modo`, `Alcance` e `Velocidade`, permitindo analisar efeitos principais e interações sem redundâncias.
2. **Calcular efeitos e significância**: com as médias e desvios fornecidos, o script monta contrastes, efeitos estimados, somas de quadrados e estatísticas *t* para identificar quais fatores influenciam o tempo médio de resposta.
3. **Comparar variabilidade e influência**: os cálculos de SSE, MSE e percentual de influência ajudam a interpretar a parcela de variabilidade explicada por cada efeito e a validar se o planejamento atende ao objetivo de otimização.

Basta executar o script no R (após instalar `FrF2`) para visualizar a tabela de efeitos e métricas do experimento.
