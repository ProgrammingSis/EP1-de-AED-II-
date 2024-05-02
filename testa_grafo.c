#include <stdio.h>
#include <stdbool.h>

#define MAXNUMVERTICES 100
#define AN -1 //aresta nula (ausência e aresta)
#define VERTICEINVALIDO -1

typedef int Peso;

typedef struct a{
  int vdest;
  struct a* prox;
} Aresta;

typedef struct b{
  Peso mat[MAXNUMVERTICES][MAXNUMVERTICES];
  int numVertices;
  int numArestas;
} Grafo;

int main(){

}