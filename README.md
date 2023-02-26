# Jogo-do-Sem-foro
Este é um jogo de tabuleiro entre 2 pessoas que efetuam jogadas alternadas, até que uma delas vença ou que se verifique um empate.
O jogo do semáforo desenrola-se num tabuleiro dividido em células. No início, o tabuleiro
está vazio. Alternadamente os jogadores vão colocando peças de cor Verde (G), Amarela
(Y) ou Vermelha (R). Ganha o jogador que coloque uma peça que permita formar uma linha,
coluna ou diagonal completa (1) com peças da mesma cor. As jogadas válidas relativas à
colocação de peças são as seguintes:
1. Colocar uma peça Verde numa célula vazia
2. Trocar uma peça Verde que esteja colocada no tabuleiro por uma peça Amarela
3. Trocar uma peça Amarela que esteja colocada no tabuleiro por uma peça Vermelha
Existem duas jogadas adicionais que podem ser efetuadas pelos jogadores:
4. Colocar uma pedra numa célula vazia. Cada jogador pode colocar, no máximo, uma
pedra por jogo. A colocação de uma pedra inviabiliza que o jogo possa terminar por
preenchimento da linha e coluna afetadas (e, eventualmente também da diagonal ou
diagonais).
5. Adicionar uma linha ou uma coluna ao final do tabuleiro. Esta jogada adiciona linhas
ou colunas completas e vazias ao tabuleiro de jogo. Cada jogador pode efetuar esta
jogada, no máximo, duas vezes por jogo.
Em cada iteração, um jogador escolhe uma destas jogadas para atualizar o tabuleiro. As
jogadas 4 e 5 estão sujeitas às restrições indicadas na sua definição. O número de peças de
cada cor é ilimitado.

(1) Se o tabuleiro não for quadrado, será impossível terminar o jogo formando uma diagonal toda da mesma
cor.
