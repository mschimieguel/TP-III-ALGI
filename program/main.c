#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[]){
	char *tarefa = argv[1]; 
	FILE *ARQ = fopen(argv[2],"r");
	if(!ARQ_){
		printf("Arquivo de Trilhas Inexistente\n");
		return 0;
	}
	if ( strcomp(tarefa,"tarefa1") == 0 ){
		//realizar tarefa {"Solucao otima","grafo sem ciclos","tempo max 2 segundos"}
	}
	else if ( strcomp(tarefa,"tarfefa2") == 0 ){
		//realizar tarefa2 {"heuristica","solucao ate 2 vezes pior que a otima","grafo pode conter ciclos"}
	}
	else {
		printf("Por favor execute novamente e passe como primeiro parametro tarefa1 ou tarefa2 \n");
		return 0;
	}
}