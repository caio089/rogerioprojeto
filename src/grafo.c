#include <stdlib.h>
#include "grafo.h"
typedef struct No{int v;struct No*prox;} No;
struct Grafo{int n;No**adj;};
Grafo*grafo_criar(int n){if(n<1)return NULL;Grafo*g=malloc(sizeof(*g));if(!g)return NULL;g->n=n;g->adj=calloc((size_t)n,sizeof(No*));if(!g->adj){free(g);return NULL;}return g;}
static int aresta(Grafo*g,int a,int b){No*n=malloc(sizeof(*n));if(!n)return 0;n->v=b;n->prox=g->adj[a];g->adj[a]=n;return 1;}
int grafo_ligar(Grafo*g,int a,int b){if(!g||a<0||b<0||a>=g->n||b>=g->n)return 0;return aresta(g,a,b)&&aresta(g,b,a);}
static int bfs(Grafo*g,int o,int d,int lim){if(!g||o<0||o>=g->n)return -1;int*q=malloc((size_t)g->n*sizeof(int));int*dist=malloc((size_t)g->n*sizeof(int));if(!q||!dist){free(q);free(dist);return -1;}for(int i=0;i<g->n;i++)dist[i]=-1;int h=0,t=0,cont=0;q[t++]=o;dist[o]=0;while(h<t){int u=q[h++];if(u==d){int r=dist[u];free(q);free(dist);return r;}if(dist[u]>0&&dist[u]<=lim)cont++;if(dist[u]==lim)continue;for(No*x=g->adj[u];x;x=x->prox)if(dist[x->v]<0){dist[x->v]=dist[u]+1;q[t++]=x->v;}}free(q);free(dist);return d<0?cont:-1;}
int grafo_distancia(Grafo*g,int o,int d){if(!g||d<0||d>=g->n)return -1;return bfs(g,o,d,g->n);}
int grafo_ate(Grafo*g,int o,int lim){return bfs(g,o,-1,lim);}
void grafo_liberar(Grafo*g){if(!g)return;for(int i=0;i<g->n;i++){No*x=g->adj[i];while(x){No*t=x->prox;free(x);x=t;}}free(g->adj);free(g);}
