// Vinícius Brandão de S. Oliveira 
// Projeto prático da disciplina BCC201 -> UFOP Professor Puca Huachi
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

    int jogando = 0, tamRank = 0, jogoIniciado = 0, jogoSalvo = 0;
    PosRanking rank[11];
    //temporizadores
    time_t inicio, fim;
    long tempoDeSessao;
    //inicializando os ptrs
    jogo.nome[0] = '\0';
    jogo.dicaCol = NULL;
    jogo.dicalin = NULL;
    jogo.mask = NULL;
    jogo.tabuleiro = NULL;
    //abrindo o rank
    tamRank = carregaRanking(rank);

    printf("%sBEM VINDO AO SUMPLETE!!%s", ANSI_COLOR_YELLOW, ANSI_RESET);
    while (1){
        imprimirMenuInicial();
        
        menuInicial = verificarCmdMenu();
        if(menuInicial == 1){
            int flag = 1;
            
            while(1){
                printf("\nDigite o nome do jogador, ou \"sair\" para voltar ao menu: ");
                int a = verificaNomeValido(jogo.nome, sizeof(jogo.nome));
                if(a == 1){
                    jogo.nome[0] = '\0';
                    break;
                }
                else if(a == 2)
                    break;
            }
            //só continua criando um novo jogo se o usuário digitar um nome válido
            if(jogo.nome[0] != '\0'){    
                jogoIniciado  = 1;
                jogoSalvo = 1;
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
                    geraMatrizeDica(&jogo);}
        }
        //carrega um jogo salvo;
        else if(menuInicial == 2){
            jogoIniciado = 1;
            int flagCarregar = 1;
            char nomeArq[27];
            while(flagCarregar){
                int arq = verificanArquivo(nomeArq, sizeof(nomeArq));
                if(arq == 1)
                    break;
                if(arq == 2){
                    int v = carregarJogo(&jogo, nomeArq);
                    if(v){
                        jogando = 1;
                        inicio = time(NULL);
                        flagCarregar = 0;
                    }
                    else{
                        printf("%s\nNÃO FOI POSSÍVEL CARREGAR O JOGO%s", ANSI_COLOR_RED, ANSI_RESET);
                        continue;
                    }
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
            if(jogoIniciado){
                char nomeArq[27];
            
                int arq = verificanArquivo(nomeArq, sizeof(nomeArq));
                if(arq == 2)
                    salvarJogo(jogo, nomeArq);
                else if(arq == 1)
                    printf("\nVoltando para o menu...");
            }
            else
                printf("\n%sVOCÊ NÃO PODE SALVAR SEM TER INICIADO UM NOVO JOGO OU CARREGADO UM ANTERIOR!!%s", ANSI_COLOR_RED, ANSI_RESET);
        }
        //encerra o jogo
        else if(menuInicial == 6){
            if(jogoSalvo){
                char resposta[5];
                printf("\nDeseja salvar o jogo atual antes de sair? SIM/NAO ");
                linhaSegura(resposta, sizeof(resposta));
                while(1){
                    int z = verificaSimNao(resposta);
                    if(z == 0)
                        continue;
                    else if(z == 1){
                        char nomeArq[27];
                        jogoSalvo = 0;
                        int arq = verificanArquivo(nomeArq, sizeof(nomeArq));
                        if(arq == 2)
                            salvarJogo(jogo, nomeArq);
                        else if(arq == 1)
                            printf("\nVoltando para o menu...");
                        break;
                    }
                    else if(z == 2)
                        break;
                }
            }
            salvarRanking(rank, tamRank);
            //libera a memória antes de fechar
            liberaJogo(&jogo);

            return 1;
        }
        else if(menuInicial == 7){
            if(jogoIniciado)
                jogando = 1;
            else
                printf("%s\nPARA CONTINUAR VOCÊ PRECISA TER INICIADO UM JOGO%s", ANSI_COLOR_RED, ANSI_RESET);
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
            printf("-> \"adicionar\" <lin> <col>\n-> \"remover\" <lin> <col>\n-> \"resolver\"\n-> \"dica\"\n-> \"sair\"\n");
            printf("\n%s digite o comando: ", jogo.nome);
            //funçao retorna um int com a acao desejada e a posição x,y.
            int acaoJogo = verificaComando(&x, &y); 

            //REMOVER
            if(acaoJogo == 1){
                if(removerPos(jogo.tabuleiro, x, y, jogo.tamMatriz) == 0)
                    printf("\n%sPOSIÇÃO DO TABULEIRO  INVÁLIDA\n%s", ANSI_COLOR_RED, ANSI_RESET);
            }
                //ADICIONAR
            else if(acaoJogo == 2){
                if(adicionarPos(jogo.tabuleiro, x, y, jogo.tamMatriz) == 0)
                    printf("\n%sPOSIÇÃO DO TABULEIRO  INVÁLIDA\n%s", ANSI_COLOR_RED, ANSI_RESET);
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
                printf("\nTempo gasto: %ds", jogo.tempoTotal);
                //salva o ranking e  mostra a posição do jogador se estiver entre os 10 melhores
                if(verificaOcorreencia(jogo, rank, tamRank)){
                    tamRank = insereJogadorRank(jogo, rank, tamRank);
                    int posPlayer = procuraPosJogador(jogo, rank, tamRank);
                    if(posPlayer)
                        printf("\nSua posição: %s%d lugar%s",ANSI_COLOR_BLUE, posPlayer, ANSI_RESET);
                    else
                        printf("\nVocê ficou fora do TOP 10 :(");
                }
                else
                    printf("\n%sJÁ EXISTE UM JOGADOR NO RANKING COM SEU NOME, \nSUA POSIÇÃO NÃO FOI CONSIDERADA%s", ANSI_COLOR_RED, ANSI_RESET);
                
                jogando = 0;
                esperaEnter();
                break;
                }
                
                
            }
    }
    


return 0;
}

