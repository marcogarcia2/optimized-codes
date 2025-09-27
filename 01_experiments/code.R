library(FrF2)

# ---- DESIGN 2^3 (sem redundâncias) ----
plan.person <- FrF2(
  nruns        = 8,
  nfactors     = 3,
  replications = 1,
  repeat.only  = FALSE,
  factor.names = list(
    Modo       = c("Modificado", "Padrao"),
    Alcance    = c("Curto", "Longo"),
    Velocidade = c("Lenta", "Rapida")
  ),
  randomize    = FALSE
)

# Respostas (tempo médio em s) nas 8 combinações
resultados <- c(7.76, 10.13, 5.86, 8.76, 9.03, 14.59, 9.18, 13.04)

# Desvios-padrão por ponto (20 repetições por condição – dados do NIST)
SD <- c(0.53, 0.74, 0.47, 1.24, 1.12, 3.22, 1.80, 2.58)
r  <- 20  # réplicas por ponto
## ---------------------------
## Box, Hunter & Hunter (1978)
## 2^3 fatorial completo
## ---------------------------

## Dados (médias por ponto e SD de 20 repetições)
dat <- data.frame(
  Y  = c(7.76, 10.13, 5.86, 8.76, 9.03, 14.59, 9.18, 13.04),
  A  = c(-1, +1, -1, +1, -1, +1, -1, +1),  # Mode: -1=Modificado, +1=Padrão
  B  = c(-1, -1, +1, +1, -1, -1, +1, +1),  # Range: -1=Curto, +1=Longo
  C  = c(-1, -1, -1, -1, +1, +1, +1, +1),  # Speed: -1=Lenta, +1=Rápida
  SD = c(0.53, 0.74, 0.47, 1.24, 1.12, 3.22, 1.80, 2.58)
)

## Parâmetros do experimento
n <- nrow(dat)    # 8 combinações
r <- 20           # 20 repetições por combinação

## Interações (sinais)
dat$AB  <- with(dat, A*B)
dat$AC  <- with(dat, A*C)
dat$BC  <- with(dat, B*C)
dat$ABC <- with(dat, A*B*C)

## Contrastes usando as MÉDIAS de célula
contrast <- function(signs, y) sum(signs * y)

q <- c(
  A   = contrast(dat$A,   dat$Y),
  B   = contrast(dat$B,   dat$Y),
  C   = contrast(dat$C,   dat$Y),
  AB  = contrast(dat$AB,  dat$Y),
  AC  = contrast(dat$AC,  dat$Y),
  BC  = contrast(dat$BC,  dat$Y),
  ABC = contrast(dat$ABC, dat$Y)
)

## Efeitos (estimativas): efeito = q / (n/2)
effects <- q / (n/2)

## Somas de quadrados dos efeitos (entre tratamentos):
## (usando meios de célula): SS_X = r * q^2 / n
SS <- r * (q^2) / n
SStrt <- sum(SS)

## Erro residual a partir dos SD por ponto (cada SD vem de r=20 reps):
## SSE = sum_i (r-1) * SD_i^2
SSE <- sum((r - 1) * dat$SD^2)
dfE <- n * (r - 1)
MSE <- SSE / dfE

## Total corrigido
SST <- SStrt + SSE

## Erro-padrão do efeito (fatorial 2^k):
## SE(effect) = sqrt( 4 * MSE / (n * r) )
SE_eff <- sqrt(4 * MSE / (n * r))

## Estatísticas t
tvals <- effects / SE_eff

## t crítico (bicaudal, 5%)
tcrit <- qt(0.975, df = dfE)

## Influência (% de SStrt explicada por cada efeito)
influence <- SS / SStrt * 100

## Tabela final
res <- data.frame(
  Efeito     = names(q),
  q          = as.numeric(q),
  Efeito_hat = as.numeric(effects),
  SS         = as.numeric(SS),
  t          = as.numeric(tvals),
  Influencia_pct = as.numeric(influence)
)

## Impressões
cat(sprintf("\nMSE = %.6f | df_error = %d | SE(efeito) = %.6f | t_crit(5%%,2-caudas) = %.3f\n",
            MSE, dfE, SE_eff, tcrit))
print(res, row.names = FALSE, digits = 4)

cat(sprintf("\nSStrt = %.6f | SSE = %.6f | SST = %.6f\n", SStrt, SSE, SST))
