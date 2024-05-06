#include <stdio.h>
#include <stdbool.h>
#include "grafo_matrizadj.h"
/*nv é numero de vertices*/

 inicializaGrafo(Grafo* grafo, int nv){
  if(nv<= 1){
    fprintf(stderr, "ERRO na chamada de inicializaGrafo: Numero de vertices maior que o maximo permitido de %d.\n", MAXNUMVERTICES);
    return false;
  }
  if (nv > MAXNUMVERTICES) {
    fprintf(stderr, "ERRO na chamada de inicializaGrafo: Numero de vertices maior que o maximo permitido de %d.\n", MAXNUMVERTICES);
    return false;
  }

  for(int i=0; i < grafo->numVertices; i++){
    for(int j=0; j < grafo->numVertices; j++){
      grafo->mat[i][j] = AN;
    }
  }

  grafo->numVertices = nv;
  grafo->numArestas = 0;
  return true;
}

bool verticeValido(Grafo * grafo, int vertice) {
  
  if (vertice <= 0) {
    fprintf(stderr, "ERRO: Numero do vértice (%d) deve ser >=0.", vertice);
    return false;
  }

  if (vertice > grafo->numVertices) {
    fprintf(stderr, "ERRO: Numero do vértice (%d) maior que o numero total de vértices (%d)", vertice, grafo->numVertices);
    return false;
  }

  return true;
}

 insereAresta(int v1, int v2, Peso peso, Grafo* grafo){
    if (!verticeValido(grafo, v1) && !verticeValido(grafo, v2)) return;
    grafo->mat[v1][v2] = peso;
    grafo->numArestas++;
    return;
 }

 existeAresta(int v1, int v2, Grafo* grafo){
  if(!verticeValido(grafo, v1) || !verticeValido(grafo, v2))
    return false;
  
  else return true;
 }
 removeAresta(int v1, int v2, Peso peso, Grafo* grafo){

 }

 listADJVazia(int v, Grafo* grafo){

 }
 primeiroListaAdj(int v, Grafo* grafo){
  return (grafo->mat[v]);

 }
 
 proxListaAdj(int v, Grafo grafo, int prox){
    if(listADJVazia(v, &grafo)) return VERTICE_INVALIDO;

    for(int i = 0; i < grafo.numVertices;i++){
      if(grafo.mat[v][i]!= AN) return i;
    }
    return VERTICE_INVALIDO;
 }

 imprimeGrafo(Grafo* grafo){

 }
 liberaGrafo(Grafo* grafo){

 }


