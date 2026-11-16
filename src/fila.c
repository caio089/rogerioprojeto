#include <stdlib.h>
#include "fila.h"
typedef struct No {int codigo;struct No*prox;} No;
struct Fila{No*ini,*fim;};
Fila*fila_criar(void){return calloc(1,sizeof(Fila));}
int fila_entrar(Fila*f,int c){if(!f)return 0;No*n=malloc(sizeof(*n));if(!n)return 0;n->codigo=c;n->prox=NULL;if(f->fim)f->fim->prox=n;else f->ini=n;f->fim=n;return 1;}
int fila_sair(Fila*f,int*c){if(!f||!f->ini)return 0;No*n=f->ini;*c=n->codigo;f->ini=n->prox;if(!f->ini)f->fim=NULL;free(n);return 1;}
void fila_liberar(Fila*f){if(!f)return;int v;while(fila_sair(f,&v)){}free(f);}
