#if !defined(GAME_H)
#define GAME_H
    typedef struct
    {
        int num;
        int estado;
    }Jogo;
    void imprimirMenuInicial();
    void imprimeTabela(char nivel);
    void convertM(char *palavra);
    void removeN(char *palavra);
    void limparBuffer();
    int verificarCmdMenu(char *comando)

#endif // GAME_H
