// Realizado por: Miguel Silva número: 89699 e Simão Amaro número: 89715
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include <math.h>
#include <time.h>

#include "ficheiro.h"                  //bibliotecas criadas
#include "grafica.h"
#include "ledados.h"
#include "funcoes.h"

void desenha_bolhas(MATRIZ* v[],int COLUNAS,int LINHAS,int raio,int v1[COLUNAS]);
void desenha_modo_debugg_vertical(int raio,MATRIZ* inicio,MATRIZ* fim,MATRIZ* v[],int COLUNAS,int LINHAS);
void desenha_modo_debugg_horizontal(int raio,MATRIZ* inicio,MATRIZ* fim,MATRIZ* v[],int COLUNAS,int LINHAS);

int main(int argc, char* argv[]) {
	srand(time(NULL));

	DADOS dados;                                                                                                //declaraçao variaveis
	int novo_jogo = 0,end_game = 0,windowsizex,windowsizey,pontostotal = 0,aux1 = 0,aux2 = 0,aux3,i = 0;
	int rato_x,rato_y,x,y,linha1,coluna1,linha2,coluna2,marca1 = 0,marca2 = 0,orientacao,win = 0,aux6,aux7;
	SDL_Event event,event1;
	char pontinhos[999];

	if((dados = le_dados(argc,argv)).erro)
		return 1;

	MATRIZ* v[dados.largura],*bola1,*bola2,*inicio,*fim,*inicio1,*fim1;
	int aux[dados.altura-2][dados.largura],aux4[dados.altura-2][dados.largura],v3[dados.largura],v4[dados.largura],aux5[dados.altura-2][dados.largura];
	windowsizex = dados.largura * dados.raio * 2;
	windowsizey = dados.altura * dados.raio * 2;
	do{
		if(inicia_matriz(novo_jogo,v,dados.largura,dados.altura-2,aux) == 0)
			break;
		else{                                                                         //o ciclo verifica se o jogo
			tamanhomatriz(dados.largura,dados.altura-2,v,v3);														//começa com multiplos de 3 bolas de cada cor
			limpa_matriz(v,dados.largura,v3);                                           //para facilitar vitoria
		}
  }while(1);
	criar_janela(windowsizex,windowsizey);

	while(end_game == 0){
		pinta_janela();
		texto(windowsizex,windowsizey,dados.raio);
		tamanhomatriz(dados.largura,dados.altura-2,v,v3);
		for(int j = 0;j < dados.largura;j++){
			if(v3[j] == 0)                                            //desenha os elementos do jogo
				win++;																									//verifica se ganhou o jogo
		}

		if(win == dados.largura){
			end_game = 1;
			printf("GANHOUUU\n");
		}

		desenha_bolhas(v,dados.largura,dados.altura-2,dados.raio,v3);
		sprintf(pontinhos,"%d",pontostotal);
		mostra_pontuacao(pontinhos,dados.raio,dados.largura*dados.raio*2);


		if(marca1 == 1)
			desenha_cruz(dados.raio,dados.altura,coluna1,linha1,bola1->cor);

		if(marca2 == 1)
			desenha_cruz(dados.raio,dados.altura,coluna2,linha2,bola2->cor);

		if(marca1 == 1 && marca2 == 1){
			orientacao = f_analisa_troca(v,&bola1,&bola2,dados.largura,dados.altura-2);
			if(orientacao != -1){
					copia_matriz(dados.largura,dados.altura-2,aux4,v,v4);
					troca(v,bola1,bola2,orientacao,dados.largura);
					copia_matriz(dados.largura,dados.altura-2,aux5,v,v4);
					do{
						aux1 = f_verifica_vertical(v,&inicio,&fim,dados.largura,dados.altura-2);
						if(aux1 != -1){
							if(dados.debugger == 1)
								desenha_modo_debugg_vertical(dados.raio,inicio,fim,v,dados.largura,dados.altura-2);
							f_elimina_vertical(v,inicio,fim,dados.largura);                                                   //desenha cruzes no modo debug
						}

						aux2 = f_verifica_horizontal(v,&inicio1,&fim1,dados.largura,dados.altura-2);
						if(aux2 != -1){
							if(dados.debugger == 1)
								desenha_modo_debugg_horizontal(dados.raio,inicio1,fim1,v,dados.largura,dados.altura-2);
							f_elimina_horizontal(v,inicio1,fim1,dados.largura,dados.altura-2);
						}
					}while(aux1 != -1 || aux2 != -1);

					apresenta_janela();
					if(dados.debugger == 0){
						i = 1;
						tamanhomatriz(dados.largura,dados.altura-2,v,v3);
						limpa_matriz(v,dados.largura,v3);
						reescreve_matriz(v,dados.largura,dados.altura-2,aux5,v4);
					}
					while(i == 0){
						SDL_PollEvent(&event1);
						switch(event1.type){
							case SDL_MOUSEBUTTONDOWN:
								i = 1;
								SDL_Delay(300);
								tamanhomatriz(dados.largura,dados.altura-2,v,v3);
								limpa_matriz(v,dados.largura,v3);
								reescreve_matriz(v,dados.largura,dados.altura-2,aux4,v4);
								SDL_Delay(300);                                                                     //avança ou retrocede consoante tecla pressionada
								break;
								case SDL_KEYDOWN:
									switch(event1.key.keysym.sym)
									{
										case SDLK_SPACE:
											tamanhomatriz(dados.largura,dados.altura-2,v,v3);
											limpa_matriz(v,dados.largura,v3);
											reescreve_matriz(v,dados.largura,dados.altura-2,aux5,v4);
											i = 1;
											break;
									}
							    break;
						}
				 }
				 i = 0;
			}
			do{
				aux1 = f_verifica_vertical(v,&inicio,&fim,dados.largura,dados.altura-2);
				aux2 = f_verifica_horizontal(v,&inicio1,&fim1,dados.largura,dados.altura-2);
				if(aux1 != -1){
					f_elimina_vertical(v,inicio,fim,dados.largura);                                                  //  elimina bolhas modo normal
					pontostotal = pontostotal + aux1;
				}
				if(aux2 != -1){
					f_elimina_horizontal(v,inicio1,fim1,dados.largura,dados.altura-2);
					pontostotal = pontostotal + aux2;
				}
			}while(aux1 != -1 || aux2 != -1);
			f_limpa_selecoes(v,dados.largura,dados.altura-2);
			marca1 = 0;
			marca2 = 0;
	  }

		SDL_PollEvent(&event);
		switch(event.type){
			case SDL_QUIT:
				end_game = 1;
				break;

				case SDL_MOUSEBUTTONDOWN:
					SDL_Delay(100);
					SDL_GetMouseState(&rato_x,&rato_y);

					if(rato_x >= windowsizex/4.5 && rato_x <= windowsizex/3.3 && rato_y >= dados.raio && rato_y <= dados.raio*2)
					{
						end_game = 1;
						break;
					}

					if(rato_x >= dados.raio && rato_x <= windowsizex/5 && rato_y >= dados.raio && rato_y <= 2*dados.raio)
					{
						if(dados.debugger == 1)
							novo_jogo = 1;
						tamanhomatriz(dados.largura,dados.altura-2,v,v3);                                          //novo_jogo no modo normal e debug
						limpa_matriz(v,dados.largura,v3);
						inicia_matriz(novo_jogo,v,dados.largura,dados.altura-2,aux);
						pontostotal = 0;
						break;
					}

					x = adquire_posicao_x(rato_x,dados.largura,dados.raio);                                     //transforma posiçoes em pixeis para as das bolas
					y = adquire_posicao_y(rato_y,dados.altura,dados.raio);

					if(marca1 == 1){

						bola2 = f_acede_posicao(x,y,v,dados.largura,dados.altura);
						aux7 = bola2->cor;
						if(bola2 == NULL){
							marca1 = 0;                                                                              //marcar segunda bola
							break;
					  }
						f_descobre_bola(&linha2,&coluna2,bola2,v,dados.largura,dados.altura-2);
						bola2->troca = 1;
						marca2 = 1;
						break;
				  }

					if(marca1 == 0){
						bola1 = f_acede_posicao(x,y,v,dados.largura,dados.altura);
						aux6 = bola1->cor;
						if(bola1 == NULL)
							break;
						f_descobre_bola(&linha1,&coluna1,bola1,v,dados.largura,dados.altura-2);
						bola1->troca = 1;                                                                    //marcar primeira bola
						marca1 = 1;
						break;
					}
		}
		apresenta_janela();
		win = 0;
	}

	linha_t linha = obtem_linha(pontostotal);

	if(escrever_nova_pontuacao(linha) == -1)
		return 1;

	return 0;
}

void desenha_bolhas(MATRIZ* v[],int COLUNAS,int LINHAS,int raio,int v1[COLUNAS]){
	int x,y;
	MATRIZ* coluna;
	for(int i=0;i<COLUNAS;i++){
		while(v1[i] == 0 && i != COLUNAS-1){      // se a a casa do vetor for nula passa para a proxima coluna
			i++;
		}
		x = 2*raio*i+raio;
		coluna = v[i];
		for(int j=0;j<LINHAS;j++){
			y = (LINHAS+2)*2*raio-2*raio-2*raio*j;
			if(coluna == NULL)                              // se o endereço for = NULL passa para a proxima coluna ou acaba
				break;
			cor_bolha(coluna->cor,x,y,raio);                  // desenha bola
			coluna = coluna->next;
		}
	}
}

void desenha_modo_debugg_vertical(int raio,MATRIZ* inicio,MATRIZ* fim,MATRIZ* v[],int COLUNAS,int LINHAS){

	int ymenor,ymaior,coluna;

	f_descobre_bola(&ymenor,&coluna,inicio,v,COLUNAS,LINHAS);
	f_descobre_bola(&ymaior,&coluna,fim,v,COLUNAS,LINHAS);
	for(int i = ymenor;i <= ymaior;i++)
		desenha_cruz(raio,LINHAS+2,coluna,i,f_acede_posicao(coluna,i,v,COLUNAS,LINHAS)->cor);

}

void desenha_modo_debugg_horizontal(int raio,MATRIZ* inicio,MATRIZ* fim,MATRIZ* v[],int COLUNAS,int LINHAS){

	int xmenor,xmaior,linha;

	f_descobre_bola(&linha,&xmenor,inicio,v,COLUNAS,LINHAS);
	f_descobre_bola(&linha,&xmaior,fim,v,COLUNAS,LINHAS);
	for(int i = xmenor;i <= xmaior;i++)
		desenha_cruz(raio,LINHAS+2,i,linha,f_acede_posicao(i,linha,v,COLUNAS,LINHAS)->cor);

}
