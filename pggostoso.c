#include <stdio.h>
#include "game.c"


int main(){
    char c = '2';
    int a = c;
    printf("%d", a);
    int x, y;
    char comando[13] = "remover 1 1";
    int res = verificaComando(comando, &x, &y);
    printf("%d", res);
    return 0;
}



