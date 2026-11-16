#ifndef PILHA_H
#define PILHA_H
#include "model.h"
typedef struct {Livro anterior,posterior;int tipo;} Acao;
typedef struct Pilha Pilha;
Pilha*pilha_criar(void);
int pilha_empilhar(Pilha*p,Acao a);
int pilha_desempilhar(Pilha*p,Acao*a);
void pilha_limpar(Pilha*p);
void pilha_liberar(Pilha*p);
#endif
