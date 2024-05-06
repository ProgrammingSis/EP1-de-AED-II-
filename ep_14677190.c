#ifdef MATRIZ
#include "grafo_matrizadj.h"
#else
#include "grafo_listaadj.h"
#endif

#include <stdio.h>
#include <assert.h> /*tá no ep do andré, retirar, please*/
#define MAXNUMVERTICES 100

typedef struct a {
	int item;
	struct a* prox;
	struct a* ant;
} NoFila;

typedef struct b{
	NoFila* fim;
	NoFila* inicio;
	int tam;
} Fila;

void inicializaFila(Fila* fila) {
	fila->inicio = NULL;
	fila->fim = NULL;
	fila->tam = 0;
}

void liberaFila(Fila* fila) {
	NoFila* p = fila->inicio;
	while(p) {
		NoFila* prox = p->prox;
		free(p);
		p = prox;
	}
}

// Insere um item no fim da fila
void insereFila(Fila* fila, int item) {
	//criando um novo endereço de fila
	NoFila* novo = (NoFila*)malloc(sizeof(NoFila));
	novo->item = item;
	novo->prox = NULL;

	if (fila->tam == 0) {
		//caso de fila vazia
		fila->inicio = novo;
		fila->fim = novo;	

		fila->tam++;		
	} else {
		//caso de com pelo menos um elemento (geral)
		fila->fim->prox = novo;	
		fila->fim = novo;
		fila->tam++;
	}
	
}

// Retira um item do início da fila
int retiraFila(Fila* fila) {
	// Garante que há itens ainda na fila para serem retirados
	assert(fila->tam != 0);

	// Adquire o início da fila e o move para trás
	NoFila* no = fila->inicio;
	fila->inicio = no->prox;

	// Adquire o item do nó e o libera
	fila->tam--;
	int item = no->item;
	free(no);
	return item;
}


struct BuscaType {
	// -- Parâmetros da busca --

	// Grafo alvo da busca
	Grafo* grafo;

	// Acessos da busca. Cada acesso permite observar o estado eventos durante a execução da busca
	// e opcionalmente alterar o seu rumo
	Acessos acessos;

	// Vértice início da busca. Por padrão possui valor -1, mas se configurado, a busca irá
	// explorar apenas o início
	int inicio;

	// Objeto do usuário. Não será alterado ou acessado pelo mecanismo de busca.
	void* objeto;
	
	// -- Estado da busca e resultados --

	// Relógio do algoritmo de busca
	int tempo;

	// Vetor de cores de todos os vértices do grafo
	BuscaCor* cor;

	// Vetor de tempo de descoberta dos vértices
	int* tempoDesc;

	// Vetor do tempo de término dos vértices
	int* tempoTerm;

	// Vetor de antecessores de cada vértice do grafo
	int* antecessor;

	// Vetor de distâncias de cada vértice em relação a raiz da árvore de busca
	int* distancia;
};
/* O arquivo Makefile NÃO deverá ser entregue

  Preciso de:

    * Entender o que vai no .c e o que vai no .h (prontooo)

    * Como colocar o include no .h, é no .h mesmo

    * Rotinas de buscas, etc (utilizando apenas as funções definidas na interface de grafos, ou seja, sem assumir explicitamente a estrutura por matriz ou lista de adjacência),

    * Main (está presente)

    * Aprender busca em largura

    * Aprender busca em profundidade

    * Aprender sobre vértices de articulação

    Como implementar 

    * Relembrar como se faz manipulação de arquivos
    *procurar como se faz para detectar um componente complexo num grafo    
*/



void visitaBP(int v, Grafo* grafo, bool* cor, int* tdesc, int* tterm, int* antecessor, int* tempo){
	cor[v]= true;
	tdesc[v]=++(*tempo);

	Apontador apontador;

	apontador = primeiroListaAdj(grafo, v);

	while(verticeValido(apontador)){
		int adjacente= verticeDestino(apontador);
		if(cor[adjacente]==false){
			antecessor[adjacente]=v;
            visitaBP(adjacente, grafo, cor, tdesc, tterm, antecessor,tempo);
		}
		apontador= proxListaAdj(grafo, v, apontador);
	}
	tterm[v]=++(*tempo);
}



void buscaEmProfundidade(Grafo* grafo){
	bool cor[MAXNUMVERTICES]=false;
	int tdesc[MAXNUMVERTICES]=0;
	int tterm[MAXNUMVERTICES]=0;
	int antecessor[MAXNUMVERTICES]=-1;
	int tempo= 0;

	for(int v=0; v<grafo->numVertices; v++){
		if(!cor[v]){
			visitaBP(v, grafo, cor, tdesc, tterm, antecessor, tempo);
		}
	}
}

int main(int arg c, argv**){

}