#include <stdlib.h>
#include "hash.h"
typedef struct No { Livro livro; struct No *prox; } No;
struct Hash { int cap; No **baldes; };
static unsigned indice(int chave,int cap){ return ((unsigned)chave*2654435761u)%(unsigned)cap; }
Hash *hash_criar(int cap){ if(cap<1)return NULL; Hash*h=calloc(1,sizeof(*h)); if(!h)return NULL;h->baldes=calloc((size_t)cap,sizeof(No*));if(!h->baldes){free(h);return NULL;}h->cap=cap;return h; }
int hash_inserir(Hash*h,Livro v){ if(!h)return 0;unsigned i=indice(v.codigo,h->cap);for(No*n=h->baldes[i];n;n=n->prox)if(n->livro.codigo==v.codigo){n->livro=v;return 1;}No*n=malloc(sizeof(*n));if(!n)return 0;n->livro=v;n->prox=h->baldes[i];h->baldes[i]=n;return 1; }
Livro*hash_buscar(Hash*h,int c){if(!h)return NULL;for(No*n=h->baldes[indice(c,h->cap)];n;n=n->prox)if(n->livro.codigo==c)return &n->livro;return NULL;}
void hash_liberar(Hash*h){if(!h)return;for(int i=0;i<h->cap;i++){No*n=h->baldes[i];while(n){No*t=n->prox;free(n);n=t;}}free(h->baldes);free(h);}
