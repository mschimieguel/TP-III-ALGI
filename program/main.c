#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include "lista.h"

int **VisitedNodes;
int *parent;

int eliminar(int elemento,lista_t **listaAdjacencia,int pos){
	printf("Elemento == %d\n",elemento);
	printf("A%d\n",pos);
	if (listaAdjacencia[pos]->tamanho > 0){
		if(listaAdjacencia[pos]->head->valor == elemento){
			printf("B%d\n",pos);
			return retirar_elemento_inicio (listaAdjacencia[pos]);
		}
		else if (listaAdjacencia[pos]->tail->valor == elemento){
			printf("C%d\n",pos);
			return retirar_elemento_fim (listaAdjacencia[pos]);
		}
		else {
			if (listaAdjacencia[pos]->tamanho <= 2)
				return -1;
			printf("D%d\n",pos);
			node_t *atual = listaAdjacencia[pos]->head;
	        node_t *tofree = NULL;
	        printf("erro 1 %d\n",listaAdjacencia[pos]->tamanho);
	        while (atual->next != listaAdjacencia[pos]->tail){
	        	if (atual->next->valor == elemento)
	        		break;
	            atual=atual->next;
	        }
	        //printf("erro 2\n");
	        tofree = atual->next;
	        atual->next = tofree->next;
	        listaAdjacencia[pos]->tamanho--;
	        int toreturn = tofree->valor;
	        free(tofree);
	        printf("erro 3\n");
	        return toreturn;
		}
	}
	return -1;
}
int VertexCoverHeuristic(lista_t **listaAdjacencia,int n,int m){
	int v = 0;
	//lista_t *unvisitednodes = createlist();
	while(m > 0){
		for(int i = 0;i < n;i++){
			if(listaAdjacencia[i]->tamanho > 0){
				parent[listaAdjacencia[i]->head->valor] = 1;
				parent[i] = 1;
				m -= listaAdjacencia[i]->tamanho;
				m -=listaAdjacencia[listaAdjacencia[i]->head->valor]->tamanho;
				for(int j = 0;j < listaAdjacencia[i]->head->valor ;j++){
					if (j != i){
						printf ("Eliminado : %d\n",eliminar(listaAdjacencia[i]->head->valor,listaAdjacencia,j));
						m--;
					}

				}
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
		node_t *atual = listaAdjacencia[atualNode]->head;
		for (int i = 0;i < listaAdjacencia[atualNode]->tamanho;i++){

			int node = atual->valor;//acessar(listaAdjacencia[atualNode],i);
			//printf("%d\n",i);
			if(node != parent[atualNode]){
				parent[node] = atualNode;
				if(isVertexCover == 0)
					soma += VertexCoverTree(listaAdjacencia,node,1);
				else
					soma += min( VertexCoverTree(listaAdjacencia,node,0),VertexCoverTree(listaAdjacencia,node,1) );
			}
			atual =atual->next;
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