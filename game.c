//Bibliotecas
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
//constantes
#define VAZIA 0
#define ATIVA 1
#define REMOVIDA 2
#define REMOVER 11
#define ADICIONAR 12
//Elementos para tabelas
#define TAB_HOR "\u2501" // ━ (horizontal)
#define TAB_VER "\u2503" // ┃ (vertical)
#define TAB_TL "\u250F" // ┏ (canto superior esquerdo)
#define TAB_ML "\u2523" // ┣ (meio-esquerda)
#define TAB_BL "\u2517" // ┗ (canto inferior esquerdo)
#define TAB_TJ "\u2533" // ┳ (top-join)
#define TAB_MJ "\u254B" // ╋ (junção do meio)
#define TAB_BJ "\u253B" // ┻ (junção inferior)
#define TAB_TR "\u2513" // ┓ (canto superior direito)
#define TAB_MR "\u252B" // ┫ (meio-direita)
#define TAB_BR "\u251B" // ┛ (canto inferior direito)
// cores e formato de texto
#define ANSI_RESET "\x1b[0m" // desativa os efeitos anteriores
#define ANSI_BOLD "\x1b[1m" // coloca o texto em preto
#define ANSI_COLOR_BLACK "\x1b[30m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_WHITE "\x1b[37m"
#define ANSI_BG_COLOR_BLACK "\x1b[40m"
#define ANSI_BG_COLOR_RED "\x1b[41m"
#define ANSI_BG_COLOR_GREEN "\x1b[42m"
#define ANSI_BG_COLOR_YELLOW "\x1b[43m"
#define ANSI_BG_COLOR_BLUE "\x1b[44m"
#define ANSI_BG_COLOR_MAGENTA "\x1b[45m"
#define ANSI_BG_COLOR_CYAN "\x1b[46m"
#define ANSI_BG_COLOR_WHITE "\x1b[47m"
#define ANSI_COLOR_GRAY  "\x1b[90m"
// macros para facilitar o uso
#define NEGRITO(string) ANSI_NEGRITO string ANSI_RESET
#define BLACK(string) ANSI_COLOR_BLACK string ANSI_RESET
#define BLUE(string) ANSI_COLOR_BLUE string ANSI_RESET
#define RED(string) ANSI_COLOR_RED string ANSI_RESET
#define GREEN(string) ANSI_COLOR_GREEN string ANSI_RESET
#define AMARELO(string) ANSI_COLOR_AMARELO string ANSI_RESET
#define BLUE(string) ANSI_COLOR_BLUE string ANSI_RESET
#define MAGENTA(string) ANSI_COLOR_MAGENTA string ANSI_RESET
#define CYAN(string) ANSI_COLOR_CYAN string ANSI_RESET
#define WHITE(string) ANSI_COLOR_WHITE string ANSI_RESET
#define GRAY(string) ANSI_COLOR_GRAY string ANSI_COLOR_RESET
#define BG_BLACK(string) ANSI_BG_COLOR_BLACK string ANSI_RESET
#define BG_BLUE(string) ANSI_BG_COLOR_BLUE string ANSI_RESET
#define BG_RED(string) ANSI_BG_COLOR_RED string ANSI_RESET
#define BG_GREEN(string) ANSI_BG_COLOR_GREEN string ANSI_RESET
#define BG_YELLOW(string) ANSI_BG_COLOR_YELLOW string ANSI_RESET
#define BG_BLUE(string) ANSI_BG_COLOR_BLUE string ANSI_RESET
#define BG_MAGENTA(string) ANSI_BG_COLOR_MAGENTA string ANSI_RESET
#define BG_CYAN(string) ANSI_BG_COLOR_CYAN string ANSI_RESET
#define BG_WHITE(string) ANSI_BG_COLOR_WHITE string ANSI_RESET


void imprimirMenuInicial(){
    printf("ANSI_COLOR_GREEN\n");
    printf("\n╔═════════════ MENU PRINCIPAL ════════════════╗\n");
    printf("║                                             ║\n");
    printf("║   [novo]     -> Iniciar um novo jogo        ║\n");
    printf("║   [carregar] -> Carregar jogo salvo         ║\n");
    printf("║   [exibir]   -> Exibir ranking              ║\n");
    printf("║   [ajuda]    -> Mostrar comandos            ║\n");
    printf("║   [sair]     -> Encerrar o jogo             ║\n");
    printf("║                                             ║\n");
    printf("╚═════════════════════════════════════════════╝\n");
    printf(ANSI_RESET);
    printf("\nDIGITE UM COMANDO: ");

}
int somaLinReal(Celula **matriz, int tamMatriz, int poslin){
    int soma = 0;
    for(int i = 0; i < tamMatriz; i++){
        if(matriz[poslin][i].estado != REMOVIDA)
            soma += matriz[poslin][i].valor;
    }
    return soma;
}
int somaColReal(Celula **matriz, int tamMatriz, int poscol){
    int soma = 0;
    for(int i = 0; i < tamMatriz; i++){
        if(matriz[i][poscol].estado != REMOVIDA)
            soma += matriz[i][poscol].valor;
    }
    return soma;

}

void imprimeTabela(char nivel, Celula **matriz, int *dicaLin, int *dicaCol){
    int cont;

    if(nivel == 'F') cont = 2;
    else if(nivel=='M') cont = 4;
    else if(nivel == 'D') cont = 6;
    else{
        printf("Dificuldade inválida\n");
        return;
    }

    int n = cont + 1; // tamanho real (valores 1..9)

    // -------- TOPO --------
    printf("%s", TAB_TL);
    for(int i = 0; i < n-1; i++){
        printf("%s%s%s%s", TAB_HOR, TAB_HOR, TAB_HOR, TAB_TJ);
    }
    printf("%s%s%s%s\n", TAB_HOR, TAB_HOR, TAB_HOR, TAB_TR);

    // -------- CORPO --------
    for(int k = 0; k < n; k++){

        for(int i = 0; i < n; i++){
            int v = matriz[k][i].valor;

            if(matriz[k][i].estado == ATIVA){
                printf("%s%s %d %s", TAB_VER, ANSI_BG_COLOR_GREEN, v, ANSI_RESET);
            }
            else if(matriz[k][i].estado == REMOVIDA){
                printf("%s%s %d %s", TAB_VER, ANSI_BG_COLOR_RED, v, ANSI_RESET);
            }
            else{
                printf("%s %d ", TAB_VER, v);
            }
        }

        // dica da linha no final
        int somaliReal = somaLinReal(matriz, n, k); 
        if(somaliReal == dicaLin[k]){
            printf("%s %d\n", TAB_VER, dicaLin[k]);
        }
        else{
            printf("%s%s %d%s\n", TAB_VER, ANSI_COLOR_GRAY, dicaLin[k], ANSI_RESET);
        }

        // -------- LINHA DO MEIO (ENTRE LINHAS) --------
        if(k < n-1){
            printf("%s", TAB_ML);
            for(int i = 0; i < n-1; i++){
                printf("%s%s%s%s", TAB_HOR, TAB_HOR, TAB_HOR, TAB_MJ);
            }
            printf("%s%s%s%s\n", TAB_HOR, TAB_HOR, TAB_HOR, TAB_MR);
        }
    }

    // -------- BORDA INFERIOR --------
    printf("%s", TAB_BL);
    for(int i = 0; i < n-1; i++){
        printf("%s%s%s%s", TAB_HOR, TAB_HOR, TAB_HOR, TAB_BJ);
    }
    printf("%s%s%s%s\n", TAB_HOR, TAB_HOR, TAB_HOR, TAB_BR);

    // -------- DICAS DAS COLUNAS --------
    printf("  ");
    
    for(int i = 0; i < n; i++){
        int somaclReal = somaColReal(matriz,n, i);
        if(somaclReal == dicaCol[i])
            printf("%2d  ", dicaCol[i]);
        else
            printf("%s%2d  %s", ANSI_COLOR_GRAY,dicaCol[i], ANSI_RESET);
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

int verificarCmdMenu(char *comando){
    if(strcmp(comando,"novo") == 0)
        return 1;
    else if(strcmp(comando, "carregar") == 0)
        return 2;
    else if(strcmp(comando, "exibir") == 0)
        return 3;
    else if(strcmp(comando, "ajuda") == 0)
        return 4;
    else if(strcmp(comando, "sair") == 0)
        return 5;
    else
        return 0; //comando incorreto ou inexistente
}

void removerEspaco(char *comando){
    int tam = strlen(comando);
    //puxa as letras após o último espaço para o começo da string
    for(int i = 0; comando[i] == ' ' || comando[i] == '\t'; i++){
        for(int j =0; j < tam; j++){
            comando[j] = comando[j+1];
        }
        tam--;

    }
    int i;
    for(i= tam -1; comando[i] == ' ' || comando[i] == '\t'; i--){

    }
    comando[i+1] = '\0';



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
    for(int i = 0; i < tam; i++){
        matriz[i] = (int*)malloc(sizeof(int) * tam);
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
        else if(strcmp(acao, "voltar") == 0)
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
int verificaVitoria(Celula **matriz,const int *sumLin,const int *sumCol, int tam){

    int somaLinha, somaColuna, cont = 0;
    for(int i = 0; i < tam; i++){
        somaLinha = 0;
        for(int j = 0; j < tam; j++){
            if(matriz[i][j].estado != REMOVIDA)
                somaLinha += matriz[i][j].valor;
        }
        if(somaLinha == sumLin[i])
            cont++;
    }
    for(int j = 0; j < tam; j++){
        somaColuna = 0;
        for(int i = 0; i < tam; i++)
            if(matriz[i][j].estado != REMOVIDA)
                somaColuna += matriz[i][j].valor;

        if(somaColuna == sumCol[j])
            cont++;
    }
    if(cont == tam * 2)
        return 1; //retorna 1 se o jogador venceu
    else
        return 0; // e 0 se a soma das linhas e colunas ainda não estão corretas
}
void geraMatrizeDica(Celula **matriz1,int **matriz2,int *lin, int *col, const int tam){

    int somaLin, somaCol;
    //completa o tabuleiro com valores aleatórios de 1 a 9
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            matriz1[i][j].valor = (rand() % 9) +1;
            matriz1[i][j].estado = 0;
        }
        }
// gera as posições removidas do tabuleiro com 1 para soma e 0 removido da soma
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++)
            matriz2[i][j] = rand() % 2;
    }
    //gera as dicas das linhas 
    for(int i = 0; i < tam; i++){
        somaLin = 0;
        for(int j = 0; j < tam; j++){
            if(matriz2[i][j] == 1)
                somaLin += matriz1[i][j].valor;
        }
        lin[i] = somaLin;
    }
    //gera as dicas das colunas
    for(int j = 0; j < tam; j++){
        somaCol = 0;
        for(int i = 0; i < tam; i++){
            if(matriz2[i][j] == 1)
                somaCol += matriz1[i][j].valor;
        }
        col[j] = somaCol;
    }

}
//procura a primeira posição que deve ser removida na máscara e compara se o estado é diferete de REMOVIDO se for remova a posição no tabuleiro
void mostrarDica(Celula **tabuleiro, int **mask,int tamMatriz){
    int c = 0;
    for(int i = 0; i < tamMatriz; i++){
        for(int j = 0; j < tamMatriz; j++){
            if(mask[i][j] == 0 && tabuleiro[i][j].estado != REMOVIDA){
                tabuleiro[i][j].estado = 2;
                c = 1;
                break;
            }
        }
        if(c)
            break;
    }

}