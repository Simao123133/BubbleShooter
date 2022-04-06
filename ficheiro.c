#include <stdio.h>
#include <stdlib.h>
#include <string.h>\

#include "ficheiro.h"

void normaliza_string(char nomeaux[],char nomefinal[]){

  int i;

  for(i=0;nomeaux[i] != '\0';i++)
    nomefinal[i] = nomeaux[i];
                                                                           //transforma os vetores em vetores com 10 elementos
  for(int j = i;j<10;j++)
    nomefinal[j] = ' ';

  nomefinal[10] = '\0';
}

linha_t le_ficheiro(FILE *fp) {
	linha_t linha;
	int i, ch;
	char nomeaux[99];
                                                                           //funcao que le do ficheiro que entra como argumento
	linha.eof = 0;

	if(fscanf(fp, "%s %d\n", nomeaux, &linha.pontos) == EOF)
		linha.eof = 1;

	normaliza_string(nomeaux,linha.nome);

	return linha;
}

linha_t obtem_linha(int pontuacao) {
	linha_t linha;
	char nomeaux[99];

	int len = 0;

	while(len > 10 || len == 0) {
		printf("Insira o nome: \n");                                                  //funcao que obtem nome
		scanf("%s", nomeaux);

		len = strlen(nomeaux);
	}

	normaliza_string(nomeaux,linha.nome);
  linha.pontos = pontuacao;

	return linha;
}

void escreve_ficheiro(FILE *fp, linha_t linha) {
	fprintf(fp, "%s %d\n", linha.nome, linha.pontos);                               //funcao que escreve no ficheiro
}

int escrever_nova_pontuacao(linha_t userline) {

	FILE *principal = fopen("resultados.txt", "r");

	if(principal == NULL) {
		principal = fopen("resultados.txt","w");
		if(principal == NULL){
			printf("Erro na criacao do ficheiro\n");
			return -1;                                                                 //cria o ficheiro se nao existir
		}                                                                            //verifica se ha problemas na abertura dos ficheiros
		fclose(principal);
		principal = fopen("resultados.txt","r");
		if(principal == NULL){
			printf("Erro na abertura do ficheiro\n");
			return -1;
		}

	}

	FILE *aux = fopen("aux.txt", "w");

	if(aux == NULL){
		printf("Erro na abertura do ficheiro\n");
		return -1;
	}

	linha_t linha = le_ficheiro(principal);

	while(linha.pontos > userline.pontos && !linha.eof) {                                  //copia dos ficheiro principal
                                                                                         //para o auxiliar ate os pontos serem menores
		escreve_ficheiro(aux, linha);
		linha = le_ficheiro(principal);
	}

	escreve_ficheiro(aux, userline);                                           //escreve a nova linha no sitio correto

	while(!linha.eof) {
		escreve_ficheiro(aux, linha);
		linha = le_ficheiro(principal);                                        //copia o resto
	}

	fclose(principal);
	fclose(aux);                                                           // fecha os ficheiros

	principal = fopen("resultados.txt", "w");
  if(principal == NULL){
    printf("Erro na abertura do ficheiro\n");
    return -1;                                                                 //abre os ficheiros outra vez
  }

	aux = fopen("aux.txt", "r");
  if(aux == NULL){
    printf("Erro na abertura do ficheiro\n");
    return -1;
  }

	do {
		linha = le_ficheiro(aux);
		if(!linha.eof)                                                             //copia do auxiliar para o principal
			escreve_ficheiro(principal, linha);
	} while(!linha.eof);
  fclose(principal);
  fclose(aux);                                                           // fecha os ficheiros

	remove("aux.txt");                                                     //remove auxiliar
}
