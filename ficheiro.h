typedef struct linha {
	char nome[11];
	int pontos;
	int eof;
} linha_t;

linha_t le_ficheiro(FILE *fp);
linha_t obtem_linha(int pontuacao);
void escreve_ficheiro(FILE *fp, linha_t linha);
int escrever_nova_pontuacao(linha_t userline);
