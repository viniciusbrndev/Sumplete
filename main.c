#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "ranking.h"


int main(){
    int menuInicial;
    char comando[10];
    
    
    imprimirMenuInicial();
    fgets(comando, sizeof(char) * 10; stdin);
    removeN(comando);
    convertM(comando);

    while (1){

        if(menuInicial == 1){
            char nome[28];
            char nivel;
            getchar();
            printf("Digite o nome do jogador: ");
            fgets(nome, sizeof(char) * 28,stdin);
            printf("Digite o nivel de dificuldade: ");
            nivel = getchar();
            while(1){
                imprimeTabela(nivel);
                printf("%s, digite o comando: ", nome);
                break;
            }
            


            
        }
    }
    



}
