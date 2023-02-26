/* Trabalho Pratico Programacao - LEI
* DEIS-ISEC 2020-2021
* Pedro Mesquita Praca a2020130980
*/

#include "utils.h"
#include "semaforo.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>




//liberta lista
void liberta_lista(sjogada *ponteiro){ //liberta struct a struct desde o inicio até ao fim

	sjogada *proximo = NULL;
	sjogada *atual = NULL;

	atual = ponteiro;
	while (atual != NULL)
	{
		proximo = atual->proximo;
		free(atual);
		atual = proximo;
	}

};

//Regista jogada
sjogada *Regista_jogada(sjogada *ponteiro_ultimo, int nlinhas, int ncolunas, int num_jogada, char opcao_jogada, int linha_jogada, int coluna_jogada, int num_jogador)
{
	sjogada *ponteiro = NULL;

	ponteiro = (sjogada *) malloc(sizeof(sjogada)); //cria espaço em memoria para a struct da jogada e devolve endereço

	//Se não for a primeira jogada, altera a última jogada registada, indicando o ponteiro da seguinte (esta nova)
	if (num_jogada > 1)
	{
		ponteiro_ultimo->proximo = ponteiro; //indica o ponteiro da seguinte
	}

	//Regista dados
	ponteiro->proximo = NULL;
	ponteiro->num_jogada = num_jogada;
	ponteiro->jogador = num_jogador;
	ponteiro->opcao_jogada = opcao_jogada;
	ponteiro->linha_jogada = linha_jogada;
	ponteiro->coluna_jogada = coluna_jogada;
	ponteiro->nlinhas_tabuleiro = nlinhas;
	ponteiro->ncolunas_tabuleiro = ncolunas;

	return ponteiro;
};


//Mostra ultimas n jogadas
//constroi tabuleiro com base em todas as jogadas
//so mostra as ultimas pedidas
void Mostra_jogadas(sjogada *primeiro, sjogada *ultimo, int mostranjogadas)
{
	char **matriztemporaria = NULL;
	sjogada *ponteiro = NULL;
	int i;

	//Cria a matriz temporaria com base na dimensao atual do tabuleiro
	//apenas mostrara tabuleiro com as dimensoes registadas em cada jogada
	matriztemporaria = dim_matriz(ultimo->nlinhas_tabuleiro, ultimo->ncolunas_tabuleiro);

	limpa_tabuleiro(matriztemporaria, ultimo->nlinhas_tabuleiro, ultimo->ncolunas_tabuleiro);

	ponteiro = primeiro;

	printf("\n *** Jogo do semaforo *** \n");
	//percorre todas as jogadas já feitas e constroi o tabuleiro
	for (i=1; i<=(ultimo->num_jogada); i++)
	{
		//se for jogada com coordenadas
		//regista na posicao correta (linha - 1 e coluna - 1)
		//sendo aumento de linha ou coluna, nao necessita de nada pq as linhas e colunas da struct servem
		if (ponteiro->opcao_jogada == 'G' || ponteiro->opcao_jogada == 'Y' || ponteiro->opcao_jogada == 'R' || ponteiro->opcao_jogada == 'o')
		{

			matriztemporaria[ponteiro->linha_jogada-1][ponteiro->coluna_jogada-1] = ponteiro->opcao_jogada;
		}

		if (i > (ultimo->num_jogada - mostranjogadas) ) //mostra apenas as ultimas n jogadas
		{
			//mostra tabuleiro
			printf("\n *** Jogada # %d *** \n", i);
			mostra_tabuleiro(matriztemporaria, ponteiro->nlinhas_tabuleiro, ponteiro->ncolunas_tabuleiro);
		}

		ponteiro = ponteiro->proximo; //o ponteiro passa a apontar para a jogada seguinte

	}

    //liberta a memoria da matriz temporaria
	liberta_array(matriztemporaria, ultimo->nlinhas_tabuleiro);

}

int main()
{
	int row, col; //linha e coluna
	int conta_jogadas; //contador do nº ede jogadas
	int njogador; //jogador atual
	int p1_pedra, p2_pedra; //contadores de pedras acrescentadas por cada jogador
	int p1_lc, p2_lc; //contadores de linhas e/ou colunas acrescentadas por cada jogador
	int casas_vazias;
	int x=0, y=0, njogadas=0;
	int jogada_valida;
	int jogada_vence;
	char **matriz_tabuleiro = NULL;
    char opcao;

    //ainda nao foi feita nenhuma jogada
    sjogada *primeira_jogada = NULL;
    sjogada *ultima_jogada = NULL;


	//Gera tabuleiro quadrado aleatório entre 3 e 5
	initRandom();
	row = intUniformRnd(3, 5);
	col = row;

	matriz_tabuleiro = dim_matriz(row, col);


    //Inicializa o tabuleiro
	limpa_tabuleiro(matriz_tabuleiro, row, col);

    //Inicia jogo
    conta_jogadas = 0;
    casas_vazias = 1;
    njogador = 1;
	p1_pedra = 0;
	p2_pedra = 0;
	p1_lc = 0;
	p2_lc = 0;

	do
	{
	   	jogada_valida = 0;

		opcao = pede_opcao(matriz_tabuleiro, row, col, njogador);

		//Se for uma pedra
		if (opcao == 'P')
		{
			if ( (njogador == 1 && p1_pedra == 0) ||  (njogador == 2 && p2_pedra == 0) )
			{
				// pode jogar pedra

				pede_lc( row, col, &x, &y);	//pede coordenadas para a peca
				jogada_valida = valida_jogada(matriz_tabuleiro, row, col, opcao, x, y);

				//Pedra jogada - incrementa contador do jogador
				if ( jogada_valida == 1 )
				{
					if (njogador == 1)
					{
						p1_pedra++;
					}
					else
					{
						p2_pedra++;
					}
				}
				else
				{
					printf("\n\n ************************");
					printf("\n *** Jogada invalida! ***");
					printf("\n *** Ja jogou pedra!! ***");
					printf("\n ************************\n\n");
				}
			}
		}

		//Se for uma peça tem que pedir coordenadas da jogada
		if (opcao == 'R' || opcao == 'G' || opcao == 'Y'  ){

			pede_lc( row, col, &x, &y);	//pede coordenadas para a peca
			jogada_valida = valida_jogada(matriz_tabuleiro, row, col, opcao, x, y);

		}

		//Se for para acrescentar coluna ou linha
		if (opcao == 'C' || opcao == 'L'){
			//verifica se jogador pode acrescentar linhas ou colunas
			if (njogador == 1 && p1_lc < 2){

				jogada_valida = 1; //jogada valida

				//se for coluna, redimensiona e incrementa colunas
				if (opcao == 'C'){
					matriz_tabuleiro = redim_col_matriz(matriz_tabuleiro, row, col);
					col++;
					p1_lc++;
				}
				if (opcao == 'L'){
					matriz_tabuleiro = redim_linha_matriz(matriz_tabuleiro, row, col);
					row++;
					p1_lc++;
				}

			}
			if (njogador == 2 && p2_lc < 2){

				jogada_valida = 1; //jogada valida

				//se for coluna, redimensiona e incrementa colunas
				if (opcao == 'C'){
					matriz_tabuleiro = redim_col_matriz(matriz_tabuleiro, row, col);
					col++;
					p2_lc++;
				}
				if (opcao == 'L'){
					matriz_tabuleiro = redim_linha_matriz(matriz_tabuleiro, row, col);
					row++;
					p2_lc++;
				}
			}
			if (jogada_valida == 0)
			{
				printf("\n\n ***********************************************");
				printf("\n ***             Jogada invalida!            ***");
				printf("\n *** Nao pode acrescentar mais linhas/colunas***");
				printf("\n ***********************************************\n\n");
			}
		}

		//Verifica se jogador atual vence
		jogada_vence = jogada_vencedora( matriz_tabuleiro, row, col);

		//Se a jogada for valida, regista na lista
		if (jogada_valida == 1)
		{
			//atualiza o contador de jogadas
			conta_jogadas++;

			//Regista jogada na lista
			if (opcao == 'P')
			{
				//regista peca pedra (o) para simplificar apresentação das jogadas
				ultima_jogada = Regista_jogada(ultima_jogada, row, col, conta_jogadas, 'o', x, y, njogador);
			}
			else
			{
			    //regista todas as outras jogadas excpto a da pedra
				ultima_jogada = Regista_jogada(ultima_jogada, row, col, conta_jogadas, opcao, x, y, njogador);
			}


			//Se for a primeira jogada, guarda o endereço no ponteiro para a primeira
			if (conta_jogadas == 1)
			{
				primeira_jogada = ultima_jogada;
			}
		}

		//Se jogada vencedora, apresenta mensagem e termina
		if (jogada_vence == 1)
		{

			printf("\n\n************************************");
			printf("\n***** Jogador %d vence o jogo! *****", njogador);
			printf("\n*****       PARABENS!!!!       *****");
			printf("\n************************************\n");

			pressEsc();
		}
		else
		{
			//se jogador nao venceu, verifica se ainda ha casas livres
			casas_vazias = ve_casas_vazias(matriz_tabuleiro, row, col);

			//Nao ha casas livres, o jogo empata
			if (casas_vazias == 0)
			{
				printf("\n\n**************************");
				printf("\n***** Jogo empatado! *****");
				printf("\n**************************\n");

				pressEsc();
			}
			else
			{
				//Muda de jogador se jogada valida
				if (jogada_valida == 1)
				{
					if (njogador == 1)
					{
						njogador = 2;
					}
					else
					{
						njogador = 1;
					}
				}
			}
		}

		//Ver ultimas jogadas
		if (opcao == 'V' || opcao == 'A')
		{
			if (conta_jogadas > 0)
			{
				//pede quantidade de jogadas a visualizar
				//njogadas = pede_njogadas(conta_jogadas);
				Mostra_jogadas(primeira_jogada,ultima_jogada, ultima_jogada->num_jogada);

				pressEsc();
			}
			else
			{
				printf("\n\n ***********************");
				printf("\n *** Nao ha jogadas! ***");
				printf("\n ***********************\n\n");
			}

		}

	}
	while (casas_vazias == 1 && opcao != 'T' && jogada_vence != 1);

	limpa_ecran(25);

	printf("\n\n************************");
	printf("\n******** ADEUS! ********");
	printf("\n************************\n");


    // Liberta array
    liberta_array(matriz_tabuleiro, row);

	//liberta lista
	liberta_lista(primeira_jogada);
	return 0;
}
