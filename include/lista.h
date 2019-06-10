#ifndef LISTA_H
#define LISTA_H

typedef struct node{
	int valor;
	struct node *next;
} node_t;

typedef struct lista{
	int tamanho;
	node_t *head;
	node_t *tail;		
}lista_t;

lista_t *createlist();
void adicionar_elemento_inicio(lista_t *lista,int valor);
void adicionar_elemento_fim(lista_t *lista,int valor);
void adicionar_elemento(lista_t *lista,int valor,int pos);

int  retirar_elemento_inicio(lista_t *lista);
int  retirar_elemento_fim(lista_t *lista);
int  retirar_elemento(lista_t *lista,int pos);

int busca_valor(lista_t *lista, int valor);

void destruir_lista(lista_t *lista);
void limpar_lista(lista_t *lista);
void imprimir_lista(lista_t *lista);

void remove_duplicados(lista_t *lista);

int acessar(lista_t *lista,int pos);

#endif