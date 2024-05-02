#include "grafo_listaadj.h"
#include <stdio.h>
#include <stdbool.h>
/*o stdbool deveria estar aqui ou não*/
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
      printf("[Vertice número %i: peso %i]  ", grafo->listaAdj[i]->vdest, grafo->listaAdj[i]->peso);
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