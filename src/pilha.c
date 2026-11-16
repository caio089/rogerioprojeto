#include <stdlib.h>
#include "pilha.h"
typedef struct No {Acao a;struct No*prox;} No;
struct Pilha{No*topo;};
Pilha*pilha_criar(void){return calloc(1,sizeof(Pilha));}
int pilha_empilhar(Pilha*p,Acao a){if(!p)return 0;No*n=malloc(sizeof(*n));if(!n)return 0;n->a=a;n->prox=p->topo;p->topo=n;return 1;}
int pilha_desempilhar(Pilha*p,Acao*a){if(!p||!p->topo)return 0;No*n=p->topo;*a=n->a;p->topo=n->prox;free(n);return 1;}
void pilha_limpar(Pilha*p){Acao a;while(pilha_desempilhar(p,&a)){} }
void pilha_liberar(Pilha*p){if(!p)return;pilha_limpar(p);free(p);}
