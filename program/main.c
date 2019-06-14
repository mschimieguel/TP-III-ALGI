#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include "lista.h"

int **VisitedNodes;
int *parent;

int VertexCoverHeuristic(lista_t **listaAdjacencia,int n,int m){
	int v = 0;
	while(m > 0){
		for(int i = 0;i < n;i++){
			if(listaAdjacencia[i]->tamanho > 0){
				parent[listaAdjacencia[i]->head->valor] = 1;
				parent[i] = 1;
				m -= listaAdjacencia[i]->tamanho;
				m -=listaAdjacencia[listaAdjacencia[i]->head->valor]->tamanho;
				limpar_lista(listaAdjacencia[listaAdjacencia[i]->head->valor]);
				limpar_lista(listaAdjacencia[i]);
				v += 2;
			}
		}
	}
	return v;
}
int min(int a,int b){
	if (a < b)
		return a;
	return b;
}
int VertexCoverTree(lista_t **listaAdjacencia,int atualNode,int isVertexCover){
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
					soma += VertexCoverTree(listaAdjacencia,node,1);
				else
					soma += min( VertexCoverTree(listaAdjacencia,node,0),VertexCoverTree(listaAdjacencia,node,1) );
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
	}

	//definindo qual tarefa deve ser feita
	if ( strcmp(tarefa,"tarefa1") == 0 ){
		//realizar tarefa {"Solucao otima","grafo sem ciclos","tempo max 2 segundos"}
		VisitedNodes = (int**)malloc(n*sizeof(int*));
		parent = (int*)malloc(n*sizeof(int));
		for (int i = 0; i < n;i++){
			VisitedNodes[i] = (int*)malloc(2*sizeof(int));
			VisitedNodes[i][0] = -1;VisitedNodes[i][1] = -1;
			parent[i] = -1;
		}
		int to_return = min( VertexCoverTree(listaAdjacencia,0,0),VertexCoverTree(listaAdjacencia,0,1));
		printf("%d\n",to_return);
		free(parent);
		for (int i = 0;i < n;i++)
			free(VisitedNodes[i]);
		free(VisitedNodes);
		return 0;
	}
	else if ( strcmp(tarefa,"tarefa2") == 0 ){
		//realizar tarefa2 {"heuristica","solucao ate 2 vezes pior que a otima","grafo pode conter ciclos"}
		parent = (int*)malloc(n*sizeof(int));
		for(int i = 0;i < n;i++)
			parent[i] = 0;
		int to_return = VertexCoverHeuristic(listaAdjacencia,n,m);
		printf("%d\n",to_return);
		// for (int i = 0;i < n;i++)
		// 	if(parent[i] == 1)
		// 		printf("%d\n",i);
		free(parent);
		return 0;
	}
	else {
		printf("Por favor execute novamente e passe como primeiro parametro tarefa1 ou tarefa2 \n");
		return 0;
	}
	return 0;
}