#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include "lista.h"

int **VisitedNodes;
int *parent;

int eliminar(int elemento,lista_t **listaAdjacencia,int pos){
	//retira uma aresta elemento de uma lista encadeda na posicao pos do vetor de listas
	if (listaAdjacencia[pos]->tamanho > 0){
		if(listaAdjacencia[pos]->head->valor == elemento){
			return retirar_elemento_inicio (listaAdjacencia[pos]);
		}
		else if (listaAdjacencia[pos]->tail->valor == elemento){
			return retirar_elemento_fim (listaAdjacencia[pos]);
		}
		else {
			if (listaAdjacencia[pos]->tamanho <= 2)
				return -1;
			node_t *atual = listaAdjacencia[pos]->head;
	        node_t *tofree = NULL;
	        while (atual->next != listaAdjacencia[pos]->tail){
	        	if (atual->next->valor == elemento)
	        		break;
	            atual=atual->next;
	        }
	        tofree = atual->next;
	        atual->next = tofree->next;
	        listaAdjacencia[pos]->tamanho--;
	        int toreturn = tofree->valor;
	        free(tofree);
	        return toreturn;
		}
	}
	return -1;
}
int VertexCoverHeuristic(lista_t **listaAdjacencia,int n,int m){
	int v = 0;
	while(m > 0){
		for(int i = 0;i < n;i++){
			if(listaAdjacencia[i]->tamanho > 0){
				parent[listaAdjacencia[i]->head->valor] = 1;
				parent[i] = 1;
				m -= listaAdjacencia[i]->tamanho;
				m -=listaAdjacencia[listaAdjacencia[i]->head->valor]->tamanho;
			
				node_t *atual = listaAdjacencia[i]->head;
				//caminhando na lista i para remover as arestas
				for (int j = 0;j < listaAdjacencia[i]->tamanho;j++){
					if(atual->valor != listaAdjacencia[i]->head->valor)
						eliminar(i,listaAdjacencia,atual->valor);
					atual = atual->next;
				}
				atual = listaAdjacencia[listaAdjacencia[i]->head->valor]->head;
				// caminhando na lista 'listaAdjacencia[i]->head->valor' para remover as arestas
				for (int j = 0;j < listaAdjacencia[listaAdjacencia[i]->head->valor]->tamanho;j++){
					if(atual->valor != i)
						eliminar(listaAdjacencia[i]->head->valor,listaAdjacencia,atual->valor);
					atual = atual->next;
				}
				//fzendo com que 
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
		return VisitedNodes[atualNode][isVertexCover];//retorna o valor ja calculado
	else{
		int soma = 0;
		node_t *aux = listaAdjacencia[atualNode]->head;
		for (int i = 0;i < listaAdjacencia[atualNode]->tamanho;i++){

			int element = aux->valor;
			if(element != parent[atualNode]){
				//se element não for o pai de atualnode entao atualnode é o pai de element 
				parent[element] = atualNode;
				if(isVertexCover == 0)
					soma += VertexCoverTree(listaAdjacencia,element,1);
				else
					soma += min( VertexCoverTree(listaAdjacencia,element,0),VertexCoverTree(listaAdjacencia,element,1) );
			}
			aux = aux->next;
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


	int a,b;
	for (int i = 0;i < m;i++){
		fscanf(ARQ,"%d %d",&a,&b);
		adicionar_elemento_fim(listaAdjacencia[a],b);
		adicionar_elemento_fim(listaAdjacencia[b],a);
	}

	//definindo qual tarefa deve ser feita
	if ( strcmp(tarefa,"tarefa1") == 0 ){
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
		parent = (int*)malloc(n*sizeof(int));
		for(int i = 0;i < n;i++)
			parent[i] = 0;
		int to_return = VertexCoverHeuristic(listaAdjacencia,n,m);
		printf("%d\n",to_return);
		for (int i = 0;i < n;i++)
		 	if(parent[i] == 1)
		 		printf("%d\n",i);
		free(parent);
		return 0;
	}
	else {
		printf("Por favor execute novamente e passe como primeiro parametro tarefa1 ou tarefa2 \n");
		return 0;
	}
	return 0;
}