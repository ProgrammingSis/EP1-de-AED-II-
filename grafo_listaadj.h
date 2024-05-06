#define AN -1 //aresta nula (ausência e aresta)
#define VERTICE_INVALIDO -1
typedef int Peso;
#include <stdbool.h>

typedef struct str_aresta{
  int verticeIndice;
  Peso peso;
  struct str_aresta* prox;
} Aresta;

typedef Aresta* Apontador;

typedef struct{
  Apontador* listaAdj;
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