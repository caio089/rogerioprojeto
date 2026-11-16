#ifndef GRAFO_H
#define GRAFO_H
typedef struct Grafo Grafo;
Grafo*grafo_criar(int n);
int grafo_ligar(Grafo*g,int a,int b);
int grafo_distancia(Grafo*g,int origem,int destino);
int grafo_ate(Grafo*g,int origem,int max_passos);
void grafo_liberar(Grafo*g);
#endif
