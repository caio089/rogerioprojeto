CC = gcc
CFLAGS = -O2 -std=c11 -Wall -Wextra -pedantic -Iinclude
SRC = src/hash.c src/vetor.c src/fila.c src/pilha.c src/grafo.c
all: biblioteca benchmark
biblioteca: src/main.c $(SRC)
	$(CC) $(CFLAGS) $^ -o $@
benchmark: src/benchmark.c $(SRC)
	$(CC) $(CFLAGS) $^ -o $@
test: all
	./benchmark > results/medicoes.csv
clean:
	rm -f biblioteca benchmark
.PHONY: all test clean
