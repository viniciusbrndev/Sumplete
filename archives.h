#if !defined(ARCHIVES_H)
#define ARCHIVES_H

int contaJogada(Celula **tabuleiro, int tamMatriz);
int salvarJogo(Celula **tabuleiro, int **mask, int tamMatriz, int *dicaLin, int dicaCol, char *nome, char *nomeArq);

#endif // ARCHIVES_H
