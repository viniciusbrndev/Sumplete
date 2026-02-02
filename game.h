#if !defined(GAME_H)
#define GAME_H
    typedef struct
    {
        int valor;
        int estado;
    }Celula;
    void imprimirMenuInicial();
    void imprimeTabela(char nivel, Celula **tabuleiro);
    void convertM(char *palavra);
    void removeN(char *palavra);
    void limparBuffer();
    int verificarCmdMenu(char *comando);
    void removerEspaco(char *comando);
    void copiaComando(char *comando, char *saida);
    Celula **alocaMatriz(int tam);
    void liberaMatriz(Celula **matriz, int tam);
    int verificaComando(char *comando, int *x, int *y);
#endif // GAME_H
