#include "grafo_listaadj.h"
#include <stdio.h>
#include <stdbool.h>

/*o stdbool deveria estar aqui ou não. RESPOSTA: NÃO FAZ MAL*/
bool inicializaGrafo(Grafo* grafo, int numVertices) {
  if (grafo == NULL) {
    fprintf(stderr, "ERRO: inicializaGrafo() -- Grafo não pode ser nulo.\n");
    return false;
  }
  if (numVertices <= 0) {
    fprintf(stderr, "ERRO: inicializaGrafo() -- Vértices tem de ser positivos.\n");
    return false;
  }

  grafo->numArestas = 0;
  grafo->numVertices = numVertices;
  grafo->listaAdj = (Apontador*) calloc(numVertices, sizeof(Apontador));
  if (!grafo->listaAdj) {
    fprintf(stderr, "ERRO: inicializaGrafo() -- Alocação falhou.\n");
    return false;
  }
  return true;
}

void imprimeGrafo(Grafo* grafo){
  Apontador atual = grafo->listaAdj;
  
  for(int i = 0; i< grafo->numVertices; i++){
    while(atual != NULL){
      printf("[Vertice número %i: peso %i]  ", grafo->listaAdj[i]->verticeIndice, grafo->listaAdj[i]->peso);
    }
  }
} 

int obtemNrAresta(Grafo* grafo){
  return grafo->numVertices;
}

Apontador proxListaAdj(Grafo* grafo, int v, Apontador atual) {
  if(atual == NULL) return NULL;
  /*n tá certo isso aqui*/
  return atual->prox;
}

/*V1 É O VERTICE DE ONDE SAI A ARESTA E V2 É O DESTINO DA ARESTA*/
 insereARESTA(int v1, int v2, Peso peso, Grafo* grafo){

  if(v1==v2){/*NÃO TEM SELF LOOPS*/
    fprintf(stderr, "ERRO: NÃO HÁ SELF LOOPS EM GRAFOS NÃO DIRECIONADOS.");
  }

  Apontador verticeAtual = grafo->listaAdj[v1];
  
  while(verticeAtual){
  
    verticeAtual = verticeAtual->prox;

      if(verticeAtual == NULL){
        if(verticeAtual->prox = (Apontador) calloc(1,(sizeof(Apontador)))){
          fprinf(stderr, "ERRO: Vertice não foi alocado corretamente!");
        };
      break;
    }
  }
 
    grafo->numArestas++;
}

 existeAresta(int v1, int v2, Grafo* grafo){
   if (!verticeValido(grafo, v1) && !verticeValido(grafo, v2)) return false;

   Apontador atual = grafo->listaAdj[v1];
   while(atual){
    if(atual->verticeIndice == v2){
      return true;
    }

    atual = atual->prox;
   }
   if(!atual) return false;
   
 }

 removeAresta(int v1, int v2, Peso peso, Grafo* grafo){
    if(!existeAresta(v1, v2, grafo)){
      return false;
    }

 }
 listADJVazia(int v, Grafo* grafo){

 }
 
 primeiroListaAdj(int v, Grafo* grafo){
  return (grafo->listaAdj[v]);
 }

 liberaGrafo(Grafo* grafo){
  int vertice;
  Apontador aresta;

  for (vertice = 0; vertice <= grafo->numVertices; vertice++)
    while ((aresta = grafo->listaAdj[vertice]) != NULL) {
      grafo->listaAdj[vertice] = aresta->prox;
      aresta->prox = NULL;
      free(aresta);
    }

  grafo->numVertices = 0;
  free(grafo->listaAdj); // pois o vetor tb tem alocacao dinamica
  grafo->listaAdj = NULL;
 }