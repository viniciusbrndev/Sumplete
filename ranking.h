#if !defined(RANKING_H)
#define RANKING_H
#define MAX 10


void ordenaRank(PosRanking *rank, int tam);
int salvarRanking(jogoSumplete jogo, PosRanking *rank);
int procuraPosJogador(jogoSumplete jogo, PosRanking *rank, int tam);
void imprimeRank(PosRanking *vet, int tam);
void mostrarTutorial();
#endif // RANKING_H
