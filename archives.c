#include "archives.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>




int contaJogada(Celula **tabuleiro, int tamMatriz){
    int cont = 0;
    for(int i = 0; i < tamMatriz; i++){
        for(int j = 0; j < tamMatriz; j++){
            if(tabuleiro[i].estado != 0)
                cont++
        }
    }
    return cont;
}

int salvarJogo(Celula **tabuleiro, int **mask, int tamMatriz, int *dicaLin, int dicaCol, char *nome, char *nomeArq){
    FILE *save = fopen(nomeArq, "w");
    
    if(save == NULL){
        printf("%s\nERRO AO ABRIR O ARQUIVO\n%s", ANSI_COLOR_RED, ANSI_RESET);
        return 0;
    }
    fprintf(save, "%d ", tamMatriz);//salva o tamanho do tabuleiro
    //imprime os valores do tabuleiro no arquivo txt
    for(int i = 0;  i < tamMatriz; i++){
        for(int j = 0; j < tamMatriz; j++){
                fprintf(save, "%d ", tabuleiro[i][j].valor);
        }
        fprintf(save, "\n");
    }
    //salva as dicas das linhas
    for(int i = 0; i < tamMatriz; i++){
        fprintf(save, "%d ", dicaLin[i])
    }
    fprintf(save, "\n");
    //salva as dicas das colunas
    for(int j = 0; j < tamMatriz; j++){
        fprintf(save, "%d ", dicaCol[j]);
    }
    fprintf(save, "\n");
    //calcula o número de posições removidas na máscara e salva no arq
    int removidos = contaRemovidos(mask, tamMatriz);
    fprintf(save, "%d ",removidos);
    fprintf(save, "\n");
    //procura as posições removidas na máscara e salva as posições no arq
    for(int i =; i < tamMatriz; i++){
        for(int j = 0; j < tamMatriz; j++){
            if(mask[i][j] == 0;)
                fprintf(save, "%d %d", i, j);
        }
        fprintf(save, "\n");
    }
    //conta as ações feitas pelo usuário e salva no arquivo
    int posJogada = contaJogada(tabuleiro, tamMatriz);
    fprintf(save, "%d", posJogada);
    fprintf(save, "\n");



}