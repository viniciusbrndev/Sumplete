#include <stdio.h>
#include <stdlib.h>
#include "game.h"
//#include "ranking.h"


int main(){
    int menuInicial;
    char comando1[10];
    Jogo **tabuleiro;
    
    imprimirMenuInicial();
    while (1){
        fgets(comando, sizeof(char) * 10, stdin);
        removeN(comando);
        convertM(comando);
        menuInicial = verificarCmdMenu(comando);
        if(menuInicial == 1){
            char nome[28];
            char nivel;
            limparBuffer();
            printf("Digite o nome do jogador: ");
            fgets(nome, sizeof(char) * 28,stdin);
            printf("Digite o nivel de dificuldade: ");
            nivel = getchar();
            while(1){
                char comando2[30];
                char acao[10];
                imprimeTabela(nivel);
                printf("\n%s digite o comando: ", nome);
                fgets(comando2, sizeof(comando2), stdin);
                removerEspaco(comando2);
                copiaComando(comando2, acao);
                convertM(acao);
                
                break;
            }
            


            
        }
    }
    


return 0;
}

