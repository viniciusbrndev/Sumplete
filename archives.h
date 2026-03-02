
#ifndef ARCHIVES_H
#define ARCHIVES_H

int contaJogada(Celula **tabuleiro, int tamMatriz);
int salvarJogo(jogoSumplete jogo, char *nomeArq);
int carregarJogo(jogoSumplete *jogo, char *nomeArq);
#endif // ARCHIVES_H
