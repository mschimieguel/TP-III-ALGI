#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include "lista.h"

int size_VC = 0;
//int VisitedNodes[n];

int vertexCover(lista_t **listaAdjacencia,int n,int vertex){
	printf("Vertice == %d \n",vertex);
	if (listaAdjacencia[vertex]->tamanho == 0)
		return 1;
	//int  addAtualNode = 0;
	int a = 1;
	for (int i = 0;i < listaAdjacencia[vertex]->tamanho;i++){
		a *= vertexCover( listaAdjacencia,n,acessar(listaAdjacencia[vertex],i) );
	}
	if (a == (int)pow(2,listaAdjacencia[vertex]->tamanho)){
		printf("______ %d\n",vertex);
		limpar_lista(listaAdjacencia[vertex]);
		return 3;
	}
	if (a == 1){
		//no colocado no set cover
		printf("XXXXX == %d\n",vertex);
		size_VC++;
		limpar_lista(listaAdjacencia[vertex]);
		return 2;
	}
	
	return 0;
}

int main(int argc,char *argv[]){
	char *tarefa = argv[1]; 
	FILE *ARQ = fopen(argv[2],"r");
	if(!ARQ){
		printf("Arquivo de Trilhas Inexistente\n");
		return 0;
	}
	int n,m;
	fscanf(ARQ,"%d %d",&n,&m);
	//criando lista de adjacencia
	lista_t **listaAdjacencia = (lista_t **) malloc(n*sizeof(lista_t*));
	for (int i = 0;i < n;i++){
		listaAdjacencia[i] = createlist();
		//VisitedNodes[i] = 0;
	}
	//considerando que a representaçao da aresta (a,b) a < b no arq de entrada
	int a,b;
	for (int i = 0;i < m;i++){
		fscanf(ARQ,"%d %d",&a,&b);
		adicionar_elemento_fim(listaAdjacencia[a],b);
		//printf("a == %d , b == %d \n",a,b);
	}


	//definindo qual tarefa deve ser feita
	if ( strcmp(tarefa,"tarefa1") == 0 ){
		//realizar tarefa {"Solucao otima","grafo sem ciclos","tempo max 2 segundos"}
		printf("tarefa1\n");
	}
	else if ( strcmp(tarefa,"tarefa2") == 0 ){
		//realizar tarefa2 {"heuristica","solucao ate 2 vezes pior que a otima","grafo pode conter ciclos"}
		printf("tarefa1\n");
	}
	else {
		printf("Por favor execute novamente e passe como primeiro parametro tarefa1 ou tarefa2 \n");
		return 0;
	}
	//for (int i = 0;i < n;i++){
	//	printf("lista  : %d\n  ",i);
	//	imprimir_lista(listaAdjacencia[i]);
	//	printf(" \n");
	//}
	vertexCover(listaAdjacencia,n,0);
	printf("VertexCover == %d\n",size_VC);
	for (int i = 0;i < n;i++){
		printf("lista  : %d\n  ",i);
		imprimir_lista(listaAdjacencia[i]);
		printf(" \n");
	}

	//printf(vertexCover(listaAdjacencia,n,0));
	return 0;
}