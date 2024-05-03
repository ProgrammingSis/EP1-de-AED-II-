#define AN -1 //aresta nula (ausência e aresta)
#define VERTICE_INVALIDO -1
typedef int Peso;

typedef struct str_aresta{
  int vdest;
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
void insereARESTA(int v1, int v2, Peso peso, Grafo* grafo);
bool existeAresta(int v1, int v2, Grafo* grafo);
void removeAresta(int v1, int v2, Peso peso, Grafo* grafo);
bool listADJVazia(int v, Grafo* grafo);
int primeiroListaAdj(int v, Grafo* grafo);
int proxListaAdj(int v, Grafo grafo, int prox);
void imprimeGrafo(Grafo* grafo);
void liberaGrafo(Grafo* grafo);