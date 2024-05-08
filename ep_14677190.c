#ifdef MATRIZ
#include "grafo_matrizadj.h"
#else
#include "grafo_listaadj.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

const int INFINITO = 2147483647;

typedef enum {
	BRANCO, CINZA, PRETO
} Cor;

typedef struct {
	Cor* cor;
	int* tempoDescoberta;
	int* tempoFechamento;
	int* antecessor;	
	int* distancia;
} Busca;

void leGrafo(Grafo* grafo, char* arquivo);
void buscaProfundidade(Grafo* grafo);
void visitaProfundidade(Grafo* grafo, Busca busca, int* temp, int vert, int prof);

FILE* arquivoSaida = NULL;

int main(int argc, char* argv[]){
	Grafo grafo;
	Grafo* g = &grafo;

//	if (argc < 3) {
//		fprintf(stderr, "Argumentos insuficientes (%i).\n", argc);
//		return -1;
//}

	char* nomeArquivoEntrada = argv[1];
	char* nomeArquivoSaida = argv[2];

	nomeArquivoEntrada = "testes/entrada1.txt"; //desativar isso antes de entregar
	nomeArquivoSaida = "saida.txt";

	// colocar o parametro recebido no terminal aqui
	leGrafo(g, nomeArquivoEntrada);

	//inicializaGrafo(g, 9);
	
	imprimeGrafo(g);

	arquivoSaida = fopen(nomeArquivoSaida, "w");
	if (!arquivoSaida) {
		fprintf(stderr, "Falha ao abrir arquivo de saída '%s'\n", nomeArquivoSaida);
		return -1;
	}
	buscaProfundidade(g);

	return 0;
}

void leGrafo(Grafo* grafo, char* entrada) {
	FILE* arquivo = fopen(entrada, "r");
	if (!arquivo) {
		fprintf(stderr, "Falha ao abrir arquivo de entrada '%s'\n", entrada);
		exit(-1);
	}

	int numArestas, numVertices, v1, v2, peso;

	fscanf(arquivo, "%i %i", &numVertices, &numArestas);
	inicializaGrafo(grafo, numVertices);

	for(int i = 0; i < numArestas; i++){
		fscanf(arquivo, "%i %i %i", &v1, &v2, &peso);

		printf("Inserindo aresta %i -> %i, w: %i\n", v1, v2, peso);
		insereAresta(grafo, v1,  v2, peso);
	}
}

void imprimeCaminho(Busca busca, int vert){

	if(busca.antecessor[vert] != -1){
	imprimeCaminho(busca, busca.antecessor[vert]);
	}
	fprintf(arquivoSaida, "%i ", vert);
}

void buscaProfundidade(Grafo* grafo) {
	int numVertices = grafo->numVertices;
	
	// Inicializa o espaço de memória para cada vetor
	Cor cor[numVertices];
	int antecessor[numVertices];
	int distancia[numVertices];
	int tempoDesc[numVertices];
	int tempoFech[numVertices];

	// Contador global do tempo do algoritmo
	int tempo = 0;

	/*INICIALIZANDO AS VARIÁVEIS COM INFINITO NO CAMPO DISTÂNCIA, 
	SEM ANTECESSOR E COM COR BRANCA NO LOOP*/

	// Inicializa as propriedades dos vértices
	for (int v = 0; v < numVertices; v++) {
		cor[v] = BRANCO;
		antecessor[v] = -1;
		distancia[v] = INFINITO;
		tempoDesc[v] = 0;
		tempoFech[v] = 0;
 	}

	// Inicializa a estrutura de busca com o endereço de cada um dos vetores,
	// para facilitar a passagem dos parâmetros
	Busca busca;
	busca.antecessor = antecessor;
	busca.distancia = distancia;
	busca.cor = cor;
	busca.tempoDescoberta = tempoDesc;
	busca.tempoFechamento = tempoFech;

	// Começo da busca em profundidade
	printf("Busca em profundidade\n");

	fprintf(arquivoSaida, "BP:\n"); 

	// Para cada um dos vértices, executa uma busca em profundidade se ele não
	// foi descoberto ainda (for branco)
	for (int v = 0; v < numVertices; v++) {
		if (cor[v] == BRANCO) {
			busca.distancia[v] = 0;
			visitaProfundidade(grafo, busca, &tempo, v, 0);
		}
	}	
	 fprintf(arquivoSaida, "\n\nCaminhos BP:\n");
	for(int i = 0; i < grafo->numVertices; i++){
		imprimeCaminho(busca, i);
		fprintf(arquivoSaida, "\n");
	}
}

void visitaProfundidade(Grafo* grafo, Busca busca, int* tempo, int vert, int prof) {
	
	busca.cor[vert] = CINZA;
	fprintf(arquivoSaida,"%i ", vert);
	(*tempo)++;
	busca.tempoDescoberta[vert] = (*tempo);
	printf("%*s Descobri o vértice %i no tempo %i.\n", prof*2, "", vert, (*tempo));

	 //posição do vertice adjacente
	Apontador apontador = primeiroListaAdj(grafo, vert);

	//o verdadeiro núm q representa o vertice adjacente (índice)
	//int verticeAdjacente = verticeDestino(apontador); 

	// itera até o final da lista de adjacência
	 
	while(apValido(apontador)){
		int verticeAdjacente = verticeDestino(apontador);
		printf("%*s O vértice adjacente é: %i .\n", prof*2, "", verticeAdjacente);
		

		if(busca.cor[verticeAdjacente] == BRANCO){
			busca.distancia[verticeAdjacente] = busca.distancia[vert]+1;
			busca.antecessor[verticeAdjacente] = vert;
			visitaProfundidade(grafo, busca, tempo, verticeAdjacente,  prof+1);
		}

		apontador = proxListaAdj(grafo, vert, apontador);
	}
	busca.cor[vert] = PRETO;
	(*tempo)++;
	busca.tempoFechamento[vert] = (*tempo);
}

/*
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

	//Acessos acessos;

	// Vértice início da busca. Por padrão possui valor -1, mas se configurado, a busca irá
	// explorar apenas o início
	int inicio;

	// Objeto do usuário. Não será alterado ou acessado pelo mecanismo de busca.
	void* objeto; //hein
	
	// -- Estado da busca e resultados --

	// Relógio do algoritmo de busca
	int tempo;

	// Vetor de cores de todos os vértices do grafo
	BuscaCor* cor;

	// Vetor de tempo de descoberta dos vértices
	int* tempoDesc;

	// Vetor do tempo de término dos vértices. O QUE ISSO SIGNIFICA
	int* tempoTerm;

	// Vetor de antecessores de cada vértice do grafo AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
	int* antecessor;

	// Vetor de distâncias de cada vértice em relação a raiz da árvore de busca. PARA QUEEEEE
	int* distancia;
};*/
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


/*
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
		apontador= proxListaAdj(v, *grafo, apontador);
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
}*/

