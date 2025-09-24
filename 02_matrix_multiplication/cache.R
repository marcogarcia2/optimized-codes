library(FrF2)

# Planejamento de experimentos: 2 alocações × 2 métodos
plan.person <- FrF2(
  nruns = 4, # 2 alocações × 2 métodos
  nfactors = 2,
  factor.names = list(
    Alocacao = c("Estática", "Dinâmica"),
    Metodo   = c("Naive", "Interchange")
  ),
  replications = 1,   # usar médias
  randomize = FALSE
)

summary(plan.person)

# -----------------------------
# Vetores de respostas (médias)
# -----------------------------
# L1-Dcache-loads
L1_cache_loads = c(
  2296266450, # Estática + Naive
  2834498550, # Dinâmica + Naive
  2296053602, # Estática + Interchange
  2834218651  # Dinâmica + Interchange
)

# L1-Dcache-load-misses
L1_cache_misses = c(
  134602227, # Estática + Naive
  147758328, # Dinâmica + Naive
  8670594,   # Estática + Interchange
  9068203    # Dinâmica + Interchange
)

# -----------------------------
# Adiciona resultados ao plano
# -----------------------------
plan.loads  <- add.response(design = plan.person, response = L1_cache_loads)
plan.misses <- add.response(design = plan.person, response = L1_cache_misses)

summary(plan.loads)
summary(plan.misses)

# -----------------------------
# Gráficos
# -----------------------------
# Gráfico de efeitos principais para L1-Dcache-loads
png("MEPlot_loads.png", width = 800, height = 600)
MEPlot(plan.loads)
dev.off()

# Gráfico de efeitos principais para L1-Dcache-load-misses
png("MEPlot_misses.png", width = 800, height = 600)
MEPlot(plan.misses)
dev.off()

# Gráfico de interação para L1-Dcache-loads
png("IAPlot_loads.png", width = 800, height = 600)
IAPlot(plan.loads)
dev.off()

# Gráfico de interação para L1-Dcache-load-misses
png("IAPlot_misses.png", width = 800, height = 600)
IAPlot(plan.misses)
dev.off()


# -----------------------------
# Modelos lineares e ANOVA
# -----------------------------
plan.formula_loads  <- lm(plan.loads$L1_cache_loads~(plan.loads$Alocacao*plan.loads$Metodo))
plan.formula_misses <- lm(plan.misses$L1_cache_misses~(plan.misses$Alocacao*plan.misses$Metodo))

# A tabela fornecida na linha abaixo diz na coluna "Estimate" os valores de q0 (média), qA (Alocacao1), qB (Metodo1) e qAB (Alocacao e Metodo)
summary(plan.formula_loads)
summary(plan.formula_misses)

# Cálculo das Somas dos Quadrados
plan.anova_loads  <- anova(plan.formula_loads)
plan.anova_misses <- anova(plan.formula_misses)

# Valores das médias dos quadrados podem ser observados na coluna "Mean Sq"
summary(plan.anova_loads$`Mean Sq`)
summary(plan.anova_misses$`Mean Sq`)


# Soma dos quadrados de cada fator
SS.loads  <- plan.anova_loads$"Sum Sq"[1:3]
SST.loads <- sum(SS.loads)

Influencia.loads <- (SS.loads / SST.loads) * 100
Influencia.loads

SS.misses  <- plan.anova_misses$"Sum Sq"[1:3]
SST.misses <- sum(SS.misses)

Influencia.misses <- (SS.misses / SST.misses) * 100
Influencia.misses

