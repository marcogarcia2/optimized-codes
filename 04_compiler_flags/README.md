# Otimizações pelo Compilador

Esta prática consiste em utilizar diferentes flags compilação para avaliar o seu impacto nos programas. O **Shell Script** `benchmark.sh` mede tempo de compilação, tempo de execução e tamanho do binário gerado pela compilação dos programas escolhidos. 

> Todos os programas foram tirados do [site do CLBG](https://benchmarksgame-team.pages.debian.net/benchmarksgame/). Os programas **fannkuch-redux** e **n-body**, presentes no repositório, não são de minha autoria, a sua fonte está devidamente especificada no comentário presente no topo dos arquivos. 

Para rodar o benchmark, execute o comando abaixo, substituindo `<arg>` pelo número de repetições desejadas:

```shell
./benchmark.sh <arg>
```

Ao fim da execução, uma tabela com os resultados obtidos irá aparecer no terminal.