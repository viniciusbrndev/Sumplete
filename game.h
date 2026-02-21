// Vinícius Brandão de S. Oliveira Matrícula 25.2.4154
#ifndef GAME_H
#define GAME_H



    void imprimirMenuInicial();
    int somaLinReal(jogoSumplete jogo, int poslin);
    int somaColReal(jogoSumplete jogo, int poscol);
    void imprimeTabela(jogoSumplete jogo);
    void convertM(char *palavra);
    void removeN(char *palavra);
    void limparBuffer();
    int linhaSegura(char *linha, int tam);
    int verificarCmdMenu();
    void removerEspaco(char *comando);
    void copiaComando(char *comando, char *saida);
    //--------------alocação dinâmica-------------
    Celula **alocaTabuleiro(int tam);
    int **alocaMatriz(int tam);
    int *alocaVetor(int tam);
    void liberaTabuleiro(Celula **matriz, int tam);
    void liberaMatriz(int **matriz, int tam);
    //--------------------------------------------
    int verificaComando(int *x, int *y);
    void adicionarPos(Celula **jogo, int lin, int col, int tam);
    void removerPos(Celula **jogo, int lin, int col, int tam);
    int verificaVitoria(jogoSumplete jogo);
    void geraMatrizeDica(jogoSumplete *jogo);
    void mostrarDica(jogoSumplete *jogo);
    void resolverJogo(jogoSumplete *jogo);
    int contaRemovidos(int **mask, int tamMatriz);
    void esperaEnter();
    void liberaJogo(jogoSumplete *jogo);
    int verificanArquivo(char *linha, int tam);
#endif // GAME_H
