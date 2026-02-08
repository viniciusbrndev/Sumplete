#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include <time.h>
//#include "ranking.h"


int main(){
    int menuInicial;
    char comando1[10];
    Celula **tabuleiro;
    int **posRemovidas;
    int *dicaLin;
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
            limparBuffer();
            int tamMatriz;
            if(nivel == 'F' || nivel == 'f')
                tamMatriz = 3;
            else if(nivel == 'M' || nivel == 'm')
                tamMatriz = 5;
            else if(nivel == 'D' || nivel == 'd')
                tamMatriz = 7;
            else{
                printf("\nDificuldade inválida!!");
                continue;
            }
            //aloca o tabuleiro e os vetores dicaLin e dicaCol
            tabuleiro = alocaTabuleiro(tamMatriz);
            posRemovidas = alocaMatriz(tamMatriz);
            dicaLin = alocaVetor(tamMatriz);
            dicaCol = alocaVetor(tamMatriz);
            //--------------GERAR TABULEIRO-----------------
            geraMatrizeDica(tabuleiro, posRemovidas, dicaLin, dicaCol, tamMatriz);

            while(1){
                //posiçao removida ou adicionada
                int x;
                int y;
                //impressão do tabuleiro
                imprimeTabela(nivel, tabuleiro, dicaLin, dicaCol);
                printf("\n%s digite o comando: ", nome);
                //funçao retorna um int com a acao desejada e a posição x,y.
                int acaoJogo = verificaComando(&x, &y); 

                    //REMOVER
                    if(acaoJogo == 1){
                        removerPos(tabuleiro, x, y, tamMatriz);
                    }
                    //ADICIONAR
                    else if(acaoJogo == 2){
                        adicionarPos(tabuleiro, x, y, tamMatriz);
                    }
                    //DICA
                    else if(acaoJogo == 3){
                        mostrarDica(tabuleiro, posRemovidas, tamMatriz);
                    }
                    //VOLTAR
                    else if(acaoJogo == 4){
                        break;
                    }
                    //RESOLVER
                    else if(acaoJogo == 5){}
                    int venceu = verificaVitoria(tabuleiro, dicaLin, dicaCol,tamMatriz);
                    /*if(venceu){
                        //mostra as posições corretas em verde e as outras em vermelho e acaba
                        break;
                    }*/
                
            }
            


                free(dicaCol);
                free(dicaLin);
                liberaMatriz(posRemovidas, tamMatriz);
                liberaTabuleiro(tabuleiro, tamMatriz);
                break;
        }
    break;
    }
    


return 0;
}

