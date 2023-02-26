/* Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2020-2021
 * Pedro Mesquita Praca a2020130980
 *
 * Funcoes relacionadas com o tabuleiro de jogo do Semaforo
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "semaforo.h"

//Coloca todas as posicoes do tabuleiro com _
void limpa_tabuleiro(char **matriz, int l, int c)
{
	int i, j;

	for (i = 0; i < l; i++) {
      for (j = 0; j < c; j++) {
		matriz[i][j] = '_';
      }
      printf("\n");
   }
}

//liberta a memoria ocupada pelo array do tabuleiro
void liberta_array(char **matriz, int l)
{
	int i;

	for (i = 0; i < l; i++) {
		free(matriz[i]);
	}
	free(matriz);

}

//Mostra tabuleiro na consola
void mostra_tabuleiro(char **matriz, int l, int c)
{
	int i, j;

	printf("\n   ");
	for (j = 0; j < c; j++) {
		printf(" %d ", j+1);
	}
	printf("\n   ");
	for (j = 0; j < c; j++) {
		printf("---");
	}
	printf("\n");
	for (i = 0; i < l; i++) {
	  printf(" %d|", i+1);
      for (j = 0; j < c; j++) {

         printf(" %c ", matriz[i][j]);
      }
      printf("\n");
   }
}

//Aloca memoria para o tabuleiro
char **dim_matriz( int l, int c)
{
	char **matriz;
	int i;
	matriz = malloc(l * sizeof(char *)); //Aloca os ponteiros da linha
	for(i = 0; i < l; i++)
	  matriz[i] = malloc(c * sizeof(char));  //Aloca cada linha separadamente

	return matriz;
}

//Aumenta o tamanho do tabuleiro em 1 linha
char **redim_linha_matriz(char **matriz, int l, int c)
{

	int i;


	char **tmp = realloc( matriz, sizeof matriz * (l + 1) );
	//verifica se conseguiu fzr realloc das linhas da matriz
	if ( tmp )
	{
            //aloca espaço para cada coluna
			tmp[l] = malloc( sizeof tmp[l] * c );
	}
	for (i=0; i<c; i++)
	{
		tmp[l][i] = '_';
	}

	return tmp;
}

//Aumenta o tamanho do tabuleiro em 1 coluna
char **redim_col_matriz(char **matriz, int l, int c)
{
	int i;

    //percorre linhas da matriz
	for (  i = 0; i < l; i++ )
	{
	    //acrescenta coluna á linha atual
		int *tmp = realloc( matriz[i], sizeof matriz[i] * (c + 1) );
		if ( tmp )
		{
			matriz[i] = tmp;
		}
	}
	for (i=0; i<l; i++)
	{
		matriz[i][c] = '_';
	}
	return matriz;
}

//Mostra legenda com jogadas possiveis
void mostra_legenda()
{
		printf("\n Opcoes:");
		printf("\n    G: peca verde");
		printf("\n    Y: peca amarela");
		printf("\n    R: peca vermelha");
		printf("\n    P: pedra");
		printf("\n    C: acrescentar coluna");
		printf("\n    L: acrescentar linha");
		printf("\n\n    V: ver ultimas jogadas\n");
		printf("\n    A: Mostrar todas a jogadas");
		printf("\n    T: terminar");
}

//Pede opcao ao utilizador
char pede_opcao(char **matriz, int l, int c, int njogador)
{
   char opcao;
   int valida = 0;

   do{
	   limpa_ecran(25);

	   printf("\n *** Jogo do semaforo *** \n");

	   mostra_tabuleiro(matriz, l, c);
	   printf("\n");
	   mostra_legenda();
	   printf("\n");
	   printf("\nIndique a sua jogada, jogador %d: ", njogador);
	   scanf(" %c", &opcao);

	   opcao = toupper(opcao); //coloca em caps

	   if (opcao == 'R' || opcao == 'G' || opcao == 'Y' || opcao == 'T' || opcao == 'P' || opcao == 'C' || opcao == 'L' || opcao == 'V' || opcao == 'A'){
		   valida = 1;
	   }
	   else
	   {
		   printf("\n\n *********************");
		   printf("\n *** Opcao errada! ***");
		   printf("\n *********************\n\n");
	   }
   }
   while (valida == 0);

	return opcao;
}

//Pede linha e coluna ao utilizador (coordenadas do tabuleiro)
void pede_lc(int l, int c, int *x, int *y)
{
   char opcaox[20], opcaoy[20]; //strings para introdução das coordenadas
   int valida = 0;

   do{

	   printf("\nIndique a linha [1 - %d]: ", l);
	   scanf(" %c", opcaox);                          //%c para prevenir que o programa estoura

	   printf("\nIndique a coluna [1 - %d]: ", c);
	   scanf(" %c", opcaoy);

	   *x = atoi(opcaox); //tenta converter para inteiro
	   *y = atoi(opcaoy);

       //verifica se as coordenadas sao validas
	   if ( *x >= 1 && *x <= l && *y >=1 && *y<= c)
	   {
		   valida = 1; //valores validos
	   }
	   else
	   {
		   printf("\n\n **************************");
		   printf("\n *** Valores invalidos! ***");
		   printf("\n **************************\n\n");
	   }
   }
   while (valida == 0);

}


//verifica se ainda ha casas vazias no tabuleiro
int ve_casas_vazias(char **matriz, int l, int c)
{
	int i, j;

	for (i = 0; i < l; i++) {

      for (j = 0; j < c; j++) {

		if ( matriz[i][j] == '_')
			return 1;

      }
    }
    return 0;
}

//valida jogada
int valida_jogada(char ** matriz, int row, int col, char opcao, int x, int y)
{
	//se opcao = pedra
	if (opcao == 'P'){
		//verifica se a casa do tabuleiro esta vazia
		if ( matriz[x-1][y-1] == '_' )
		{
			matriz[x-1][y-1] = 'o'; //regista pedra
		}
		else
		{
			return 0;
		}
	}
	//se opcao = verde
	if (opcao == 'G'){
		//verifica se a casa do tabuleiro esta vazia
		if ( matriz[x-1][y-1] == '_' )
		{
			matriz[x-1][y-1] = 'G'; //regista verde
		}
		else
		{
			return 0;
		}
	}
	//se opcao = amarelo
	if (opcao == 'Y'){
		//verifica se a casa do tabuleiro tem peca verde
		if ( matriz[x-1][y-1] == 'G' )
		{
			matriz[x-1][y-1] = 'Y'; //regista amarelo
		}
		else
		{
			return 0;
		}
	}
	//se opcao = vermelho
	if (opcao == 'R'){
		//verifica se a casa do tabuleiro tem peca amarela
		if ( matriz[x-1][y-1] == 'Y' )
		{
			matriz[x-1][y-1] = 'R'; //regista vermelho
		}
		else
		{
			return 0;
		}
	}
	return 1;
}

//verifica se jogada vence
int jogada_vencedora(char **matriz, int row, int col)
{
	int i, j;
	int vence;
	//Verifica linhas

	for (i = 0; i < row; i++)
	{
		vence = 1;       //foi a jogadora vencedora até provar contrario

		//primeira celula vazia?
		if (matriz[i][0] == '_')
		{
			vence = 0;
		}
		else
		{
			for (j = 1; j < col; j++)
			{
				//se alguma celula for diferente da anterior ou vazia
				if ( (matriz[i][j-1] != matriz[i][j]) || (matriz[i][j] == '_') )
				{
					vence = 0;
				}
			}
		}
		//se vence == 1 entao a linha e toda igual
		if (vence == 1)
		{
			return 1;
		}
	}


	for (i = 0; i < col; i++)
	{
		vence = 1;

		//primeira celula vazia?
		if (matriz[0][i] == '_')
		{
			vence = 0;
		}
		else
		{
			for (j = 1; j < row; j++)
			{
				//se alguma celula da linha for diferente da anterior ou vazia
				if ( (matriz[j-1][i] != matriz[j][i]) || (matriz[j][i] == '_') )
				{
					vence = 0;
				}
			}
		}
		//se vence == 1 entao a coluna e toda igual
		if (vence == 1)
		{
			return 1;
		}
	}

	//verifica diagonais se matriz quadrada
	if (row == col)
	{
		vence = 1;
		if (matriz[0][0] == '_')
		{
			vence = 0;
		}
		else
		{
			for (i = 1; i < row; i++)
			{
				if (matriz[i][i] != matriz[i-1][i-1])
				{
					vence = 0;
				}
			}
		}
		if (vence == 1)
		{
			return 1;
		}

		//verifica a outra diagonal
		vence = 1;
		if (matriz[0][col-1] == '_')
		{
			vence = 0;
		}
		else
		{
			for (i = 1; i < row; i++)
			{
				if (matriz[i][col-1-i] != matriz[i-1][col-i])
				{
					vence = 0;
				}
			}
		}
		if (vence == 1)
		{
			return 1;
		}
	}


	return 0;
}

//introducao e validacao de quantidade de jogadas a mostrar
int pede_njogadas(int conta_jogadas)
{
   char opcao[20]; //string para introdução das coordenadas
   int valida = 0;
   int n;

   do{

	   printf("\nIndique quantas jogadas quer visualizar [1 - %d]: ", conta_jogadas);
	   scanf(" %c", opcao);


	   n = atoi(opcao); //tenta converter para inteiro


	   if ( n >= 1 && n <= conta_jogadas)
	   {
		   valida = 1; //valor valido
	   }
	   else
	   {
		   printf("\n\n ***********************");
		   printf("\n *** Valor invalido! ***");
		   printf("\n ***********************\n\n");
	   }
   }
   while (valida == 0);

  return n;
}

//Espera por utilizador premir Esc
//retirada de https://stackoverflow.com/questions/21091191/implementing-a-keypress-event-in-c
void pressEsc(void)
{
	int c;
	printf("\n\n Prima Esc para continuar\n");
	//fica num ciclo á espera de uma tecla
	while((c = getch()) != EOF ) // EOF - end of file
		if(c == 27)   return; //codigo ascii de ESC
}
