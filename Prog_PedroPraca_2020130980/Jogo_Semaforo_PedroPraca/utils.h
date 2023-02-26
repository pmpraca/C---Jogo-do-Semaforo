// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
// Pedro Mesquita Praca a2020130980

#ifndef UTILS_H
#define UTILS_H


// Inicializa o gerador de numeros aleatorios.
// Esta funcao deve ser chamada apenas uma vez no inicio da execucao do programa
void initRandom();

//Devolve um valor inteiro aleatorio distribuido uniformemente entre [a, b]
int intUniformRnd(int a, int b);

// Devolve o valor 1 com probabilidade prob. Caso contrario, devolve 0
int probEvento(float prob);

//limpa o ecran
void limpa_ecran(int nlinhas);

#endif /* UTILS_H */
