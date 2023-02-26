// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
// Pedro Mesquita Praca a2020130980

#ifndef SEMAFORO_H
#define SEMAFORO_H

typedef struct struct_jogada {
	int num_jogada; 	//número da jogada
	int jogador; 		//jogador
	char opcao_jogada;  //tipo de jogada
	int linha_jogada;	//linha da jogada (qd inserida)
	int coluna_jogada;	//coluna da jogada (qd inserida)
	int nlinhas_tabuleiro;	//numero de linhas do tabuleiro
	int ncolunas_tabuleiro;		//numero de colunas do tabuleiro
	struct struct_jogada *proximo; //ponteiro que aponta para a proxima struct
} sjogada;

//Coloca todas as posicoes do tabuleiro com _
void limpa_tabuleiro(char **matriz, int l, int c);

//liberta a memoria ocupada pelo array do tabuleiro
void liberta_array(char **matriz, int l);

//Mostra tabuleiro na consola
void mostra_tabuleiro(char **matriz, int l, int c);

//Aloca memoria para o tabuleiro
char **dim_matriz( int l, int c);

//Aumenta o tamanho do tabuleiro em 1 linha
char **redim_linha_matriz(char **matriz, int l, int c);

//Aumenta o tamanho do tabuleiro em 1 coluna
char **redim_col_matriz(char **matriz, int l, int c);


//Mostra legenda com jogadas possiveis
void mostra_legenda();

//Pede opcao ao utilizador
char pede_opcao(char **matriz, int l, int c, int njogador);

//verifica se ainda ha casas vazias no tabuleiro
int ve_casas_vazias(char **matriz, int l, int c);

//Pede linha ou coluna ao utilizador
void pede_lc(int l, int c, int *x, int *y);

//valida jogada
int valida_jogada(char ** matriz, int row, int col, char opcao, int x, int y);

//verifica se jogada vence
int jogada_vencedora(char ** matriz, int row, int col);

//introducao e validacao de quantidade de jogadas a mostrar
int pede_njogadas(int conta_jogadas);

//Espera por utilizador premir Esc
//retirada de https://stackoverflow.com/questions/21091191/implementing-a-keypress-event-in-c
void pressEsc(void);
#endif /* SEMAFORO_H */
