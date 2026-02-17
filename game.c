//Bibliotecas
#include "types.h"
#include "game.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>



void imprimirMenuInicial(){
    printf("%s\n", ANSI_COLOR_BLUE);
    printf("\n╔═════════════ MENU PRINCIPAL ════════════════╗\n");
    printf("║                                             ║\n");
    printf("║   [novo]     -> Iniciar um novo jogo        ║\n");
    printf("║   [carregar] -> Carregar jogo salvo         ║\n");
    printf("║   [exibir]   -> Exibir ranking              ║\n");
    printf("║   [ajuda]    -> Mostrar comandos            ║\n");
    printf("║   [salvar]   -> Salva o jogo atual          ║\n");
    printf("║   [sair]     -> Encerrar o jogo             ║\n");
    printf("║                                             ║\n");
    printf("╚═════════════════════════════════════════════╝\n");
    printf("%s", ANSI_RESET);
    printf("\nDIGITE UM COMANDO: ");

}
int somaLinReal(jogoSumplete jogo, int poslin){
    int soma = 0;
    for(int i = 0; i < jogo.tamMatriz; i++){
        if(jogo.tabuleiro[poslin][i].estado != REMOVIDA)
            soma += jogo.tabuleiro[poslin][i].valor;
    }
    return soma;
}
int somaColReal(jogoSumplete jogo, int poscol){
    int soma = 0;
    for(int i = 0; i < jogo.tamMatriz; i++){
        if(jogo.tabuleiro[i][poscol].estado != REMOVIDA)
            soma += jogo.tabuleiro[i][poscol].valor;
    }
    return soma;

}

void imprimeTabela(jogoSumplete jogo){
    int n = jogo.tamMatriz; // tamanho real (valores 1..9)

    // -------- TOPO --------
    printf("%s", TAB_TL);
    for(int i = 0; i < n-1; i++){
        printf("%s%s%s%s", TAB_HOR, TAB_HOR, TAB_HOR, TAB_TJ);
    }
    printf("%s%s%s%s\n", TAB_HOR, TAB_HOR, TAB_HOR, TAB_TR);

    // -------- CORPO --------
    for(int k = 0; k < n; k++){

        for(int i = 0; i < n; i++){
            int v = jogo.tabuleiro[k][i].valor;

            if(jogo.tabuleiro[k][i].estado == ATIVA){
                printf("%s%s %d %s", TAB_VER, ANSI_BG_COLOR_GREEN, v, ANSI_RESET);
            }
            else if(jogo.tabuleiro[k][i].estado == REMOVIDA){
                printf("%s%s %d %s", TAB_VER, ANSI_BG_COLOR_RED, v, ANSI_RESET);
            }
            else{
                printf("%s %d ", TAB_VER, v);
            }
        }

        // dica da linha no final
        int somaliReal = somaLinReal(jogo, k); 
        if(somaliReal == jogo.dicalin[k]){
            printf("%s%s %d%s\n", TAB_VER, ANSI_COLOR_GREEN, jogo.dicalin[k], ANSI_RESET);
        }
        else{
            printf("%s%s %d%s\n", TAB_VER, ANSI_COLOR_GRAY, jogo.dicalin[k], ANSI_RESET);
        }

        // linha do meio antes da borda
        if(k < n-1){
            printf("%s", TAB_ML);
            for(int i = 0; i < n-1; i++){
                printf("%s%s%s%s", TAB_HOR, TAB_HOR, TAB_HOR, TAB_MJ);
            }
            printf("%s%s%s%s\n", TAB_HOR, TAB_HOR, TAB_HOR, TAB_MR);
        }
    }

    // borda inferior
    printf("%s", TAB_BL);
    for(int i = 0; i < n-1; i++){
        printf("%s%s%s%s", TAB_HOR, TAB_HOR, TAB_HOR, TAB_BJ);
    }
    printf("%s%s%s%s\n", TAB_HOR, TAB_HOR, TAB_HOR, TAB_BR);

    // -------- DICAS DAS COLUNAS --------
    printf("  ");
    
    for(int i = 0; i < n; i++){
        int somaclReal = somaColReal(jogo, i);
        if(somaclReal == jogo.dicaCol[i])
            printf("%s%2d%s  ",ANSI_COLOR_GREEN, jogo.dicaCol[i], ANSI_RESET);
        else
            printf("%s%2d  %s", ANSI_COLOR_GRAY,jogo.dicaCol[i], ANSI_RESET);
    }

    printf("\n");

    printf("-> \"adicionar\"\n-> \"remover\"\n-> \"resolver\"\n-> \"dica\"\n-> \"sair\"\n");
}
//Função para converter a palavra para letras minúsculas   
void convertM(char *palavra){
    for(int i = 0; palavra[i] != '\0'; i++)
        if(palavra[i] >= 65 && palavra[i] <= 90)
            palavra[i] += 32; 
}
//remove o "\n" da string
void removeN(char *palavra){
    for (int i = 0; palavra[i] != '\0'; i++)
        if (palavra[i] == '\n')
            palavra[i] = '\0';
}
void limparBuffer(){
    char c;
    while ((c = getchar()) != '\n' && !EOF);    
}

int verificarCmdMenu(){
    char comando[30];
    char acao[11];
    char lixo;
    fgets(comando, sizeof(comando), stdin);
    removeN(comando);
    removerEspaco(comando);

    int n = sscanf(comando,"%9s %c",acao, &lixo);
    if (comando[0] == '\0')
        return -1;
    if(n > 2)
        return 0;    
    else if(n == 1){
        if(strcmp(acao, "novo") == 0)
            return 1;
        else if(strcmp(acao, "carregar") == 0)
            return 2;
        else if(strcmp(acao, "exibir") == 0)
            return 3;
        else if(strcmp(acao, "ajuda") == 0)
            return 4;
        else if(strcmp(acao, "salvar") == 0)
            return 5;
        else if(strcmp(acao, "sair") == 0)
            return 6;
        else 
            return 0;
    }
    return 0;
}

void removerEspaco(char *s){
    if (!s) return;

    // remove \n e \r se existirem (caso removeN não pegue todos)
    size_t len = strcspn(s, "\r\n");
    s[len] = '\0';

    // remove espaços/tabs do começo
    size_t start = 0;
    while (s[start] && isspace((unsigned char)s[start])) start++;

    if (start > 0) {
        memmove(s, s + start, strlen(s + start) + 1);
    }

    // remove espaços/tabs do fim
    len = strlen(s);
    while (len > 0 && isspace((unsigned char)s[len - 1])) {
        s[len - 1] = '\0';
        len--;
    }
}

void copiaComando(char *comando, char *saida){
    for(int i = 0; comando[i] != ' '; i++)
    saida[i] = comando[i];
}

Celula **alocaTabuleiro(int tam){
    
    Celula **jogo = malloc(sizeof(Celula*) *tam);
    if(jogo == NULL)
        return NULL;
    for(int i = 0; i < tam; i++){
        jogo[i] = malloc(sizeof(Celula) * tam);
        //se ocorrer um erro, libera as posições alocadas antes
        if(jogo[i] == NULL){
            for(int k = 0; k < i; k++){
                free(jogo[k]);
                free(jogo);
            }
            printf(ANSI_COLOR_RED);
            printf("\nNão foi possível alocar o tabuleiro, confira as entradas tente novamente");
            printf(ANSI_RESET);
            return NULL;
        }
    }
        return jogo;
    }
int **alocaMatriz(int tam){
    int **matriz = (int**)malloc(tam *sizeof(int*));
        if(matriz == NULL)
            return NULL;
    for(int i = 0; i < tam; i++){
        matriz[i] = (int*)malloc(sizeof(int) * tam);
        if(matriz[i] == NULL)
        for(int k = 0;k < i; k++){
            free(matriz[i]);
            free(matriz);
        }
    }
    return matriz;
}
int *alocaVetor(int tam){
    int * vetor = malloc(sizeof(int) * tam);
    return vetor;
}
void liberaTabuleiro(Celula **matriz, int tam){
    for(int i = 0; i < tam; i++)
        free(matriz[i]);
    free(matriz);
}
void liberaMatriz(int **matriz, int tam){
    for(int i = 0; i < tam; i++)
        free(matriz[i]);
    free(matriz);
}
int verificaComando(int *x, int *y){
    char comando2[30];
    char acao[11]; //10 letras + \0
    int a,b; //posições a serem lidas
    char lixo; //lixo que pode ser inserido pelo usuario "...1 1 abc"
    int opcao = 0;
    //Lê o comando do teclado e usa funções para formatar a entrada 
    fgets(comando2, sizeof(comando2), stdin);
    removerEspaco(comando2);
    removeN(comando2);
    //sscanf() lê de uma string e retorna a quantidade de membros encontrados
    int n = sscanf(comando2," %10s %d %d %c", acao, &a, &b, &lixo);
    convertM(acao);
    /*
    Se n > 3 o usuário digitou uma entrada inválida = ERRO 
    Se n = 1 entra na verificação se é voltar ou dica, se o teste falhar a  função retorna erro por padrão
    Se n = !3 O usuário não digitou as posições Lin x Col da matriz retorna erro por padrão 
    */
    if(n == 1){ 
        if(strcmp(acao, "resolver") == 0)
            return 5;
        else if(strcmp(acao, "sair") == 0)
            return 4;
        else if(strcmp(acao, "dica") == 0)
            return 3;
        else
            return 0;
    }
    else if(n != 3)
        return 0; //código de erro, comando inválido ou o usuário digitou o cmd sem a posição desejada
    else if(n == 3){
        if(strcmp(acao, "adicionar") == 0)
            opcao = 2;
        else if(strcmp(acao, "remover") == 0)
            opcao = 1;
        else
            return 0;
    }
    //verifica se o número é válido, ou seja se é menor que o tamaho do maior tabuleiro 
    if( a < 0 || a >= 7 || b < 0 || b >= 7)
        return 0;
    *x = a;
    *y = b;
    
    
    return opcao;

}

void adicionarPos(Celula **jogo, int lin, int col, int tam){
    if(lin > tam || col > tam)
        return;
    if(jogo[lin][col].estado == 1)
        jogo[lin][col].estado = 0; //se já estiver "verde" volta para o estado inicial 0
    else
        jogo[lin][col].estado = 1;
}
void removerPos(Celula **jogo, int lin, int col, int tam){
    if(lin > tam || col > tam)
        return;
    if(jogo[lin][col].estado == 2)
        jogo[lin][col].estado = 0; //se já estiver "vermelho" volta para o estado inicial 0
    else
        jogo[lin][col].estado = 2;
}
int verificaVitoria(jogoSumplete jogo){

    int somaLinha, somaColuna, cont = 0;
    for(int i = 0; i < jogo.tamMatriz; i++){
        somaLinha = somaLinReal(jogo, i);
        if(somaLinha == jogo.dicalin[i])
            cont++;
    }
    for(int j = 0; j < jogo.tamMatriz; j++){
        somaColuna = somaColReal(jogo, j);
        if(somaColuna == jogo.dicaCol[j])
            cont++;
    }
    if(cont == jogo.tamMatriz * 2)
        return 1; //retorna 1 se o jogador venceu
    else
        return 0; // e 0 se a soma das linhas e colunas ainda não estão corretas
}
void geraMatrizeDica(jogoSumplete *jogo){

    int somaLin, somaCol;
    //completa o tabuleiro com valores aleatórios de 1 a 9
    for(int i = 0; i < jogo->tamMatriz; i++){
        for(int j = 0; j < jogo->tamMatriz; j++){
            jogo->tabuleiro[i][j].valor = (rand() % 9) +1;
            jogo->tabuleiro[i][j].estado = 0;
        }
        }
// gera as posições removidas do tabuleiro com 1 para soma e 0 removido da soma
    for(int i = 0; i < jogo->tamMatriz; i++){
        for(int j = 0; j < jogo->tamMatriz; j++)
            jogo->mask[i][j] = rand() % 2;
    }
    //gera as dicas das linhas 
    for(int i = 0; i < jogo->tamMatriz; i++){
        somaLin = 0;
        for(int j = 0; j < jogo->tamMatriz; j++){
            if(jogo->mask[i][j] == 1)
                somaLin += jogo->tabuleiro[i][j].valor;
        }
        jogo->dicalin[i] = somaLin;
    }
    //gera as dicas das colunas
    for(int j = 0; j < jogo->tamMatriz; j++){
        somaCol = 0;
        for(int i = 0; i < jogo->tamMatriz; i++){
            if(jogo->mask[i][j] == 1)
                somaCol += jogo->tabuleiro[i][j].valor;
        }
        jogo->dicaCol[j] = somaCol;
    }

}
//procura a primeira posição que deve ser removida na máscara e compara se o estado é diferete de REMOVIDO se for remova a posição no tabuleiro
void mostrarDica(jogoSumplete *jogo){
    int c = 0;
    for(int i = 0; i < jogo->tamMatriz; i++){
        for(int j = 0; j < jogo->tamMatriz; j++){
            if(jogo->mask[i][j] == 0 && jogo->tabuleiro[i][j].estado != REMOVIDA){
                jogo->tabuleiro[i][j].estado = 2;
                c = 1;
                break;
            }
        }
        if(c)
            break;
    }

}
void resolverJogo(jogoSumplete *jogo){
    for(int i = 0; i < jogo->tamMatriz; i++){
        for(int j = 0; j < jogo->tamMatriz; j++){
            if(jogo->mask[i][j] == 0)
                jogo->tabuleiro[i][j].estado = REMOVIDA;
            else
                jogo->tabuleiro[i][j].estado = ATIVA;
        }
    }
}

int contaRemovidos(int **mask, int tamMatriz){
    int cont = 0;
    for(int i = 0; i < tamMatriz; i++){
        for(int j = 0; j < tamMatriz; j++){
            if(mask[i][j] == 0)
                cont++;
        }
    }
    return cont;
}

void esperaEnter(){
    char buf[64];

    printf("\nDigite \"ENTER\" para continuar: ");
    fgets(buf, sizeof(buf), stdin);
}
int lerLinha(char *buf, int tam){
    if (!fgets(buf, tam, stdin)) 
        return 0;
    removeN(buf);
    removerEspaco(buf);
    return 1;
}