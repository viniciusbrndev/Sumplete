#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "types.h"
#include "game.h"
#include "archives.h"
#include "ranking.h"


int main(){
    srand(time(NULL));
    jogoSumplete jogo;
    int menuInicial;

    int jogando = 0, tamRank = 0;
    PosRanking rank[11];
    //temporizadores
    time_t inicio, fim;
    long tempoDeSessao;
    //inicializando os ptrs
    jogo.dicaCol = NULL;
    jogo.dicalin = NULL;
    jogo.mask = NULL;
    jogo.tabuleiro = NULL;

    printf("%sBEM VINDO AO SUMPLETE!!%s", ANSI_COLOR_YELLOW, ANSI_RESET);
    while (1){
        imprimirMenuInicial();
        
        menuInicial = verificarCmdMenu();
        if(menuInicial == 1){
            int flag = 1;

        printf("Digite o nome do jogador: ");
        fgets(jogo.nome, sizeof(char) * 28,stdin);
        removeN(jogo.nome);
        removerEspaco(jogo.nome);
        //se o jogo já estiver sido alocado antes libera antes de alocar
        liberaJogo(&jogo);
            
        while (flag){
            char linha[16];
            printf("\nDigite o nivel de dificuldade (F,M,D): ");
            if (linhaSegura(linha, sizeof(linha)) != 1) {
                printf("\nEntrada inválida! Tente novamente.\n");
                continue;
            }
            removeN(linha);
            removerEspaco(linha);
            
            char c = tolower(linha[0]); // pega só o 1º char
            if (linha[1] != '\0') { 
                // se digitou mais de 1 caractere 
                printf("\nDigite apenas F, M ou D.\n");
                continue;
            }

            if (c == 'f') jogo.tamMatriz = 3;
            else if (c == 'm') jogo.tamMatriz = 5;
            else if (c == 'd') jogo.tamMatriz = 7;
            else{
                printf("\n%sDificuldade inválida!!%s\n", ANSI_COLOR_RED, ANSI_RESET);
                continue;
            }

            jogando = 1;
            inicio = time(NULL);
            flag = 0;
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
            int arq = verificanArquivo(nomeArq, sizeof(nomeArq));
            if(arq == 2){
                int v = carregarJogo(&jogo, nomeArq);
                if(v){
                    jogando = 1;
                    inicio = time(NULL);
                }
                else{
                    printf("%s\nNÃO FOI POSSÍVEL CARREGAR O JOGO%s", ANSI_COLOR_RED, ANSI_RESET);
                    esperaEnter();
                }
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
            
            int arq = verificanArquivo(nomeArq, sizeof(nomeArq));
            if(arq == 2)
                salvarJogo(jogo, nomeArq);
            else if(arq == 1)
                printf("\nVoltando para o menu...");
        }
        //encerra o jogo
        else if(menuInicial == 6){
            //libera a memória antes de fechar
            liberaJogo(&jogo);

            return 1;
        }
        else if(menuInicial == -1)
            printf("%s\nVOCÊ PRECISA DIGITAR UM COMANDO VÁLIDO!%s", ANSI_COLOR_RED, ANSI_RESET);
        else
            printf("%s\nCOMANDO INVÁLIDO%s", ANSI_COLOR_RED, ANSI_RESET);
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
                resolverJogo(&jogo);
                imprimeTabela(jogo);
                printf("%sVOCÊ VENCEU O SUMPLETE!!!%s", ANSI_COLOR_GREEN, ANSI_RESET);
                printf("\nTempo gasto: %lds", jogo.tempoTotal);
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

