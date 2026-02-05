#include <stdio.h>
//#include "game.c"


void imprimeTabela(char nivel, Celula **matriz, int *dicaLin, int *dicaCol){
    int cont;

    if(nivel == 'F') cont = 2;
    else if(nivel == 'M') cont = 4;
    else if(nivel == 'D') cont = 6;
    else{
        printf("Dificuldade inválida");
        return;
    }

    int N = cont + 1; // 3, 5 ou 7

    // ===== Topo =====
    printf("%s", TAB_TL);
    for(int i = 0; i < cont; i++){
        printf("%s%s%s%s", TAB_HOR, TAB_HOR, TAB_HOR, TAB_TJ);
    }
    printf("%s%s%s%s\n", TAB_HOR, TAB_HOR, TAB_HOR, TAB_TR);

    // ===== Corpo (linhas + separadores) =====
    for(int k = 0; k < N; k++){

        // Linha de conteúdo
        for(int i = 0; i < N; i++){
            if(matriz[k][i].estado == ATIVA){
                printf("%s%s %d %s ", TAB_VER, ANSI_BG_COLOR_GREEN, matriz[k][i].valor, ANSI_RESET);
            }
            else if(matriz[k][i].estado == REMOVIDA){
                printf("%s%s %d %s ", TAB_VER, ANSI_BG_COLOR_RED, matriz[k][i].valor, ANSI_RESET);
            }
            else{
                printf("%s %d ", TAB_VER, matriz[k][i].valor);
            }
        }

        // Dica da linha (uma vez no final)
        printf("%s %d\n", TAB_VER, dicaLin[k]);

        // Separador horizontal interno (entre as linhas)
        if(k < N - 1){
            printf("%s", TAB_ML);
            for(int i = 0; i < cont; i++){
                printf("%s%s%s%s", TAB_HOR, TAB_HOR, TAB_HOR, TAB_MJ);
            }
            printf("%s%s%s%s\n", TAB_HOR, TAB_HOR, TAB_HOR, TAB_MR);
        }
    }

    // ===== Borda inferior =====
    printf("%s", TAB_BL);
    for(int i = 0; i < cont; i++){
        printf("%s%s%s%s", TAB_HOR, TAB_HOR, TAB_HOR, TAB_BJ);
    }
    printf("%s%s%s%s\n", TAB_HOR, TAB_HOR, TAB_HOR, TAB_BR);

    // ===== Dicas das colunas =====
    // Ajuste de alinhamento: como cada célula tem " %d " (3 chars) + borda,
    // esse "  " inicial pode precisar ser calibrado dependendo dos seus símbolos.
    printf("  ");
    for(int i = 0; i < N; i++){
        printf("%d   ", dicaCol[i]);
    }
    printf("\n");

    printf("-> \"adicionar\"\n->\"remover\"\n->\"salvar\"\n->\"dica\"\n->\"sair\"\n");
}

int main(){
    imprimeTabela("M",)
    return 0;
}



