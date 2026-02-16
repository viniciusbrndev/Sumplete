#include "ranking.h"
#include "game.h"
#include <stdlib.h>
#include <stdio.h>

int salvarRanking(jogoSumplete jogo){
    FILE *arqRanking = fopen("ranking.dat", "rb+");
    if(arqRanking == NULL)
        arqRanking = fopen("ranking.dat", "wr+");
    if(arqRanking == NULL)
        return 0;
    
    
    }