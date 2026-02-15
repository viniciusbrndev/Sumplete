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

int salvarJogo(jogoSumplete jogo, char *nomeArq){
    FILE *save = fopen(nomeArq, "w");
    
    if(save == NULL){
        printf("%s\nERRO AO ABRIR O ARQUIVO\n%s", ANSI_COLOR_RED, ANSI_RESET);
        return 0;
    }
    fprintf(save, "%d ", jogo.tamMatriz);//salva o tamanho do tabuleiro
    //imprime os valores do tabuleiro no arquivo txt
    for(int i = 0;  i < jogo.tamMatriz; i++){
        for(int j = 0; j < jogo.tamMatriz; j++){
                fprintf(save, "%d ", jogo.tabuleiro[i][j].valor);
        }
        fprintf(save, "\n");
    }
    //salva as dicas das linhas
    for(int i = 0; i < jogo.tamMatriz; i++){
        fprintf(save, "%d ", jogo.dicalin[i])
    }
    fprintf(save, "\n");
    //salva as dicas das colunas
    for(int j = 0; j < jogo.tamMatriz; j++){
        fprintf(save, "%d ", jogo.dicaCol[j]);
    }
    fprintf(save, "\n");
    //calcula o número de posições removidas na máscara e salva no arq
    int removidos = contaRemovidos(jogo.mask,jogo.tamMatriz);
    fprintf(save, "%d ",removidos);
    fprintf(save, "\n");
    //procura as posições removidas na máscara e salva as posições no arq
    for(int i =; i < jogo.tamMatriz; i++){
        for(int j = 0; j < jogo.tamMatriz; j++){
            if(jogo.mask[i][j] == 0;)
                fprintf(save, "%d %d", i, j);
        }
        fprintf(save, "\n");
    }
    //conta as ações feitas pelo usuário e salva no arquivo
    int posJogada = contaJogada(jogo.tabuleiro, jogo.tamMatriz);
    fprintf(save, "%d", posJogada);
    fprintf(save, "\n");
    // imprime o tabuleiro com o estado da célula, se removido a posição recebe "r" se adicionada recebe "a" nenhuma ação mandtém o valor real da célula
    for(int i = 0; i < jogo.tamMatriz; i++){
        for(int j = 0; j < jogo.tamMatriz; j++){
            if(jogo.tabuleiro[i][j].estado == 2)
                fprintf(save, "r ");
            else if(jogo.tabuleiro[i][j].estado == 1)
                fprintf(save, "a ");
            else
                fprintf(save, "%d ", jogo.tabuleiro[i][j].valor);
        }
        fprintf(save, "\n");
    }
    fprintf(save, "\n%s", nome);
    fprintf(save, "\n%ld", jogo.tempoTotal);


}
int carregarJogo(jogoSumplete *jogo, char *nomeArq){
    FILE *arqSalvo = fopen(nomeArq, "r");
    fscanf(arqSalvo, "%d", &jogo->tamMatriz);
    //alocando a memória
    jogo->tabuleiro = alocaTabuleiro(jogo->tamMatriz);
    jogo->mask = alocaMatriz(jogo->tamMatriz);
    jogo->dicalin = alocaVetor(jogo->tamMatriz);
    jogo->dicaCol = alocaVetor(jogo->tamMatriz);

    //lendo os valores das células 
    for(int i = 0; i < jogo->tamMatriz; i++){
        for(int j = 0; j < jogo->tamMatriz; j++){
            fscanf(arqSalvo, "%d", &jogo->tabuleiro[i][j].valor);
            jogo->tabuleiro.estado = 0;
        }
    }
    //lendo as dicas
    for(int i = 0; i < jogo->tamMatriz; i++)
        fscanf(arqSalvo, "%d", &jogo->dicalin[i]);
    for(int j = 0; j < jogo->tamMatriz; j++)
        fscanf(arqSalvo, "%d", &jogo->dicaCol[j]);
    
    //preenche a máscara com 1;
    for(int i = 0; i < jogo->tamMatriz; i++){
        for(int j = 0; j < jogo->tamMatriz; j++){
            jogo->mask[i][j] = 1;
        }
    }
    //pega as posições salvas no arq como removida e coloca 0 no local na máscara
    int n, lin, col;
    fscanf(arqSalvo, "%d", &n);
    for(int i = 0; i < n; i++){
        fscanf(arqSalvo, "%d %d", &lin, &col);
        jogo->mask[lin][col] = 0;
    }
    
}