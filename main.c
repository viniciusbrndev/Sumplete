#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "types.h"
#include "game.h"
#include "archives.h"
#include "ranking.h"


int main(){
    jogoSumplete jogo;
    int menuInicial;

    int jogando = 0, tamRank = 0;
    PosRanking rank[11];
    //temporizadores
    time_t inicio, fim;
    long tempoDeSessao;
    srand(time(NULL));
    printf("%sBEM VINDO AO SUMPLETE!!%s", ANSI_BG_COLOR_YELLOW, ANSI_RESET);
    while (1){
        imprimirMenuInicial();
        
        menuInicial = verificarCmdMenu();
        if(menuInicial == 1){
            int flag = 1;
            char nivel;
            printf("Digite o nome do jogador: ");
            fgets(jogo.nome, sizeof(char) * 28,stdin);
            removeN(jogo.nome);
            removerEspaco(jogo.nome);

            while(flag){
                char linha[16];
                printf("Digite o nivel de dificuldade (F,M,D): ");
                lerLinha(linha, sizeof(linha));
                nivel = (unsigned char)toupper(linha[0]);

                if(nivel == 'F'){
                    jogo.tamMatriz = 3;
                    jogando = 1;
                    inicio = time(NULL);
                    flag = 0;
                }
                else if(nivel == 'M'){
                    jogo.tamMatriz = 5;
                    jogando = 1;
                    inicio = time(NULL);
                    flag = 0;
                }
                else if(nivel == 'D'){
                    jogo.tamMatriz = 7;
                    jogando = 1;
                    inicio = time(NULL);
                    flag = 0;
                }
                else{
                    printf("\nDificuldade inválida!!\n");
                }
            }
            
            //aloca o tabuleiro e os vetores dicaLin e dicaCol
            jogo.tabuleiro = alocaTabuleiro(jogo.tamMatriz);
            jogo.mask = alocaMatriz(jogo.tamMatriz);
            jogo.dicalin = alocaVetor(jogo.tamMatriz);
            jogo.dicaCol = alocaVetor(jogo.tamMatriz);
            //gera as posições aleatoriamente e as dicas
            geraMatrizeDica(&jogo);
        }
        //carrega um jogo salvo;
        else if(menuInicial == 2){
            char nomeArq[27];
            printf("\n%sDIGITE O NOME DO ARQUIVO:%s\nUtilize a extenssão \".txt\" ao final do nome!", ANSI_COLOR_BLUE, ANSI_RESET);
            fgets(nomeArq, sizeof(nomeArq), stdin);
            removerEspaco(nomeArq);
            removeN(nomeArq);
            int v = carregarJogo(&jogo, nomeArq);
            if(v){
                jogando = 1;
                inicio = time(NULL);
            }
            else{
                printf("%s\nNÃO FOI POSSÍVEL CARREGAR O JOGO%s", ANSI_COLOR_RED, ANSI_RESET);
            }
        }
        //exibe o ranking
        else if(menuInicial == 3){
            imprimeRank(rank, tamRank);
            esperaEnter();
        }
        //mostra os comando do jogo
        else if(menuInicial == 4){
            mostrarTutorial();
            esperaEnter();
        }
        //salva o jogo atual
        else if(menuInicial == 5){
            char nomeArq[27];
            printf("\nDigite o nome do save: ");
            fgets(nomeArq, sizeof(nomeArq), stdin);
            removerEspaco(nomeArq);
            removeN(nomeArq);
            salvarJogo(jogo, nomeArq);
        }
        //encerra o jogo
        else if(menuInicial == 6){
            //libera a memória antes de fechar
            liberaTabuleiro(jogo.tabuleiro, jogo.tamMatriz);
            liberaMatriz(jogo.mask, jogo.tamMatriz);
            free(jogo.dicaCol);
            free(jogo.dicalin);

            return 1;
        }
        else if(menuInicial == -1)
            continue;
        
        while(jogando){
            //posiçao removida ou adicionada
            int x;
            int y;
            //impressão do tabuleiro
            imprimeTabela(jogo);
            printf("\n%s digite o comando: ", jogo.nome);
            //funçao retorna um int com a acao desejada e a posição x,y.
            int acaoJogo = verificaComando(&x, &y); 

            //REMOVER
            if(acaoJogo == 1){
                removerPos(jogo.tabuleiro, x, y, jogo.tamMatriz);
            }
                //ADICIONAR
            else if(acaoJogo == 2){
                adicionarPos(jogo.tabuleiro, x, y, jogo.tamMatriz);
            }
            //DICA
            else if(acaoJogo == 3){
                mostrarDica(&jogo);
            }
            //VOLTAR
            else if(acaoJogo == 4){
                fim = time(NULL);
                tempoDeSessao = (long)difftime(fim, inicio);
                jogo.tempoTotal += tempoDeSessao;
                jogando = 0;
            }
            //RESOLVER
            else if(acaoJogo == 5){
                resolverJogo(&jogo);
            }
            else{
                printf("\n%sCOMANDO INVÁLIDO!!%s\n", ANSI_COLOR_RED, ANSI_RESET);
            }
            int venceu = verificaVitoria(jogo);
            if(venceu){
                //marca o tempo final e salva 
                fim = time(NULL);
                tempoDeSessao = difftime(fim, inicio);
                jogo.tempoTotal += tempoDeSessao;

                printf("%sVOCÊ VENCEU O SUMPLETE!!!%s", ANSI_COLOR_GREEN, ANSI_RESET);
                printf("\nTempo gasto: %ld", jogo.tempoTotal);
                //salva o ranking e  mostra a posição do jogador se estiver entre os 10 melhores
                tamRank = salvarRanking(jogo, rank);
                int posPlayer = procuraPosJogador(jogo, rank, tamRank);
                if(posPlayer)
                    printf("\nSua posição: %s%d lugar%s",ANSI_COLOR_BLUE, posPlayer, ANSI_RESET);
                else
                    printf("\nVocê ficou fora do TOP 10 :(");
                
                jogando = 0;
                esperaEnter();
                break;
                }
                
                
            }
    }
    


return 0;
}

