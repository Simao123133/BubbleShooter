#include <stdio.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "grafica.h"

SDL_Window* g_pWindow = NULL;
SDL_Renderer* g_pRenderer = NULL;

void cor_bolha(int cor, int px, int py, int raio){       // desenha de acordo com a cor,posiçao,raio

	if(cor == 1)
	{
		SDL_SetRenderDrawColor( g_pRenderer,254,221,0,255);
		filledCircleRGBA(g_pRenderer, px, py, raio, 254, 221, 0, 255);
		circleRGBA(g_pRenderer, px, py, raio, 0,0,0,255);
	}

  if(cor == 2)
	{
		SDL_SetRenderDrawColor( g_pRenderer,16,6,159,255);
		filledCircleRGBA(g_pRenderer, px, py, raio, 16, 6, 159, 255);
		circleRGBA(g_pRenderer, px, py, raio, 0,0,0,255);
	}

  if(cor == 3)
	{
		SDL_SetRenderDrawColor( g_pRenderer,0,171,132,255);
		circleRGBA(g_pRenderer, px, py, raio, 0,0,0,255);
		filledCircleRGBA(g_pRenderer, px, py, raio, 0, 171, 132, 255);
	}

  if(cor == 4)
	{
		SDL_SetRenderDrawColor( g_pRenderer,187,41,187,255);
		circleRGBA(g_pRenderer, px, py, raio,0,0,0,255);
		filledCircleRGBA(g_pRenderer, px, py, raio, 187,41,187, 255);
	}

  if(cor == 5)
	{
		SDL_SetRenderDrawColor( g_pRenderer,0,175,215,255);
		filledCircleRGBA(g_pRenderer, px, py, raio, 0, 175, 215, 255);
		circleRGBA(g_pRenderer, px, py, raio, 0,0,0,255);
	}

  if(cor == 6)
	{
		SDL_SetRenderDrawColor( g_pRenderer,239,51,64,255);
		filledCircleRGBA(g_pRenderer, px, py, raio, 239, 51, 64, 255);
		circleRGBA(g_pRenderer, px, py, raio, 0,0,0,255);
	}

  if(cor == 7)
	{
		SDL_SetRenderDrawColor( g_pRenderer,132,117,78,255);
		filledCircleRGBA(g_pRenderer, px, py, raio, 132, 117, 78, 255);
		circleRGBA(g_pRenderer, px, py, raio, 0,0,0,255);
	}

  if(cor == 8)
	{
		SDL_SetRenderDrawColor( g_pRenderer,0,0,0,255);
		filledCircleRGBA(g_pRenderer, px, py, raio, 0, 0, 0, 255);
		circleRGBA(g_pRenderer, px, py, raio, 0,0,0,255);
	}

  if(cor == 9)
	{
		SDL_SetRenderDrawColor( g_pRenderer,255,255,255,255);
		filledCircleRGBA(g_pRenderer, px, py, raio, 255, 255,255, 255);
		circleRGBA(g_pRenderer, px, py, raio, 0,0,0,255);
	}

}

int criar_janela(int windowsizex,int windowsizey){    //cria janela

	if(SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		g_pWindow = SDL_CreateWindow("BOLHAS",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,windowsizex,windowsizey,SDL_WINDOW_SHOWN);
		if(g_pWindow != NULL)
		{
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
		}
	}
	else
	{
		return 1;
	}
	return 0;
}

void texto(int windowsizex,int windowsizey,int raio){  // escreve o texto

  char nj[] ="NOVO JOGO", f[]="FIM", p[]="PONTOS:";

	SDL_SetRenderDrawColor( g_pRenderer, 50, 90, 200, 255 );
	SDL_RenderDrawLine(g_pRenderer,0,0,windowsizex-1,0);
	SDL_RenderDrawLine(g_pRenderer,0,0,0,windowsizey-1);
	SDL_RenderDrawLine(g_pRenderer,windowsizex-1,0,windowsizex-1,windowsizey-1);
	SDL_RenderDrawLine(g_pRenderer,0,windowsizey-1,windowsizex-1,windowsizey-1);
	SDL_RenderDrawLine(g_pRenderer,0,3*raio/1.2,windowsizex,3*raio/1.2);

	SDL_SetRenderDrawColor( g_pRenderer, 0, 0, 0, 255 );
	SDL_RenderDrawLine(g_pRenderer,raio,raio,windowsizex/5,raio);
	SDL_RenderDrawLine(g_pRenderer,raio,raio,raio,2*raio);
	SDL_RenderDrawLine(g_pRenderer,windowsizex/5,raio,windowsizex/5,raio*2);
	SDL_RenderDrawLine(g_pRenderer,raio,2*raio,windowsizex/5,2*raio);

	SDL_RenderDrawLine(g_pRenderer,windowsizex/4.5,raio,windowsizex/3.3,raio);
	SDL_RenderDrawLine(g_pRenderer,windowsizex/4.5,raio,windowsizex/4.5,2*raio);
	SDL_RenderDrawLine(g_pRenderer,windowsizex/3.3,raio,windowsizex/3.3,2*raio);
	SDL_RenderDrawLine(g_pRenderer,windowsizex/4.5,2*raio,windowsizex/3.3,2*raio);

	SDL_RenderDrawLine(g_pRenderer,windowsizex/1.9,raio,windowsizex/1.4,raio);
	SDL_RenderDrawLine(g_pRenderer,windowsizex/1.9,raio,windowsizex/1.9,raio*2);
	SDL_RenderDrawLine(g_pRenderer,windowsizex/1.4,raio,windowsizex/1.4,raio*2);
	SDL_RenderDrawLine(g_pRenderer,windowsizex/1.9,raio*2,windowsizex/1.4,raio*2);

	stringRGBA(g_pRenderer, windowsizex/13, raio*1.4, nj, 0, 0, 0, 255);
	stringRGBA(g_pRenderer, windowsizex/3.95, raio*1.4, f, 0, 0, 0, 255);
	stringRGBA(g_pRenderer, windowsizex/1.75, raio*1.4, p, 0, 0, 0, 255);

}
																																									//como existe uma biblioteca separada para a parte grafica
void pinta_janela (void){                                                         //foi necessario cria funçoes especificas para a main
	SDL_SetRenderDrawColor(g_pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(g_pRenderer);
}

void apresenta_janela (void){
	SDL_RenderPresent(g_pRenderer);
}

void desenha_cruz(int raio,int LINHAS,int i,int j,int cor){                    //desenha cruz nas bolas de acordo com posicao
	if(cor == 8)                                                                 // no ecra
		SDL_SetRenderDrawColor(g_pRenderer,255,255,255,255);
	else
		SDL_SetRenderDrawColor(g_pRenderer,0,0,0,255);
	SDL_RenderDrawLine(g_pRenderer,2*raio*i+raio/2,LINHAS*2*raio-2*raio*j-2*raio,2*raio*i+(3*raio)/2,LINHAS*2*raio-2*raio*j-2*raio);
	SDL_RenderDrawLine(g_pRenderer,2*raio*i+raio,LINHAS*2*raio-2*raio*j-1.5*raio,2*raio*i+raio,LINHAS*2*raio-2*raio*j-2.5*raio);
}

void mostra_pontuacao(char pontinhos[],int raio,int windowsizex){                             //mostra a pontuacao
	stringRGBA(g_pRenderer, windowsizex/1.5, raio*1.4, pontinhos, 0, 0, 0, 255);
}

void limpa_janela(void){
	SDL_RenderClear(g_pRenderer);
}
