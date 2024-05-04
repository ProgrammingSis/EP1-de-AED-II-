#ifdef MATRIZ
#include "grafo_matrizadj.h"
#else
#include "grafo_listaadj.h"
#endif

#define MAXNUMVERTICES 100
/* O arquivo Makefile NÃO deverá ser entregue

  Preciso de:

    * Entender o que vai no .c e o que vai no .h (prontooo)

    * Como colocar o include no .h, é no .h mesmo

    * Rotinas de buscas, etc (utilizando apenas as funções definidas na interface de grafos, ou seja, sem assumir explicitamente a estrutura por matriz ou lista de adjacência),

    * Main (está presente)

    * Aprender busca em largura

    * Aprender busca em profundidade

    * Aprender sobre vértices de articulação

    * Ler o artigo sobre a forma mais eficiente de se descobrir um vértic de articulação

    * Relembrar como se faz manipulação de arquivos
    *procurar como se faz para detectar um componente complexo num grafo    
*/

void visitaBP(int v, Grafo* grafo, bool* cor, int* tdesc, int* tterm, int* antecessor, int* tempo){
	cor[v]= true;
	tdesc[v]=++(*tempo);

	Apontador apontador;

	apontador = primeiroListaAdj(grafo, v);

	while(ehApValido(apontador)){
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