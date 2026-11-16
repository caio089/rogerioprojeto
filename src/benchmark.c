#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "hash.h"
#include "vetor.h"
#include "fila.h"
#include "pilha.h"
#include "grafo.h"
static volatile unsigned long long sink=0;
static uint32_t seed=2026;
static uint32_t rnd(void){seed^=seed<<13;seed^=seed>>17;seed^=seed<<5;return seed;}
static void preparar(int *a,int n,int modo){for(int i=0;i<n;i++)a[i]=i; if(modo==0){for(int i=n-1;i>0;i--){int j=(int)(rnd()%(unsigned)(i+1));int t=a[i];a[i]=a[j];a[j]=t;}}else if(modo==2){for(int k=0;k<n/100+1;k++){int i=(int)(rnd()%(unsigned)n),j=(int)(rnd()%(unsigned)n);int t=a[i];a[i]=a[j];a[j]=t;}}}
static Livro livro(int x){Livro l; l.codigo=x+1;snprintf(l.titulo,sizeof(l.titulo),"Titulo%06d",x);l.emprestado=0;return l;}
static double us(clock_t inicio){return 1000000.0*(clock()-inicio)/CLOCKS_PER_SEC;}
static void out(const char*d,const char*tipo,int n,const char*m,double tempo,int operacoes){printf("%s,%s,%d,%s,%.3f,%d\n",d,tipo,n,m,tempo,operacoes);}
static void d1(int *a,int n,const char *m){Vetor v;vetor_iniciar(&v,n);Hash*h=hash_criar(n*2+1);for(int i=0;i<n;i++){Livro l=livro(a[i]);vetor_adicionar(&v,l);hash_inserir(h,l);}int reps=n==100?300:n==1000?60:6;clock_t t=clock();for(int r=0;r<reps;r++)for(int i=0;i<n;i++){Livro*p=hash_buscar(h,a[i]+1);sink+=(unsigned)(p?p->codigo:0);}out("D1","hash",n,m,us(t)/(reps*n),reps*n);t=clock();for(int r=0;r<reps;r++)for(int i=0;i<n;i++){Livro*p=vetor_buscar_linear(&v,a[i]+1);sink+=(unsigned)(p?p->codigo:0);}out("D1","linear",n,m,us(t)/(reps*n),reps*n);hash_liberar(h);vetor_liberar(&v);}
static void d2(int *a,int n,const char*m){Vetor v;vetor_iniciar(&v,n);clock_t t=clock();for(int i=0;i<n;i++)vetor_adicionar(&v,livro(a[i]));vetor_ordenar(&v);sink+=v.dados[n/2].codigo;out("D2","ordenar_ao_listar",n,m,us(t),n);vetor_liberar(&v);vetor_iniciar(&v,n);t=clock();for(int i=0;i<n;i++)vetor_inserir_ordenado(&v,livro(a[i]));sink+=v.dados[n/2].codigo;out("D2","insercao_ordenada",n,m,us(t),n);vetor_liberar(&v);}
static void d3(int *a,int n,const char*m){clock_t t=clock();Fila*f=fila_criar();for(int i=0;i<n;i++)fila_entrar(f,a[i]);int x;for(int i=0;i<n;i++){fila_sair(f,&x);sink+=(unsigned)x;}out("D3","fila_encadeada",n,m,us(t),2*n);fila_liberar(f);int *v=malloc((size_t)n*sizeof(int));t=clock();for(int i=0;i<n;i++)v[i]=a[i];int tam=n;while(tam){x=v[0];sink+=(unsigned)x;memmove(v,v+1,(size_t)(--tam)*sizeof(int));}out("D3","vetor_deslocamento",n,m,us(t),2*n);free(v);}
static void d4(int*a,int n,const char*m){clock_t t=clock();Pilha*p=pilha_criar(),*redo=pilha_criar();Acao x;memset(&x,0,sizeof(x));for(int i=0;i<n;i++){x.anterior.codigo=a[i];x.posterior.codigo=a[i];pilha_empilhar(p,x);}for(int i=0;i<n;i++){pilha_desempilhar(p,&x);sink+=(unsigned)x.anterior.codigo;pilha_empilhar(redo,x);}for(int i=0;i<n;i++){pilha_desempilhar(redo,&x);pilha_empilhar(p,x);}out("D4","duas_pilhas",n,m,us(t),4*n);pilha_liberar(p);pilha_liberar(redo);Acao*v=malloc((size_t)n*sizeof(Acao)),*r=malloc((size_t)n*sizeof(Acao));t=clock();int topo=0,redo_topo=0;for(int i=0;i<n;i++){x.anterior.codigo=a[i];v[topo++]=x;}while(topo){x=v[--topo];sink+=(unsigned)x.anterior.codigo;r[redo_topo++]=x;}while(redo_topo){x=r[--redo_topo];v[topo++]=x;}out("D4","duas_pilhas_vetor",n,m,us(t),4*n);free(v);free(r);}
static int bfs_matriz(unsigned char *mat,int n,int origem){int*q=malloc((size_t)n*sizeof(int));signed char *d=malloc((size_t)n);memset(d,-1,(size_t)n);int h=0,t=0,cont=0;q[t++]=origem;d[origem]=0;while(h<t){int u=q[h++];if(d[u]>0)cont++;if(d[u]==2)continue;for(int v=0;v<n;v++)if(mat[(size_t)u*n+v]&&d[v]<0){d[v]=d[u]+1;q[t++]=v;}}free(d);free(q);return cont;}
static void d5(int*a,int n,const char*m){Grafo*g=grafo_criar(n);unsigned char *mat=calloc((size_t)n*n,1);for(int i=0;i<n-1;i++){grafo_ligar(g,i,i+1);mat[(size_t)i*n+i+1]=mat[(size_t)(i+1)*n+i]=1;}for(int i=0;i<n/3;i++){int u=a[i],v=a[n-i-1];if(u!=v){grafo_ligar(g,u,v);mat[(size_t)u*n+v]=mat[(size_t)v*n+u]=1;}}int consultas=n==100?100:n==1000?25:5;clock_t t=clock();for(int i=0;i<consultas;i++)sink+=(unsigned)grafo_ate(g,a[i],2);out("D5","lista_adjacencia",n,m,us(t)/consultas,consultas);t=clock();for(int i=0;i<consultas;i++)sink+=(unsigned)bfs_matriz(mat,n,a[i]);out("D5","matriz_adjacencia",n,m,us(t)/consultas,consultas);free(mat);grafo_liberar(g);}
int main(void){puts("demanda,estrutura,n,entrada,tempo_us,operacoes");int tamanhos[]={100,1000,10000};const char*nomes[]={"aleatoria","ordenada","quase_ordenada"};for(int k=0;k<3;k++)for(int modo=0;modo<3;modo++){int n=tamanhos[k];seed=2026;int*a=malloc((size_t)n*sizeof(int));preparar(a,n,modo);d1(a,n,nomes[modo]);d2(a,n,nomes[modo]);d3(a,n,nomes[modo]);d4(a,n,nomes[modo]);d5(a,n,nomes[modo]);free(a);}fprintf(stderr,"checksum=%llu\n",sink);return 0;}
