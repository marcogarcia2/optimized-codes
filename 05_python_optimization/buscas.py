from collections import deque
import heapq
from math import radians, sin, cos, sqrt, atan2

# BUSCA NÃO INFORMADA: BREADTH-FIRST SEARCH
def bfs(grafo, origem, destinos):
    # Conjunto para armazenar nós já visitados, evitando ciclos
    visitado = set()
    
    # Fila FIFO (First In First Out) para gerenciar a ordem de exploração
    # Cada elemento da fila é uma tupla (nó_atual, caminho_até_nó)
    fila = deque([(origem, [origem])])

    while fila:
        # Remove o primeiro elemento da fila (FIFO)
        atual, caminho = fila.popleft()
        
        # Se o nó já foi visitado, pula para o próximo
        if atual in visitado:
            continue
            
        # Marca o nó atual como visitado
        visitado.add(atual)

        # Se encontramos um destino, retorna o caminho
        if atual in destinos:
            return caminho

        # Explora todos os vizinhos do nó atual
        for vizinho in grafo.neighbors(atual):
            if vizinho not in visitado:
                # Adiciona o vizinho na fila com o caminho atualizado
                fila.append((vizinho, caminho + [vizinho]))

    # Se a fila ficou vazia e não encontramos um destino
    return None

## --- ## --- ## --- ## --- ## --- ## --- ## --- ## --- ##

# BUSCA INFORMADA: A-ESTRELA

# Heurística não-otimizada
def __haversine(n1, n2, grafo):

    R = 6371000  # Raio da Terra em metros
    lat1, lon1 = radians(grafo.nodes[n1]['y']), radians(grafo.nodes[n1]['x'])
    lat2, lon2 = radians(grafo.nodes[n2]['y']), radians(grafo.nodes[n2]['x'])

    dlat = lat2 - lat1
    dlon = lon2 - lon1

    a = sin(dlat / 2)**2 + cos(lat1) * cos(lat2) * sin(dlon / 2)**2
    c = 2 * atan2(sqrt(a), sqrt(1 - a))
    return R * c

# A* não otimizado
def a_estrela(grafo, origem, destinos):

    destinos = set(destinos)
    fila = []

    # Inicializa a fila de prioridade com o nó origem
    # f(n) = g(n) + h(n) → custo atual + heurística (distância estimada até o destino mais próximo)
    heapq.heappush(
        fila, 
        (0 + min(__haversine(origem, d, grafo) for d in destinos), 0, origem, [origem])
    )

    # g(n): custo real acumulado até cada nó
    custo_ate_agora = {origem: 0}

    while fila:
        f, g, atual, caminho = heapq.heappop(fila)

        if atual in destinos:
            return caminho

        for vizinho in grafo.neighbors(atual):
            # Calcula o custo da aresta entre atual e vizinho
            if grafo.is_multigraph():
                arestas = grafo[atual][vizinho]  # Pega as múltiplas arestas entre os nós
                custo = min(attr.get('length', 0) for attr in arestas.values())
            else:
                custo = grafo[atual][vizinho].get('length', 0)

            novo_g = g + custo  # g(n) atualizado

            # Só atualiza se for a primeira vez ou se o novo caminho for melhor
            if vizinho not in custo_ate_agora or novo_g < custo_ate_agora[vizinho]:
                custo_ate_agora[vizinho] = novo_g
                h = min(__haversine(vizinho, d, grafo) for d in destinos)  # h(n): heurística até o destino mais próximo
                f_novo = novo_g + h
                heapq.heappush(fila, (f_novo, novo_g, vizinho, caminho + [vizinho]))

    raise ValueError("Nenhum caminho encontrado para os destinos fornecidos.")


## --- ## --- ## --- ## --- ## --- ## --- ## --- ## --- ##

# # BUSCA INFORMADA: A* OTIMIZADO
import functools

__GRAPH_REGISTRY = {}

def register_graph(grafo):
    # registra o grafo e retorna um id para uso no cache
    gid = id(grafo)
    __GRAPH_REGISTRY[gid] = grafo
    return gid

@functools.lru_cache(maxsize=None)
def __haversine_cached(n1, n2, grafo_id):
    # distância geodésica cacheada
    grafo = __GRAPH_REGISTRY[grafo_id]
    R = 6371000
    lat1, lon1 = radians(grafo.nodes[n1]['y']), radians(grafo.nodes[n1]['x'])
    lat2, lon2 = radians(grafo.nodes[n2]['y']), radians(grafo.nodes[n2]['x'])
    dlat, dlon = lat2 - lat1, lon2 - lon1
    a = sin(dlat / 2)**2 + cos(lat1) * cos(lat2) * sin(dlon / 2)**2
    c = 2 * atan2(sqrt(a), sqrt(1 - a))
    return R * c

def optimized_a_estrela(grafo, origem, destinos):
    destinos = set(destinos)
    gid = register_graph(grafo)

    is_multi = grafo.is_multigraph()
    heur_cache = {}  # cache leve local: heurística mínima até um destino

    def heuristica(n):
        # calcula e memoriza a heurística mínima até qualquer destino
        if n not in heur_cache:
            heur_cache[n] = min(__haversine_cached(n, d, gid) for d in destinos)
        return heur_cache[n]

    fila = [(heuristica(origem), 0, origem)]
    pais = {origem: None}
    custo_ate_agora = {origem: 0}

    while fila:
        f, g, atual = heapq.heappop(fila)
        if atual in destinos:
            return reconstruir_caminho(pais, atual)

        vizinhos = grafo[atual]  # acesso local mais rápido
        for vizinho, dados in vizinhos.items():
            if is_multi:
                custo = min(attr.get('length', 0) for attr in dados.values())
            else:
                custo = dados.get('length', 0)

            novo_g = g + custo
            if vizinho not in custo_ate_agora or novo_g < custo_ate_agora[vizinho]:
                custo_ate_agora[vizinho] = novo_g
                pais[vizinho] = atual
                f_novo = novo_g + heuristica(vizinho)
                heapq.heappush(fila, (f_novo, novo_g, vizinho))

    return None

def reconstruir_caminho(pais, destino):
    caminho = []
    while destino is not None:
        caminho.append(destino)
        destino = pais[destino]
    return list(reversed(caminho))
