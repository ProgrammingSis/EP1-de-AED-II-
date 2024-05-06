#include <stdbool.h>
#include <stdio.h>

//typedef int bool; IS THIS NECESSARY include bool

/*ESSA PARTE ACIMA É UMA GAMBIARRA PORQUE NÃO CONSEGUI COLOCAR O INCLUDE DE STDBOOL*/

#define MAXNUMVERTICES 100
#define AN -1 //aresta nula (ausência e aresta)
#define VERTICE_INVALIDO -1
typedef int Peso;
typedef int Apontador;

typedef struct{
  Peso mat[MAXNUMVERTICES][MAXNUMVERTICES]; /*ou bool, mas n consigo colocar o include aqui*/
  int numVertices;
  int numArestas;
} Grafo;

bool inicializaGrafo(Grafo* grafo, int nv);
void insereAresta(Grafo* grafo, int v1, int v2, Peso peso);
bool existeAresta(Grafo* grafo, int v1, int v2);
Apontador primeiroListaAdj(Grafo* grafo, int v);
Apontador proxListaAdj(Grafo* grafo, int vert, Apontador atual);
bool removeAresta(Grafo* grafo, int v1, int v2, Peso* peso);
bool listaAdjVazia(Grafo* grafo, int v);
void imprimeGrafo(Grafo* grafo);
void liberaGrafo(Grafo* grafo);
int verticeDestino(Apontador ap);
bool apValido(Apontador ap);