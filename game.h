#if !defined(GAME_H)
#define GAME_H
    typedef struct
    {
        int valor;
        int estado;
    }Celula;
    void imprimirMenuInicial();
    void imprimeTabela(char nivel, Celula **matriz, int *dicaLin, int *dicaCol);
    void convertM(char *palavra);
    void removeN(char *palavra);
    void limparBuffer();
    int verificarCmdMenu(char *comando);
    void removerEspaco(char *comando);
    void copiaComando(char *comando, char *saida);
    //--------------alocação dinâmica-------------
    Celula **alocaTabuleiro(int tam);
    int **alocaMatriz(int tam);
    int *alocaVetor(int tam);
    void liberaTabuleiro(Celula **matriz, int tam);
    void liberaMatriz(int **matriz, int tam);
    //--------------------------------------------
    int verificaComando(const char *comando, int *x, int *y);
    void adicionarPos(Celula **jogo, int lin, int col, int tam);
    void removerPos(Celula **jogo, int lin, int col, int tam);
    int verificaVitoria(const Celula **matriz,const int *sumLin,const int *sumCol, int tam);
    void geraMatrizeDica(Celula **matriz1,int **matriz2,int *lin, int *col, const int tam);
#endif // GAME_H
