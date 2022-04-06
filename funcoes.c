#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "funcoes.h"

#define HORIZONTAL 0
#define VERTICAL 1

int inicia_matriz(int novo_jogo,MATRIZ *v[],int COLUNAS,int LINHAS,int aux1[LINHAS][COLUNAS]){

    MATRIZ *aux=NULL;
    MATRIZ *novo=NULL;

    int i,k,v1[10];
    for(int h = 1;h < 10;h++)
      v1[h] = 0;
    for(i=0;i<COLUNAS;i++){
      for(k=0;k<LINHAS;k++){
        novo=(MATRIZ *)calloc(1,sizeof(MATRIZ));
        if(novo==NULL)
          exit(0);    //Alocação mal sucedida
        if (k==0){
          v[i]=novo;    //Cabeças da lista
          novo->ant=NULL;
          aux=NULL;
        }
        novo->troca=0;                                                     /*As cabeças das listas guardam as bolas de baixo(posição LINHAS-1) porque as bolas*/
        novo->next=NULL;                                                   /*caem para baixo, e por isso para contaras bolas começa-se por baixo*/
        if(aux!=NULL)
          novo->ant=aux;
        if(aux!=NULL)
          aux->next=novo;

        aux=novo;    //O aux toma o valor de novo para ambos andarem desfazados
                     //para podermos fazer o apontador para ant.
        if(novo_jogo == 0){
          if(k>1){
            do{
              novo->cor=rand() % 9;
              novo->cor=novo->cor + 1;
              if(i>1){
                  while(f_acede_posicao(i-2,k,v,COLUNAS,LINHAS)->cor == f_acede_posicao(i-1,k,v,COLUNAS,LINHAS)->cor && f_acede_posicao(i-1,k,v,COLUNAS,LINHAS)->cor == novo->cor){
                  novo->cor=rand() % 9;
                  novo->cor=novo->cor + 1;
                  }
              }
            }while(aux->ant->ant->cor == aux->ant->cor && aux->ant->cor == novo->cor);
          }
          else{
            novo->cor=rand() % 9;
            novo->cor=novo->cor + 1;
            if(i>1){
                while(f_acede_posicao(i-2,k,v,COLUNAS,LINHAS)->cor == f_acede_posicao(i-1,k,v,COLUNAS,LINHAS)->cor && f_acede_posicao(i-1,k,v,COLUNAS,LINHAS)->cor == novo->cor){
                novo->cor=rand() % 9;
                novo->cor=novo->cor + 1;
                }
            }
          }
          aux1[k][i] = novo->cor;
          v1[novo->cor]++;                                            /*Desenhar as bolas no ecra vai se basear no x e y dos campos da MATRIZ*/
        }
        else
          novo->cor = aux1[k][i];
      }
    }
    for(int n = 1;n<10;n++){
      if((v1[n]%3) != 0)
        return 1;
    }
    return 0;
}
                                                                    /*VAI TER QUE SER MODIFICADA MAS O ACEESO AS LISTAS JA FICA */
MATRIZ  *f_acede_posicao(int x,int y,MATRIZ *v[],int COLUNAS,int LINHAS){

 int i;

 if(x<0 || y >= LINHAS || x >= COLUNAS || y<0)
    return NULL;                              //caso tente aceder a posição que não existe retorna NULL

 MATRIZ *aux=v[x];    //seleciona coluna

         for(i=0;i<y;i++){

         	  if (aux!=NULL)

              aux=aux->next;   //percorre a coluna

              else
              	return NULL;

         }


   return aux;

}

int f_analisa_troca(MATRIZ *v[],MATRIZ **tr1,MATRIZ **tr2,int COLUNAS,int LINHAS){        /*Verifica se a troca é possível e modifica *tr1 e *tr2 dando-lhes os endereços
                                                                      dos blocos para trocar*/
    int i;
    int k;
    int aux=0;



    for(i=0;i<COLUNAS;i++){
      	  for(k=0;k<LINHAS;k++){
              if(f_acede_posicao(i,k,v,COLUNAS,LINHAS)!=NULL){               //percorre todo o quadro de bolas em rpocura da primeira estrutura
                                                                            //com campo troca=1 (verifica sempre se o endereço acedido não
              	  if(f_acede_posicao(i,k,v,COLUNAS,LINHAS)->troca==1){      //é nulo, o que pode acontecer ,em sitios onde não há bola)
                	 *tr1=f_acede_posicao(i,k,v,COLUNAS,LINHAS);
                     aux=-1;     //o auxiliar apenas serve para sair do segundo for
                     break;
                     }
               }
           }
             if(aux==-1)   //foi descoberta a troca=1 e sai do ciclo
               break;
       }
        if (aux==0)
        	return -1;    /*Não se viu nenhuma bola marcada*/
        if((*tr1)->next!=NULL){             //Para nao dar segmentation fault ao aceder a um campo em endereço nulo(o end nunca deveria ser
             if((*tr1)->next->troca==1){    //nulo porque já é verificado em cima, mas torna o programa totalmente celado.
             	*tr2=(*tr1)->next;
                return VERTICAL;
             }
          }                        //verifica se existem bolas marcadas no eixo vertical, nas proximidades. Se houver o end2 é alterado por valor
        if((*tr1)->ant!=NULL){     //tal como o end1 e retorna VERTICAL para se ter informação de como se vai trocar a bola
            if((*tr1)->ant->troca==1){
               *tr2=(*tr1)->ant;
               return VERTICAL;
            }
           }
        if(f_acede_posicao(i+1,k,v,COLUNAS,LINHAS)!=NULL){
        	if(f_acede_posicao(i+1,k,v,COLUNAS,LINHAS)->troca==1){
        		*tr2=f_acede_posicao(i+1,k,v,COLUNAS,LINHAS);
           	    return HORIZONTAL;                          //faz a verificação, mas no eixo horizontal. Caso haja bola nas proximidades
           	}                                               //então retorna HORIZONTAL e altera o end2
        }
        if(f_acede_posicao(i-1,k,v,COLUNAS,LINHAS)!=NULL){
        	if(f_acede_posicao(i-1,k,v,COLUNAS,LINHAS)->troca==1){
        		*tr2=f_acede_posicao(i-1,k,v,COLUNAS,LINHAS);
           	    return HORIZONTAL;
           	}
        }
        return -1; //se não houverem bolas marcadas nas proximidades da bola encontrada
}

void f_limpa_selecoes(MATRIZ *v[],int COLUNAS,int LINHAS){

     int i,k;
     MATRIZ *aux=NULL;

     for(i=0;i<COLUNAS;i++){
           aux=v[i];                 //seleciona a coluna
           for(k=1;k<LINHAS;k++){

               if(aux!=NULL){       //percorre a coluna e coloca o campo de troca a 0
                 aux->troca=0;
                aux=aux->next;
                }
                if(aux!=NULL)
                aux->troca=0;     //para o a última posição na lista ser alterada, de outra forma não seria
         }
    }
}
/*NÃO ESQUECER que a função acede posição tem o refrencial das bolas de baixo para cima, por questão de conveniência*/
//A representação no ecrã é facilitada porque garantimos que em baixo há sempre bolas e ao rebentarem as bolas "caem" para o lado conveniente


void troca(MATRIZ *v[],MATRIZ *tr1,MATRIZ *tr2,int orientacao,int COLUNAS){

	MATRIZ *maior;
    MATRIZ *menor;
    MATRIZ *aux;
    int aux1,aux2;

 if(orientacao==VERTICAL){
           if(tr1->next==tr2){
           maior=tr2;                  //para saber qual está em cima de qual
           menor=tr1;
           }

           else if(tr2->next==tr1){
         	  maior=tr1;
         	  menor=tr2;

          }
            else{

         	 exit(0); //se tiver ocorrido um erro e não detetar bolas nas proximidades

            }
            /*No caso de estar na ultima casa*/
                              /*Se o tr1 tiver em ultimo, entao com a troca o tr2 fica em ultimo e com
            	                                                  a informaçao no vetor*/

           aux=menor->ant;

            if(menor->ant==NULL)
               v[f_casa_vetor(v,menor,COLUNAS)]=maior;
               else
               	aux->next=maior; //se nao tiver na ultima casa entao altera o campo next do que está atrás do menor(o bloco que estava atrás do maior)

           menor->next=maior->next;  //o menor aponta para onde apontava o maior
           menor->ant=maior;         //o maior fica "por trás" do menor
           maior->ant=aux;           //utiliza-se o aux para nao perder o end do ant do menor, que foi anteriormente alterado
           maior->next=menor;        //o menor fica por trás do maior portanto aponta para este

      }

   else if(orientacao==HORIZONTAL){


   	     aux=tr1->ant;

         if(tr1->next!=NULL || tr2->next!=NULL){      //Veridica se exitem bolas por cima do tr1 e tr2
            if(tr1->next!=NULL && tr2->next!=NULL){
               tr1->next->ant=tr2;                   //no caso de haverem bolas por cima dos dois então o procedimento é normal e o campo ant do seguinte
               tr2->next->ant=tr1;                   //é alterado (a bola que seguia tr1 fica ant=tr2 e a bola que seguia tr2 fica ant=tr1)

            }
            else if(tr1->next==NULL && tr2->next!=NULL){
              tr2->next->ant=tr1;                        //tr1 nao tem bolas à frente portanto o end do campo ant que segue a bola 2 passa a ser tr1
            }                                            // e não acontece mais nada porque nenhuma bola segue tr1
            else if(tr1->next!=NULL && tr2->next==NULL){
              tr1->next->ant=tr2;                        //no caso em que não se seguem bolas em tr2
            }

         }



   	     if(tr2->ant!=NULL){  //neste caso é indiferente no if se está tr1 ou tr2, porque se tudo correu bem tr2->ant!=NULL <=> tr1->ant!=NULL
   	     tr2->ant->next=tr1;
         tr1->ant->next=tr2;
         }

         /*if(aux!=NULL)       //desnecessário
         aux->next=tr2;*/

         tr1->ant=tr2->ant;
         tr2->ant=aux;   //aux usado de novo para não se perder o end do bloco anterior e seguinte
         aux=tr1->next;
         tr1->next=tr2->next;
         tr2->next=aux;


         if(tr1->ant==NULL){

         	aux1=f_casa_vetor(v,tr2,COLUNAS);  //estão na ultima linha portanto a troca altera o vetor com as cabeças das listas
         	aux2=f_casa_vetor(v,tr1,COLUNAS);  //a função f_casa_vetor procura a coluna em que está cada  bola
         	  /*Para nao perder os endereços*/

            v[aux1]=tr1;  //as bolas trocam de coluna

            v[aux2]=tr2;  //o end->ant de cada uma já foi alterado e permaneceu nulo e o next também

         }

   }

}

int f_casa_vetor(MATRIZ *v[],MATRIZ *end,int COLUNAS){/*AJUDA a funçao troca para indicar qual a posição no vetor da bola*/

     int i,k;

       for(i=0;i<COLUNAS;i++){

           if (end==v[i]){
           	   k=0;
           	   break;
           }

       }

       if(k==0)   /*É suposto que o ciclo acabe com k=0 para que tudo ocorra normalmente*/
       	return i;

       return -1;

   }

void f_elimina_vertical(MATRIZ *v[],MATRIZ *inicio,MATRIZ *fim,int COLUNAS){     /*Não verifica sentido*/
       MATRIZ *aux=NULL;
       MATRIZ *aux2=NULL;
       aux=inicio->next;

   	   while(aux!=fim){


   	   	   aux2=aux->next; //Usa-se o aux2 para dar free do aux sem se perder a continuidade da lista

   	   	   if (aux2==NULL)
   	   	   	  break;
              /*exit(0);*/ //Modei isto Simão

   	   	   free(aux);          //liberta os blocos de memoria entre o inicio e o fim das bolas que vao estourar
   	   	   /*fflush(stdout);*/

   	   	   aux=aux2;

   	   }

       /*fflush(stdout);*/

     if(inicio->ant==NULL){

      fflush(stdout);
     	v[f_casa_vetor(v,inicio,COLUNAS)]=fim->next; //É apagada a cabeça da lista e portanto é substituida peças bolas de cima

        if(fim->next!=NULL)
     	fim->next->ant=NULL;  //Se houver bolasna lista depois de eliminada, então a bola que fica na cabeça tem campo ant=NULL

     	free(inicio);
     	free(fim);   // finalmente apaga a primeira e ultima bola das bolas da mesma cor

       }
     else{
     	/*fflush(stdout);*/
      if(fim->next != NULL){
        inicio->ant->next=fim->next;   //cortam-se as bolas do inicio até ao fim e estabelece-se ligação entre a bola anterior e seguinte
     	  fim->next->ant=inicio->ant;


      }
      if(fim->next == NULL)
        inicio->ant->next = NULL;
     	free(inicio);
     	free(fim);
     }

    /*fflush(stdout);*/
 }

 void f_elimina_horizontal(MATRIZ *v[],MATRIZ *inicio,MATRIZ *fim,int COLUNAS,int LINHAS){
      MATRIZ *aux1;
      MATRIZ *aux2;
      int coluna=-1,linha=-1;
      int xmenor,xmaior,aux;

      if(inicio==NULL || fim==NULL)
        exit(0);

 f_descobre_bola(&linha, &coluna,inicio,v,COLUNAS,LINHAS);   //descobre a linha e coluna do inicio e do fim
 xmenor=coluna;

 f_descobre_bola(&linha, &coluna,fim,v,COLUNAS,LINHAS);

 xmaior=coluna;

 if(xmaior<xmenor){
 	aux=xmaior;
 	xmaior=xmenor;     //verifica qual o xmaior e menor
 	xmenor=aux;

 }

 if(linha==0){


 	 for(xmenor;xmenor<=xmaior;xmenor++){    //se a linha==0 então altera o vetor de cabeças das listas e substitui pelas bolas seguintes
     	aux1=v[xmenor];
    	v[xmenor]=v[xmenor]->next;
    	if(v[xmenor]!=NULL)
    	v[xmenor]->ant=NULL;
    	free(aux1);        //liberta o bloco eliminado
        }

    }

 else{

 	     for(xmenor;xmenor<=xmaior;xmenor++){
         aux1=f_acede_posicao(xmenor,linha,v,COLUNAS,LINHAS);   //acede a todas as posições entre o primeiro e ultimo elemento(percorre linha)
         if(aux1 == NULL){
          break;
         }
           if(aux1->next!=NULL){
     	   aux1->next->ant=aux1->ant;     //estabelece novas ligações
    	   aux1->ant->next=aux1->next;
    	   }
    	   else{
    	   	aux1->ant->next=NULL;
    	   }
    	  free(aux1);
           }

       }
 }

 MATRIZ *f_descobre_bola(int *linha, int *coluna,MATRIZ *end,MATRIZ *v[],int COLUNAS,int LINHAS){

 	  int i,k,l;
      MATRIZ *aux;

 	  for(i=0;i<COLUNAS;i++){
          aux=v[i];
          for(k=0;k<LINHAS;k++){

               if(end==aux){      //Percorre coluna a coluna, quando encontrar o endereço igual a end, então devolve por endereço
              	   *coluna=i;     // k (linhas) e i(colunas)
               	   *linha=k;

                   return end;
                  }
             if(aux!=NULL)
             aux=aux->next;
           }

 	  }

 	  return NULL; /*se nao encontra*/

 }

int verifica_troca(MATRIZ* bola){
  if(bola->troca)
 		return 1;
	return 0;
}

int adquire_posicao_x(int rato_x,int COLUNAS,int raio){
	float x;
	x = (float)(rato_x-raio)/(float)(2*raio);
	if(x >= (int) x + 0.5)
		return (int)x+1;
	else
		return (int)x;
}

int adquire_posicao_y(int rato_y,int LINHAS,int raio){
	float y;
	y = (float)(rato_y-(LINHAS)*2*raio+2*raio)/(float)(-2*raio);
	if(y >= (int) y + 0.5)
		return (int)y+1;
	else
		return (int)y;
}

int f_verifica_horizontal(MATRIZ *v[],MATRIZ **end1, MATRIZ **end2,int COLUNAS,int LINHAS){
   int i,k,l=0,cor_aux,k_max=-1;

   for(i=0;i<LINHAS;i++){

        for(k=0;k<COLUNAS;k++){
        	k_max++; //serve apenas para quando o ciclo acaba, porque o k é uma variável interna ao ciclo

            if(l==0){
                *end1=f_acede_posicao(k,i,v,COLUNAS,LINHAS);  //corre as linhas
                    if(*end1!=NULL){
                 	   cor_aux=(*end1)->cor;             //fica com a cor marcada

                      }
             }

            if(f_acede_posicao(k,i,v,COLUNAS,LINHAS)!=NULL){
            	if(f_acede_posicao(k,i,v,COLUNAS,LINHAS)->cor==cor_aux)                           //se for igual soma 1 a l
            		l++;                                                                            //se l=0, entao no primeiro ciclo fica logo l=1, porque soma
            	else if(l<3 && f_acede_posicao(k,i,v,COLUNAS,LINHAS)->cor!=cor_aux ){            //porque cor_aux=f_aced...->cor
                    cor_aux=f_acede_posicao(k,i,v,COLUNAS,LINHAS)->cor;                        //se l=1, entao se a cor for igual a f_aced...->cor entao soma+1
            		l=1;                                                                          //até chegar a 3
            		*end1=f_acede_posicao(k,i,v,COLUNAS,LINHAS); //a cor é diferente e o lfica=1 porque no proximo ciclo aparece uma nova cor
            	}                                              //se for igual à anterior entao soma +1
            	else if(f_acede_posicao(k,i,v,COLUNAS,LINHAS)->cor!=cor_aux && l>=3){
            		*end2=f_acede_posicao(k-1,i,v,COLUNAS,LINHAS);  //pelo menos 3 bolas seguidas da mesma cor, mas o ciclo continuou a correr
                                                        //e foi encontrada uma nova bola de cor diferente, portanto fica-se com o end2
                    return l;                                   //porque é o endereço (na mesma linha) na coluna anterior
                }
            }



            if(l>=3 && f_acede_posicao(k,i,v,COLUNAS,LINHAS)==NULL){   //situação parecida com a anterior, mas encontra-se endereço nulo nessa linha
            	*end2=f_acede_posicao(k-1,i,v,COLUNAS,LINHAS);

              return l;
            }

            else if(l<3 && f_acede_posicao(k,i,v,COLUNAS,LINHAS) == NULL){
              l = 0;
            }

        }

        if(l>=3){
        	*end2=f_acede_posicao(k_max,i,v,COLUNAS,LINHAS);   //encontram-se 3 bolas seguidas mas entretanto o ciclo troca de linha

            return l;                                        //a ultima bola é a bola da coluna kmax e da linha i
        }
        k_max=-1;    //para acompanhar o k nas iterações

        l=0;
   }

return -1;

}


int f_verifica_vertical(MATRIZ *v[],MATRIZ **end1,MATRIZ **end2,int COLUNAS,int LINHAS){

   int i,k,l=0,cor_aux,i_max=-1;


   for(k=0;k<COLUNAS;k++){

        for(i=0;i<LINHAS;i++){
            i_max++;

            if(l==0){
                *end1=f_acede_posicao(k,i,v,COLUNAS,LINHAS);      //prototipo igual à função que verifica horizontal mas
                    if(*end1!=NULL){                              //percorre colunas
                       cor_aux=(*end1)->cor;
                      }
             }

            if(f_acede_posicao(k,i,v,COLUNAS,LINHAS)!=NULL){
                if(f_acede_posicao(k,i,v,COLUNAS,LINHAS)->cor==cor_aux)
                    l++;
                else if(l<3 && f_acede_posicao(k,i,v,COLUNAS,LINHAS)->cor!=cor_aux ){
                    cor_aux=f_acede_posicao(k,i,v,COLUNAS,LINHAS)->cor;
                    l=1;
                    *end1=f_acede_posicao(k,i,v,COLUNAS,LINHAS);
                }
                else if(f_acede_posicao(k,i,v,COLUNAS,LINHAS)->cor!=cor_aux && l>=3){ /*teste*/
                    *end2=f_acede_posicao(k,i-1,v,COLUNAS,LINHAS);

                    return l;
                }
            }

            if(l>=3 && f_acede_posicao(k,i,v,COLUNAS,LINHAS)==NULL){
                *end2=f_acede_posicao(k,i-1,v,COLUNAS,LINHAS);

                return l;
            }

        }

        if(l>=3){
            *end2=f_acede_posicao(k,i_max,v,COLUNAS,LINHAS);

            return l;
        }
        i_max=-1;

        l=0;


   }

return -1;
}

void copia_matriz(int COLUNAS,int LINHAS,int aux[LINHAS][COLUNAS],MATRIZ* v[],int v1[COLUNAS]){
  MATRIZ* coluna;
  int a,b;
  for(a=0;a<COLUNAS;a++){
    do{                                                                                     //verifica se existem bolas nessa linha
      coluna = v[a];
      if(coluna == NULL){
        v1[a] = 0;
        a++;
      }
    }while(coluna == NULL && a != COLUNAS);
		for(b=0;b<LINHAS;b++){
			if(coluna == NULL)
        break;
      aux[b][a] = f_acede_posicao(a,b,v,COLUNAS,LINHAS)->cor;                                             //copia cor e guarda
			coluna = coluna->next;
		}
    if(a != COLUNAS)
      v1[a] = b;
  }
}

void reescreve_matriz(MATRIZ *v[],int COLUNAS,int LINHAS,int aux1[LINHAS][COLUNAS],int v1[COLUNAS]){

    MATRIZ *aux=NULL;
    MATRIZ *novo=NULL;

    int i,k;
    for(i=0;i<COLUNAS;i++){
      for(k=0;k<v1[i];k++){
        novo=(MATRIZ *)calloc(1,sizeof(MATRIZ));
        if(novo==NULL)
          exit(0);
        if (k==0){
          v[i]=novo;
          novo->ant=NULL;
          aux=NULL;
        }
        novo->cor = aux1[k][i];                                             //copia cor
        novo->troca=0;
        novo->next=NULL;
        if(aux!=NULL)
          novo->ant=aux;
        if(aux!=NULL)
          aux->next=novo;
        aux=novo;
      }
    }
}

void limpa_matriz(MATRIZ* v[],int COLUNAS,int v1[COLUNAS]){                    // limpa matrizes auxiliares
  int i,j;
  MATRIZ* aux,*aux1;

  for(i=0;i<COLUNAS;i++){
    while(v1[i] == 0)
      i++;
    if(i == COLUNAS)
      break;
    aux1 = v[i];
    for(j=0;j<v1[i];j++){
      aux = aux1;
      aux1 = aux1->next;
      free(aux);
    }
  }

}

void tamanhomatriz(int COLUNAS,int LINHAS,MATRIZ* v[],int v1[COLUNAS]){                   //da o vetor com o tamanho da matriz
  MATRIZ* coluna = NULL;
  int a,b;
  for(a=0;a<COLUNAS;a++){
    do{
      coluna = v[a];
      if(coluna == NULL){
        v1[a] = 0;
        a++;
      }
    }while(coluna == NULL && a != COLUNAS);
		for(b=0;b<LINHAS;b++){
			if(coluna == NULL)
        break;
			coluna = coluna->next;
		}
    if(a != COLUNAS)
      v1[a] = b;
  }
}
