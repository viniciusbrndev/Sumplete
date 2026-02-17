#include "types.h"
#include "ranking.h"
#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void ordenaRank(PosRanking *rank, int tam){
    PosRanking temp;
    for(int i = 0; i < tam-1; i++){
        for(int j = 0; j < tam -1 -i; j++){
            if(rank[j].tempoTotal > rank[j+1].tempoTotal){
                temp = rank[j];
                rank[j] = rank[j+1];
                rank[j+1] = temp;
            }
        }
    }
}
int salvarRanking(jogoSumplete jogo, PosRanking *rank){
    int n = 0;

    // lê até 10 do arquivo
    FILE *arqRank = fopen("ranking.dat", "rb");
    if (arqRank != NULL){
        n = (int)fread(rank, sizeof(PosRanking), MAX, arqRank);
        fclose(arqRank);
        if (n < 0) n = 0;
        if (n > MAX) n = MAX;
    }

    // coloca o novo jogador na posição extra (rank[n] é seguro: n <= MAX)
    memset(&rank[n], 0, sizeof(PosRanking));
    strncpy(rank[n].nome, jogo.nome, sizeof(rank[n].nome) - 1);
    rank[n].tempoTotal = jogo.tempoTotal;

    int tamOrdenar = n + 1;         // agora tem 1 a mais (até 11)
    ordenaRank(rank, tamOrdenar);

    // mantém só 10 para salvar
    int tamSalvar = (tamOrdenar > MAX) ? MAX : tamOrdenar;

    arqRank = fopen("ranking.dat", "wb");
    if (arqRank == NULL) return 0;

    fwrite(rank, sizeof(PosRanking), tamSalvar, arqRank);
    fclose(arqRank);

    return tamSalvar;
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
    printf("\n%sTOP PLAYERS!!%s",ANSI_COLOR_YELLOW, ANSI_RESET );
    int n;
    if(tam < 5)
        n = tam;
    else
        n = 5;
    for(int i = 0; i < n; i++){
        printf("\n%s%d%s %s %ld", ANSI_COLOR_CYAN,i+1,ANSI_RESET, vet[i].nome, vet[i].tempoTotal);
    }
}
void mostrarTutorial(){
    printf("%s", ANSI_COLOR_BLUE);
    printf("\n==================== TUTORIAL - JOGO SUMPLETE ================\n");
    printf("%s", ANSI_RESET);

    printf("%s\nOBJETIVO:%s\n", ANSI_COLOR_BLUE, ANSI_RESET);
    printf("Remova numeros do tabuleiro de forma que a soma dos valores\n");
    printf("restantes em CADA LINHA e CADA COLUNA seja igual as dicas\n");
    printf("mostradas ao lado e abaixo do tabuleiro.\n");

    printf("\n---------------------------------------------------------------\n");

    printf("%s\nTABULEIRO:%s\n", ANSI_COLOR_BLUE, ANSI_RESET);
    printf("- Cada celula possui um numero inteiro.\n");
    printf("- As celulas podem assumir tres estados:\n\n");

    printf("  * %sNORMAL%s    -> valor ainda pode ser alterado (mas ainda entra na soma)\n",
        ANSI_COLOR_GRAY, ANSI_RESET);

    printf("  * %sATIVA%s     -> valor confirmado na soma\n",
        ANSI_COLOR_GREEN, ANSI_RESET);

    printf("  * %sREMOVIDA%s  -> valor excluido da soma\n",
        ANSI_COLOR_RED, ANSI_RESET);

    printf("\n---------------------------------------------------------------\n");

    printf("%s\nDICAS:%s\n", ANSI_COLOR_BLUE, ANSI_RESET);
    printf("- As dicas indicam a soma correta de cada linha e coluna.\n");
    printf("- Quando a soma de uma linha ou coluna for atingida corretamente,\n");
    printf("  a dica correspondente %smuda de cor%s indicando que esta correta.\n",
        ANSI_COLOR_GREEN, ANSI_RESET);

    printf("\n---------------------------------------------------------------\n");

    printf("%s\nCOMANDOS DURANTE O JOGO:%s\n\n", ANSI_COLOR_BLUE, ANSI_RESET);

    printf("  %sadicionar LIN COL%s\n", ANSI_COLOR_GREEN, ANSI_RESET);
    printf("      Marca a posicao como ATIVA (verde)\n\n");

    printf("  %sremover LIN COL%s\n", ANSI_COLOR_RED, ANSI_RESET);
    printf("      Marca a posicao como REMOVIDA (vermelha)\n\n");

    printf("  %sdica%s\n", ANSI_COLOR_BLUE, ANSI_RESET);
    printf("      Remove automaticamente uma posicao incorreta\n\n");

    printf("  %sresolver%s\n", ANSI_COLOR_BLUE, ANSI_RESET);
    printf("      Mostra a solucao completa do tabuleiro\n\n");

    printf("  %ssair%s\n", ANSI_COLOR_BLUE, ANSI_RESET);
    printf("      Volta ao menu principal\n\n");

    printf("Obs: LIN e COL iniciam em 0.\n");

    printf("\n---------------------------------------------------------------\n");

    printf("%s\nVITORIA:%s\n", ANSI_COLOR_BLUE, ANSI_RESET);
    printf("Voce vence quando TODAS as linhas e colunas estiverem corretas,\n");
    printf("ou seja, quando todas as dicas mudarem de cor.\n");

    printf("\n---------------------------------------------------------------\n");

    printf("%s\nMENU PRINCIPAL:%s\n\n", ANSI_COLOR_BLUE, ANSI_RESET);
    printf("  novo      -> Iniciar um novo jogo\n");
    printf("  carregar  -> Carregar jogo salvo\n");
    printf("  exibir    -> Exibir ranking\n");
    printf("  ajuda     -> Mostrar esta tela de ajuda\n");
    printf("  salvar    -> Salvar jogo atual\n");
    printf("  sair      -> Encerrar o jogo\n");

    printf("\n---------------------------------------------------------------\n");

    printf("%s\nPONTUACAO:%s\n", ANSI_COLOR_BLUE, ANSI_RESET);
    printf("- O tempo total do jogo e registrado.\n");
    printf("- Os 10 melhores tempos ficam no ranking.\n");

    printf("%s\n===============================================================\n%s",ANSI_COLOR_BLUE, ANSI_RESET);
}