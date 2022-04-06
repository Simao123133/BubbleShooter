#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ledados.h"

DADOS le_dados(int argc,char* argv[]){
	DADOS dados;

	int checkraio = 0,checkaltura = 0,checklargura = 0,debugger = 0;
	dados.erro = 0;
	dados.debugger = 0;

  for(int i=1;i<argc;i++){
    if(strcmp(argv[i],"-l") == 0 && i != argc-1){
			dados.largura = atoi(argv[i+1]);
      if(dados.largura > 0)
        checklargura++;                                                      //verificação introduçao largura
		}

    else if(strcmp(argv[i],"-a") == 0 && i != argc-1){
			dados.altura = atoi(argv[i+1]);                                         //verificação introduçao altura
      if(dados.altura > 0)
        checkaltura++;
    }

		else if(strcmp(argv[i],"-b") == 0 && i != argc-1){
			dados.raio = atoi(argv[i+1]);
      if(dados.raio > 0)                                                      //verificação introduçao raio
        checkraio++;
		}

    else if(strcmp(argv[i],"-d") == 0)                                            //verificação introduçao debugger
      dados.debugger++;

	}

  if(checklargura != 1 || checkraio != 1 || checkaltura != 1 || argc > 8)
    dados.erro = 1;
	if(argc == 8 && dados.debugger == 0)
		dados.erro = 1;                                                                  //verifica condições

	if(dados.erro == 1){
		printf("Siga o exemplo: -l (largura) -a (altura) -b (raio)\n");
    printf("Caso queira modo debugger acrescente -d\n");
	}

	if((((dados.altura-2)*dados.largura)%3) != 0){
		printf("Para facilitar o jogo insira uma (altura-2) e largura cuja multiplicacao seja multipla de 3\n");
		dados.erro = 1;
	}

	return dados;

}
