#include "ranking.h"
#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void ordenaRank(PosRanking *rank, int tam){
    PosRanking temp;
    for(int i = 0; i < tam-1; i++){
        for(int j = 0; j < tam){
            if(rank[i] < rank[j]){
                temp = rank[i];
                rank[i] = rank[j];
                rank[j] = temp;
            }
        }
    }
}
int salvarRanking(jogoSumplete jogo, PosRanking *rank){
    FILE *arqRank = fopen("ranking.dat", "rb");
    int n;//qunatidade de linhas lidas
    if(arqRank != NULL){
        //le todas as linhas do arquivo e retorna a quantidade de linhas lidas
        n = fread(rank, sizeof(PosRanking) * MAX, arqRank);
        fclose(arqRank); // fecha a leitura do arquivo
    }
    //insere o jogador no vetor do ranking
    strncpy(rank[n].nome, jogo.nome, 28);
    rank[n].tempoTotal = jogo.tempoTotal;
    //ordena o rank
    ordenaRank(rank, n);
    //remove o último do rank 11pos
    if(n > MAX)
        n--;
    //abre o arquvivo para escrita
    arqRank = fopen("ranking.dat", "wb");
    fwrite(rank, sizeof(PosRanking) * n, arqRank);//grava o vetor de rank no arquivo
    return n;

    }
int procuraPosJogador(jogoSumplete jogo, PosRanking *rank, int tam){
    for(int i = 0; i < tam; i++){
        if(strcmp(jogo.nome, rank[i].nome) == 0 && jogo.tempoTotal == rank[i].tempoTotal){
            return i+1;
        }
    }
    return 0;
}
void imprimeRank(PosRanking *vet, int tam){
    int n;
    if(tam < 5)
        n = tam;
    else
        n = 5;
    for(int i = 0; i < n; i++){
        printf("\n%s%d%s %s %ld", ANSI_COLOR_CYAN,i+1,ANSI_RESET, vet[i].nome, vet[i].tempoTotal);
    }
}