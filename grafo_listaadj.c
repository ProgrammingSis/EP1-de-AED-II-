#include "grafo_listaadj.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

bool verticeValido(Grafo * grafo, int vertice);

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
	for(int i = 0; i< grafo->numVertices; i++){
		printf("Adjacentes de %i:\n", i);
		Apontador atual = grafo->listaAdj[i];
		while(atual != NULL){
			printf("  [%i: Peso %i ]\n", atual->verticeIndice, atual->peso);
			atual = atual->prox;
		}
	}
} 

Apontador proxListaAdj(Grafo* grafo, int v, Apontador atual) {
	if(atual == NULL) return NULL;
	/*n tá certo isso aqui*/
	return atual->prox;
}

/*V1 É O VERTICE DE ONDE SAI A ARESTA E V2 É O DESTINO DA ARESTA*/
void insereAresta(Grafo* grafo, int v1, int v2, Peso peso){

	if(v1==v2){/*NÃO TEM SELF LOOPS*/
		fprintf(stderr, "ERRO: NÃO HÁ SELF LOOPS EM GRAFOS NÃO DIRECIONADOS.");
	}

	// Cria Aresta A: V1 -> V2
	Apontador novaArestaA = (Aresta*) malloc(sizeof(Aresta));
	novaArestaA->verticeIndice = v2;
	novaArestaA->peso = peso;

	novaArestaA->prox = grafo->listaAdj[v1];
	grafo->listaAdj[v1] = novaArestaA;	
	
	// Cria Aresta A: V2 -> V1
	Apontador novaArestaB = (Aresta*) malloc(sizeof(Aresta));
	novaArestaB->verticeIndice = v1;
	novaArestaB->peso = peso;

	novaArestaB->prox = grafo->listaAdj[v2];
	grafo->listaAdj[v2] = novaArestaB;

	// Incrementamos o número de arestas em 1 pois o grafo é não direcionado
	grafo->numArestas++;
}

bool existeAresta(Grafo* grafo, int v1, int v2){
	 if (!verticeValido(grafo, v1) && !verticeValido(grafo, v2)) return false;

	 Apontador atual = grafo->listaAdj[v1];
	 while(atual){
		if(atual->verticeIndice == v2){
			return true;
		}

		atual = atual->prox;
	 }

	return false; 
}

bool removeArestaImpl(Grafo* grafo, int v1, int v2, Peso* peso) {
	// Busca a presença de V2 na lista de adjacência de V1,
	// vamos iterar a lista de adjacência de v1
	Aresta* ant = NULL;
	Aresta* aresta = grafo->listaAdj[v1];
	while (aresta) {
		if (aresta->verticeIndice != v2) {
			ant = aresta;
			aresta = aresta->prox;
			continue;
		}

		if (peso) *peso = aresta->peso;
		
		if (!ant) {
			grafo->listaAdj[v1] = aresta->prox;
		} else {
			ant->prox = aresta->prox;
		}

		free(aresta);
		return true;
	}

	// Passamos todo o laço, então não existia aresta entre v1 e v2
	return false;
}

bool removeAresta(Grafo* grafo, int v1, int v2, Peso* peso){
	// Verifica a validade dos vértices
	assert(verticeValido(grafo, v1));
	assert(verticeValido(grafo, v2));

	grafo->numArestas--;
		
	// Remove a aresta V2 -> V1
	removeArestaImpl(grafo, v2, v1, NULL);

	// Remove a aresta V1 -> V2
	return removeArestaImpl(grafo, v1, v2, peso);
 }
 
 bool listaAdjVazia(Grafo* grafo, int v){
	if(grafo->listaAdj[v] == NULL) return true;

	return false;
 }
 
Apontador primeiroListaAdj(Grafo* grafo, int v){
	return (grafo->listaAdj[v]);
 }
	
void liberaGrafo(Grafo* grafo){
	int vertice;
	Apontador aresta;

	for (vertice = 0; vertice <= grafo->numVertices; vertice++)
		while ((aresta = grafo->listaAdj[vertice]) != NULL) {
			grafo->listaAdj[vertice] = aresta->prox;
			aresta->prox = NULL;
			free(aresta);
		}

	grafo->numArestas = 0;
	free(grafo->listaAdj); // pois o vetor tb tem alocacao dinamica
	grafo->listaAdj = NULL;
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

bool apValido(Apontador ap){
	if(ap == NULL) 
		return false;
	else 
		return true;
}

int verticeDestino(Apontador ap){
	return ap->verticeIndice;
}