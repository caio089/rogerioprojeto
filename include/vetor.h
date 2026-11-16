#ifndef VETOR_H
#define VETOR_H
#include "model.h"
typedef struct {Livro *dados;int n,cap;} Vetor;
void vetor_iniciar(Vetor*v,int cap);
int vetor_adicionar(Vetor*v,Livro l);
void vetor_ordenar(Vetor*v);
int vetor_inserir_ordenado(Vetor*v,Livro l);
Livro*vetor_buscar_linear(Vetor*v,int codigo);
void vetor_liberar(Vetor*v);
#endif
