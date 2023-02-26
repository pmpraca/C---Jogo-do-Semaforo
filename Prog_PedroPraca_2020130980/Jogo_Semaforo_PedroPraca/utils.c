// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
// Pedro Mesquita Praca a2020130980

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"

void initRandom(){
    srand(time(NULL));
}

int intUniformRnd(int a, int b){
    return a + rand()%(b-a+1);
}

int probEvento(float prob){
    return prob > ((float)rand()/RAND_MAX);
}

//limpa o ecran
void limpa_ecran(int nlinhas)
{
	for (int i = 1; i<= nlinhas; i++)
	{
		printf("\n");
	}

}
