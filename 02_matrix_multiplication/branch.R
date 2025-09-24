library(FrF2)

# Planejamento de experimentos: 2 alocações × 2 métodos (Naive e Loop Tiling)
plan.person <- FrF2(
  nruns = 4, # 2 alocações × 2 métodos
  nfactors = 2,
  factor.names = list(
    Alocacao = c("Estática", "Dinâmica"),
    Metodo   = c("Naive", "Tiling")
  ),
  replications = 1,   # médias
  randomize = FALSE
)

summary(plan.person)

# -----------------------------
# Vetores de respostas (médias)
# -----------------------------
# branch-instructions
branch_instructions = c(
  145540712, # Estática + Naive
  145349137, # Dinâmica + Naive
  157621904, # Estática + Tiling
  157427863  # Dinâmica + Tiling
)

# branch-misses
branch_misses = c(
  303657, # Estática + Naive
  318822, # Dinâmica + Naive
  176575, # Estática + Tiling
  207042  # Dinâmica + Tiling
)

# -----------------------------
# Adiciona resultados ao plano
# -----------------------------
plan.instructions <- add.response(design = plan.person, response = branch_instructions)
plan.misses_branch <- add.response(design = plan.person, response = branch_misses)

summary(plan.instructions)
summary(plan.misses_branch)

# -----------------------------
# Gráficos
# -----------------------------
# Gráfico de efeitos principais
png("MEPlot_instructions.png", width = 800, height = 600)
MEPlot(plan.instructions)
dev.off()

png("MEPlot_misses_branch.png", width = 800, height = 600)
MEPlot(plan.misses_branch)
dev.off()

# Gráfico de interação
png("IAPlot_instructions.png", width = 800, height = 600)
IAPlot(plan.instructions)
dev.off()

png("IAPlot_misses_branch.png", width = 800, height = 600)
IAPlot(plan.misses_branch)
dev.off()

# -----------------------------
# Modelos lineares e ANOVA
# -----------------------------
plan.formula_instructions <- lm(plan.instructions$branch_instructions ~
                                  (plan.instructions$Alocacao * plan.instructions$Metodo))
plan.formula_misses_branch <- lm(plan.misses_branch$branch_misses ~
                                   (plan.misses_branch$Alocacao * plan.misses_branch$Metodo))

summary(plan.formula_instructions)
summary(plan.formula_misses_branch)

# Cálculo das Somas dos Quadrados
plan.anova_instructions <- anova(plan.formula_instructions)
plan.anova_misses_branch <- anova(plan.formula_misses_branch)

# Soma dos quadrados de cada fator
SS.instructions  <- plan.anova_instructions$"Sum Sq"[1:3]
SST.instructions <- sum(SS.instructions)

Influencia.instructions <- (SS.instructions / SST.instructions) * 100
Influencia.instructions

SS.misses_branch  <- plan.anova_misses_branch$"Sum Sq"[1:3]
SST.misses_branch <- sum(SS.misses_branch)

Influencia.misses_branch <- (SS.misses_branch / SST.misses_branch) * 100
Influencia.misses_branch
