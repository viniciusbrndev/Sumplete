#include <stdio.h>
#include <stdlib.h>
#include "game.h"
//#include "ranking.h"


int main(){
    int menuInicial;
    char comando1[10];
    Celula **tabuleiro;
    int *DicaLin;
    int *dicaCol;
    imprimirMenuInicial();
    srand(time(NULL));
    while (1){
        fgets(comando1, sizeof(char) * 10, stdin);
        removeN(comando1);
        convertM(comando1);
        menuInicial = verificarCmdMenu(comando1);
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
                //impressão do tabuleiro
                imprimeTabela(nivel);
                printf("\n%s digite o comando: ", nome);
                
                fgets(comando2, sizeof(comando2), stdin);//Lê o comando do teclado e usa funções para formatar a entrada 
                removerEspaco(comando2);
                removeN(comando2);
                //posiçao removida ou adicionada
                int x;
                int y;

                int acaoJogo = verificaComando(comando2, &x, &y); //funçao retorna um int com a acao desejada e a posição x,y.
                    //REMOVER
                    if(acaoJogo == 1){
                        
                    }
                    //ADICIONAR
                    else if(acaoJogo == 2){}
                    //DICA
                    else if(acaoJogo == 3){}
                    //VOLTAR
                    else if(acaoJgo == 4)
                
                break;
            }
            


            
        }
    }
    


return 0;
}

