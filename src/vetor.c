#include <stdlib.h>
#include <string.h>
#include "vetor.h"
static int cmp(const Livro*a,const Livro*b){int c=strcmp(a->titulo,b->titulo);return c?c:(a->codigo>b->codigo)-(a->codigo<b->codigo);}
static void merge(Livro*a,Livro*t,int lo,int mid,int hi){int i=lo,j=mid,k=lo;while(i<mid&&j<hi)t[k++]=cmp(&a[i],&a[j])<=0?a[i++]:a[j++];while(i<mid)t[k++]=a[i++];while(j<hi)t[k++]=a[j++];memcpy(a+lo,t+lo,(size_t)(hi-lo)*sizeof(Livro));}
static void ordenar(Livro*a,Livro*t,int lo,int hi){if(hi-lo<2)return;int mid=lo+(hi-lo)/2;ordenar(a,t,lo,mid);ordenar(a,t,mid,hi);merge(a,t,lo,mid,hi);}
void vetor_iniciar(Vetor*v,int cap){v->n=0;v->cap=cap>0?cap:1;v->dados=malloc((size_t)v->cap*sizeof(Livro));}
static int espaco(Vetor*v){if(!v->dados)return 0;if(v->n<v->cap)return 1;int c=v->cap*2;Livro*t=realloc(v->dados,(size_t)c*sizeof(Livro));if(!t)return 0;v->dados=t;v->cap=c;return 1;}
int vetor_adicionar(Vetor*v,Livro l){if(!espaco(v))return 0;v->dados[v->n++]=l;return 1;}
void vetor_ordenar(Vetor*v){if(v->n<2)return;Livro*t=malloc((size_t)v->n*sizeof(Livro));if(!t)return;ordenar(v->dados,t,0,v->n);free(t);}
int vetor_inserir_ordenado(Vetor*v,Livro l){if(!espaco(v))return 0;int lo=0,hi=v->n;while(lo<hi){int mid=lo+(hi-lo)/2;if(cmp(&v->dados[mid],&l)<=0)lo=mid+1;else hi=mid;}memmove(v->dados+lo+1,v->dados+lo,(size_t)(v->n-lo)*sizeof(Livro));v->dados[lo]=l;v->n++;return 1;}
Livro*vetor_buscar_linear(Vetor*v,int codigo){for(int i=0;i<v->n;i++)if(v->dados[i].codigo==codigo)return &v->dados[i];return NULL;}
void vetor_liberar(Vetor*v){free(v->dados);v->dados=NULL;v->n=v->cap=0;}
