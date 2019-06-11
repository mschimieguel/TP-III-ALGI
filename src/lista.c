#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

lista_t *createlist(){
    //retorna uma lista vazia alocada no heap
    lista_t *lista = (lista_t*) malloc(sizeof(lista_t));
    lista->head = NULL;
    lista->tail = NULL;
    lista->tamanho = 0;
    return lista; 
}
void adicionar_elemento_inicio(lista_t *lista,int valor){
    //alocando o no novo no heap
    node_t *no_novo=(node_t*)malloc(sizeof(node_t));
    
    //atribuindo as caracteristicas do novo no e da lista
    no_novo->valor = valor;
    no_novo->next = lista->head;
    lista->tamanho++;
    

    if (lista->head == NULL){
        //caso a lista esteja vazia
        lista->head=no_novo;
        lista->tail=no_novo;
    }
    else {
        //caso a lista tenha pelo menos um elemento
        no_novo -> next = lista->head;
        lista->head=no_novo;    
    }    
}
void adicionar_elemento_fim(lista_t *lista,int valor){
    //alocando no heap o novo no
	node_t *no_novo=(node_t*)malloc(sizeof(node_t));

    //atribuindo as caracteristicas do novo no e da lista
    no_novo->valor= valor;
    no_novo->next = NULL;
    lista->tamanho++;
    
    if (lista->head == NULL){
        //caso a lista seja vazia
        lista->head=no_novo;
        lista->tail=no_novo;
    }
    else {
        //caso a lista tenha pelo menos um elemento
        lista->tail->next = no_novo;
        lista->tail=no_novo;    
    }    
}
void adicionar_elemento(lista_t *lista,int valor,int pos){       
    if (pos > 0 && pos < lista->tamanho-1){
        node_t *tovisit=lista->head;
        for (int i = 0;i < pos-1;i++){
            tovisit=tovisit->next;
        }
        node_t *ultrapassado = tovisit->next;
        node_t *no_novo=(node_t*)malloc(sizeof(node_t));
        tovisit->next=no_novo;
        no_novo->next=ultrapassado;
        no_novo->valor = valor;
        lista->tamanho++;
    }
    else if (pos == 0)
        adicionar_elemento_inicio(lista,valor);
    else if (pos == lista->tamanho)
        adicionar_elemento_fim(lista,valor);
    else 
        printf("posicao nao permitida\n");
     
}
int retirar_elemento_inicio(lista_t *lista){
    
    node_t *tofree = lista->head;
    int toreturn=tofree->valor;
    lista->head=lista->head->next;
    lista->tamanho--;

    free(tofree);
    return toreturn;
}
int retirar_elemento_fim(lista_t *lista){
    
    node_t *previus = lista->head;
    while(previus->next != lista->tail)
        previus = previus->next;
    
    node_t *tofree=previus->next;
    int toreturn=tofree->valor;
    
    lista->tail = previus;
    previus->next = NULL;
    free(tofree);
    lista->tamanho--;
    return toreturn;
}
int retirar_elemento(lista_t *lista,int pos){
    
    if (pos > 0 && pos < lista->tamanho - 1){
        node_t *tovisit =lista->head;
        node_t *tofree = NULL;
        for (int i = 0;i < pos-1;i++)
            tovisit=tovisit->next;
        tofree = tovisit->next;
        tovisit->next = tofree->next;
        lista->tamanho--;
        int toreturn = tofree->valor;
        free(tofree);
        return toreturn;
    }    
    else if (pos==0)
        return retirar_elemento_inicio(lista);
    else if (pos == lista->tamanho - 1)
        return retirar_elemento_fim(lista);
    else {
        printf ("posicao inexistente ou nao permitida\n");
        return -1;
    } 
        
}
void destruir_lista(lista_t *lista){
    while (lista->head != NULL){
         retirar_elemento_inicio(lista);
    }
    free(lista);    
}
void limpar_lista(lista_t *lista){
   while (lista->head != NULL){
         retirar_elemento_inicio(lista);
    } 
}
void imprimir_lista(lista_t *lista){
    if (lista->head != NULL){
        printf("tamanho == %d; elementos == { ",lista->tamanho);
        node_t *tovisit=lista->head;
        while (tovisit != NULL){
            printf("%d, ",tovisit->valor);
            tovisit = tovisit->next;
        }
        printf("};\n");
    }
    else 
        printf("lista vazia \n");
    //printf("tamanho == 0; elementos == {}\n");    
}
int busca_valor(lista_t *lista, int valor){
	if (lista->head == NULL){
		printf("Error, lista vazia!!");
    	exit(1);
	}

    int pos = 0;
    node_t *atual = lista->head;
	while(atual != NULL && atual->valor != valor ){
		pos++;
        atual = atual->next;
	}
	if (atual != NULL)
		return pos;
	//atual == NULL e nesse caso nao existe o elemento procurado
	return -1;
}
int acessar(lista_t *lista,int pos){
     if (pos >= 0 && pos <= lista->tamanho - 1){
        
        node_t *tovisit = lista->head;
        for (int i = 0;i < pos;i++)
            tovisit=tovisit->next;
  
        return tovisit->valor;
    }    
    else {
        printf ("posicao inexistente ou nao permitida\n");
        return -1;
    } 
}