typedef struct matriz {
int troca,cor,numero;
struct matriz *next;
struct matriz *ant;
}MATRIZ;

int inicia_matriz(int novo_jogo,MATRIZ *v[],int COLUNAS,int LINHAS,int aux1[LINHAS][COLUNAS]);
MATRIZ *f_acede_posicao(int x,int y,MATRIZ *v[],int COLUNAS,int LINHAS);
int f_analisa_troca(MATRIZ *v[],MATRIZ **tr1,MATRIZ **tr2,int COLUNAS,int LINHAS);
void f_limpa_selecoes(MATRIZ *v[],int COLUNAS,int LINHAS);
void troca(MATRIZ *v[],MATRIZ *tr1,MATRIZ *tr2,int orientacao,int COLUNAS);
int f_casa_vetor(MATRIZ *v[],MATRIZ *end,int COLUNAS);
void f_elimina_vertical(MATRIZ *v[],MATRIZ *inicio,MATRIZ *fim,int COLUNAS);
void f_elimina_horizontal(MATRIZ *v[],MATRIZ *inicio,MATRIZ *fim,int COLUNAS,int LINHAS);
MATRIZ *f_descobre_bola(int *linha, int *coluna,MATRIZ *end,MATRIZ *v[],int COLUNAS,int LINHAS);
int verifica_troca(MATRIZ* bola);
int adquire_posicao_x(int rato_x,int COLUNAS,int raio);
int adquire_posicao_y(int rato_y,int LINHAS,int raio);
int f_verifica_horizontal(MATRIZ *v[],MATRIZ **end1,MATRIZ **end2,int COLUNAS,int LINHAS);
int f_verifica_vertical(MATRIZ *v[],MATRIZ **end1,MATRIZ **end2,int COLUNAS,int LINHAS);
void copia_matriz(int COLUNAS,int LINHAS,int aux[LINHAS][COLUNAS],MATRIZ* v[],int v1[COLUNAS]);
void reescreve_matriz(MATRIZ *v[],int COLUNAS,int LINHAS,int aux1[LINHAS][COLUNAS],int v1[COLUNAS]);
void limpa_matriz(MATRIZ* v[],int COLUNAS,int v1[COLUNAS]);
void tamanhomatriz(int COLUNAS,int LINHAS,MATRIZ* v[],int v1[COLUNAS]);
