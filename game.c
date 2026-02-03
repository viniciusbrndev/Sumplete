//Bibliotecas
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
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

void imprimeTabela(char nivel, Celula **matriz){
    int cont;

    if(nivel == 'F'){
        cont = 2;
    }
    else if(nivel=='M'){
        cont = 4;
    }
    else if(nivel == 'D'){
        cont = 6;
    
    }
    else{
        printf("Dificuldade inválida");
        return;
    }

    printf("%s", TAB_TL);
    for(int i = 0; i < cont; i++){
        printf("%s%s%s%s", TAB_HOR,TAB_HOR,TAB_HOR, TAB_TJ);   //imprime a parte de cima
    }
    printf("%s%s%s%s\n", TAB_HOR, TAB_HOR, TAB_HOR, TAB_TR);
    
    //imprime o meio da tabela 
    for(int k = 0; k < cont+1;k++){
        
        for(int i = 0; i < cont+1; i++){
            
            if(matriz[k][i].estado == ATIVA){
                printf("%s%s %d %s", TAB_VER,ANSI_BG_COLOR_GREEN,  matriz[k][i].valor, ANSI_RESET);
            }
            else if(matriz[k][i].estado == REMOVIDA){
                printf("%s%s %d %s", TAB_VER,ANSI_BG_COLOR_RED,  matriz[k][i].valor, ANSI_RESET);
            }
            //Vazia / estado inicial
            else{
                printf("%s %d ", TAB_VER, matriz[k][i].valor);
            }
            
            printf("%s %d ", TAB_VER, 3);
        }
        printf("%s %d\n", TAB_VER, 2); //ultimo e dica
    }

        printf("%s", TAB_ML);
        for(int i = 0; i < cont; i++)
            printf("%s%s%s%s", TAB_HOR,TAB_HOR, TAB_HOR, TAB_MJ);
        printf("%s%s%s%s\n", TAB_HOR,TAB_HOR, TAB_HOR, TAB_MR);

        
    

    for(int k = 0; k<cont+1; k++){
        for(int i = 0; i<cont+1; i++){
            printf("%s %d ", TAB_VER, matriz[k][i].valor);
        }
    }
    printf("%s %d\n", TAB_VER, 2); //ultimo e dica


    printf("%s", TAB_BL);
    for(int i = 0; i < cont; i++)
        printf("%s%s%s%s", TAB_HOR,TAB_HOR, TAB_HOR, TAB_BJ);
    printf("%s%s%s%s\n", TAB_HOR,TAB_HOR, TAB_HOR, TAB_BR);
    
    printf("  ");
    for(int i =0; i<cont+1; i++){
        printf("%d   ", 2);
    }
    printf("\n");
    printf("-> \"adicionar\"\n->\"remover\"\n->\"salvar\"\n->\"dica\"\n->\"sair\"\n");
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

Celula **alocaMatriz(int tam){
    
    Celula **jogo = malloc(sizeof(Celula*) *tam);
    for(int i = 0; i < tam; i++)
        jogo[i] = malloc(sizeof(Celula) * tam);
    return jogo;
    if(jogo == NULL){
        printf(ANSI_COLOR_RED);
        printf("\nNão foi possível alocar o tabuleiro, confira as entradas tente novamente");
        printf(ANSI_RESET);
    }
    }
void liberaMatriz(Celula **matriz, int tam){
    for(int i = 0; i < tam; i++)
        free(matriz[i]);
    free(matriz);
}
int verificaComando(char *comando, int *x, int *y){
    char acao[11];
    int opcao = 0;
    int i;
    
    //copia o comando "adicionar", "remover" ou "sair"
    for(i = 0; i < 10 && comando[i] != ' ' && comando[i] != '\0' && comando[i] != '\t'; i++)
        acao[i] = comando[i];
    acao[i] = '\0';
    convertM(acao); //converte letras maiúsculas para minúsculas
    
    
    int tam = strlen(comando);
    if(tam == REMOVER){ 
        if(strcmp(acao, "remover") == 0 && comando[i+2] == ' ')
            opcao = 1;
        }//->compara a entrada do usuário com espaços removidos do final e começo para saber se está no formato (comando lin col)
    else if(tam == ADICIONAR)
        if(strcmp(acao, "adicionar") == 0 && comando[i+2] == ' ')
            opcao = 2;
    else if(strcmp(acao, "voltar") == 0)
        return 3;
    //verifica a formatação dos números e retorna as posições x e y ou 0 caso  ocomando seja inválido
    if(comando[i+1] >= '0' && comando[i+1] <= '9' && comando[i+3] >= '0' && comando[i+3] <= '9'){
        *x = comando[i+1] - 48;
        *y = comando[i+3] - 48;
        return opcao;
    }
    return 0;


}
