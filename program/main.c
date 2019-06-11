#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include "lista.h"

int min(int a,int b){
	if (a < b)
		return a;
	return b;
}
int **VisitedNodes;
int *parent;

int VertexCover(lista_t **listaAdjacencia,int atualNode,int isVertexCover){
	if (listaAdjacencia[atualNode]->tamanho == 0)
		return isVertexCover;
	else if (VisitedNodes[atualNode][isVertexCover] != -1)
		return VisitedNodes[atualNode][isVertexCover];
	else{
		int soma = 0;
		for (int i = 0;i < listaAdjacencia[atualNode]->tamanho;i++){

			int node = acessar(listaAdjacencia[atualNode],i);
			//printf("%d\n",i);
			if(node != parent[atualNode]){
				parent[node] = atualNode;
				if(isVertexCover == 0)
					soma += VertexCover(listaAdjacencia,node,1);
				else
					soma += min( VertexCover(listaAdjacencia,node,0),VertexCover(listaAdjacencia,node,1) );
			}
		}
		VisitedNodes[atualNode][isVertexCover] = soma + isVertexCover;
		return VisitedNodes[atualNode][isVertexCover];
	}
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
	for (int i = 0;i < n;i++)
		listaAdjacencia[i] = createlist();

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
		VisitedNodes = (int**)malloc(n*sizeof(int*));
		parent = (int*)malloc(n*sizeof(int));
		for (int i = 0; i < n;i++){
			VisitedNodes[i] = (int*)malloc(2*sizeof(int));
			VisitedNodes[i][0] = -1;VisitedNodes[i][1] = -1;
			parent[i] = -1;
		}
		//vertexCover(listaAdjacencia,n,0);
		//printf("VertexCover == %d\n",size_VC);
		for (int i = 0;i < n;i++){
			printf("lista  : %d\n  ",i);
			imprimir_lista(listaAdjacencia[i]);
			printf(" \n");
		}
		VertexCover(listaAdjacencia,0,0);
		printf("VertexCover == %d \n",min( VertexCover(listaAdjacencia,0,0),VertexCover(listaAdjacencia,0,1)));
	}
	else if ( strcmp(tarefa,"tarefa2") == 0 ){
		//realizar tarefa2 {"heuristica","solucao ate 2 vezes pior que a otima","grafo pode conter ciclos"}
		printf("tarefa1\n");
	}
	else {
		printf("Por favor execute novamente e passe como primeiro parametro tarefa1 ou tarefa2 \n");
		return 0;
	}
	return 0;
}