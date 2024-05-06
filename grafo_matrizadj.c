#include "grafo_matrizadj.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
/*nv é numero de vertices*/

bool inicializaGrafo(Grafo* grafo, int nv){
    if(nv< 1){
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

void insereAresta(Grafo* grafo, int v1, int v2, Peso peso){
		if (!verticeValido(grafo, v1) && !verticeValido(grafo, v2)) return;
		grafo->mat[v1][v2] = peso;
        grafo->mat[v2][v1] = peso;
    
		grafo->numArestas++;
		return;
 }

bool existeAresta(Grafo* grafo, int v1, int v2){
	if(!verticeValido(grafo, v1) || !verticeValido(grafo, v2))
		return false;
	
	else return true;
 }

bool removeAresta(Grafo* grafo, int v1, int v2, Peso* peso){
    if(grafo->mat[v1][v2] == AN)
        return false;

    (*peso) = grafo->mat[v1][v2];
   grafo->mat[v1][v2] = AN;
   grafo->mat[v2][v1] = AN;
   grafo->numArestas--;

   return true;
}

bool listaAdjVazia(Grafo* grafo, int v){
   for(int i = 0; i < grafo->numVertices; i++){
     if(grafo->mat[v][i] != AN) return false;
   }
   return true;
}

Apontador primeiroListaAdj(Grafo* grafo, int vert){
    for(int i = 0; i < grafo->numVertices; i++){
        if(grafo->mat[vert][i] != AN)
            return i;
    }
    
    return VERTICE_INVALIDO;
}
 
Apontador proxListaAdj(Grafo* grafo, int vert, Apontador atual){
    for(int i = atual + 1; i < grafo->numVertices; i++){
        if(grafo->mat[vert][i] != AN)
            return i;
    }

    return VERTICE_INVALIDO;
}

void imprimeGrafo(Grafo* grafo){
    printf("  ");
    for (int i = 0; i < grafo->numVertices; i++) {
        printf("%i ", i);
    }
    printf("\n  ");
    for (int i = 0; i < grafo->numVertices; i++) {
        printf("--");
    }
    printf("\n");
    for (int i = 0; i < grafo->numVertices; i++) {
        printf("%i|", i);
        for(int j = 0; j < grafo->numVertices; j++) {
            Peso p = grafo->mat[i][j];
            if (p != AN) {
                printf("%i ", p);
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

int verticeDestino(Apontador ap) {
    return ap;
}

bool apValido(Apontador ap) {
    return ap >= 0;
}

void liberaGrafo(Grafo* grafo){}



