#ifndef TREE_H
#define TREE_H


typedef struct node{
	int valor;
	struct node *next;
} node_t;

typedef struct lista{
	int tamanho;
	node_t *head;
	node_t *tail;		
}lista_t;

#endif