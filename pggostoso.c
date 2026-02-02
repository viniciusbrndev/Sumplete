#include <stdio.h>
#include 
int verificaComando(char *comando, int *x, int *y){
    char acao[10];
    int opcao;
    int i;
    
    //copia o comando "adicionar", "remover" ou "sair"
    for(i = 0; comando[i] != ' '; i++)
        acao[i] = comando[i];
    convertM(acao); //converte letras maiúsculas para minúsculas
    
    
    int tam = strlen(comando);
    if(tam == REMOVER){ 
        if(strcmp(acao, "remover" && comando[i+2] == ' ') == 0)
            opcao = 1;
        }
int main(){
    char c = '2';
    int a = c;
    printf("%d", a);

    return 0;
}



