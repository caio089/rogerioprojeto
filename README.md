# Biblioteca — 3ª Avaliação de Estrutura de Dados

**UNIFSA · Turma 28M4A · 2026.2 · Prof. Rogério de Lima Sousa**

Projeto didático em **C11**, com TADs autorais (`.h`/`.c`) e cinco demandas. **Não utiliza bibliotecas de estruturas** nem `qsort`.

| Demanda | Solução | Comparação experimental |
|---|---|---|
| D1 — localizar livro pelo código | tabela hash, encadeamento separado | busca linear em vetor |
| D2 — acervo ordenado por título | vetor + mergesort sob demanda | vetor com inserção sempre ordenada |
| D3 — reservas FIFO | fila encadeada, chegada em ordem | vetor removendo do início (deslocamentos) |
| D4 — desfazer/refazer empréstimos | duas pilhas encadeadas, estados antes/depois | duas pilhas implementadas sobre vetores |
| D5 — campi até duas transferências | grafo por lista de adjacência + BFS | matriz de adjacência + BFS |

## Compilação

```bash
make
./biblioteca
make test
```

Requer GCC/Clang e Make. O benchmark gera `results/medicoes.csv` (microsegundos, média sobre repetições). `make clean` remove binários. Para maior reprodutibilidade, use a mesma máquina e compilação `-O2`.

## Arquitetura e regras

- `include/` — interfaces dos TADs; `src/` — implementações e programas.
- D1: código exclusivo, hash com baldes e colisões por lista encadeada.
- D2: ordenação por título e desempate por código; mergesort estável O(n log n) e inserção ordenada O(n).
- D3: reservas em ordem de chegada, **não por urgência**. Fila FIFO mantém empates de chegada naturalmente.
- D4: `Acao` captura estados anterior/posterior, duas pilhas LIFO; nova alteração limpa histórico de refazer. Para simplicidade, só operações empréstimo/devolução são reversíveis.
- D5: grafo não direcionado de campi; BFS contabiliza campi distintos alcançáveis com distância 1 ou 2. Grafo do menu tem seis campi fictícios.
- **Limitação intencional:** o menu é uma demonstração pequena; os registros de teste são sintéticos e não há persistência em disco. A listagem exibe o título de cadastro, enquanto o estado do empréstimo é consultado na hash.

## Metodologia de testes

Gerador determinístico xorshift32 com semente **2026**. Volumes 100, 1.000 e 10.000, entradas `aleatoria`, `ordenada` e `quase_ordenada`. Cada medida mede um lote completo de operações repetido diversas vezes com `clock()`; há *checksum* volátil para impedir descarte de buscas pelo otimizador. As variantes usam o mesmo conjunto de dados e as consultas são verificadas; tempos dependem de CPU, compilador e carga. A granularidade de `clock()` e alocação tornam resultados pequenos ruidosos.

`results/medicoes.csv` é resultado da execução local, e o relatório em `docs/relatorio.pdf` contextualiza desempenho e complexidade. **Não use métricas de uma máquina como garantia universal.**

## Como explicar ao professor

A escolha de estrutura depende do custo da operação dominante: hashing para localizar; ordenar uma vez quando as listagens são ocasionais; FIFO para ordem de chegada; LIFO para desfazer; adjacência esparsa + BFS para transferências. Compare custos de tempo e memória e aponte casos piores da hash (colisões) e do vetor ordenado (deslocamentos).
