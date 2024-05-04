#include <stdbool.h>

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
void insereARESTA(int v1, int v2, Peso peso, Grafo* grafo);
bool existeAresta(int v1, int v2, Grafo* grafo);
void removeAresta(int v1, int v2, Peso peso, Grafo* grafo);
bool listADJVazia(int v, Grafo* grafo);
Apontador primeiroListaAdj(int v, Grafo* grafo);
Apontador proxListaAdj(int v, Grafo grafo, int prox);
void imprimeGrafo(Grafo* grafo);
void liberaGrafo(Grafo* grafo);