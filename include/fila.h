#ifndef FILA_H
#define FILA_H
typedef struct Fila Fila;
Fila*fila_criar(void);
int fila_entrar(Fila*f,int codigo);
int fila_sair(Fila*f,int *codigo);
void fila_liberar(Fila*f);
#endif
