#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
    printf("\n╔═════════════ MENU PRINCIPAL ══════════════╗\n");
    printf("║                                             ║\n");
    printf("║   [novo]      Iniciar um novo jogo          ║\n");
    printf("║   [carregar]  Carregar jogo salvo           ║\n");
    printf("║   [exibir]    Exibir ranking                ║\n");
    printf("║   [comandos]  Mostrar comandos              ║\n");
    printf("║   [sair]      Encerrar o jogo               ║\n");
    printf("║                                             ║\n");
    printf("╚═════════════════════════════════════════════╝\n");
    printf(ANSI_RESET);


}

void imprimeTabela(char nivel){
    int cont;

    if(nivel == 'F'){
        cont = 2;
    
    }
    else if(nivel=='M'){
        cont = 4;
        
    }
    else{
        
        cont = 6;
    
    }

    printf("%s", TAB_TL);
    for(int i= 0; i<cont;i++){
        printf("%s%s%s%s", TAB_HOR,TAB_HOR,TAB_HOR, TAB_TJ);   //imprime a parte de cima
    }
    printf("%s%s%s%s\n", TAB_HOR, TAB_HOR, TAB_HOR, TAB_TR);

    for(int k =0; k<cont;k++){

        for(int i =0; i<cont+1; i++){
            printf("%s %d ", TAB_VER, 3);
        }
        printf("%s %d\n", TAB_VER, 2); //ultimo e dica


        printf("%s", TAB_ML);
        for(int i = 0; i < cont; i++)
            printf("%s%s%s%s", TAB_HOR,TAB_HOR, TAB_HOR, TAB_MJ);
        printf("%s%s%s%s\n", TAB_HOR,TAB_HOR, TAB_HOR, TAB_MR);

        
    }

    for(int i =0; i<cont+1; i++){
            printf("%s %d ", TAB_VER, 3);
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
}   

