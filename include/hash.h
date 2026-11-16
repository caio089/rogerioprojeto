#ifndef HASH_H
#define HASH_H
#include "model.h"
typedef struct Hash Hash;
Hash *hash_criar(int capacidade);
int hash_inserir(Hash *h,Livro livro);
Livro *hash_buscar(Hash *h,int codigo);
void hash_liberar(Hash *h);
#endif
