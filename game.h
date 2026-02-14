#if !defined(GAME_H)
#define GAME_H

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
    typedef struct
    {
        int valor;
        int estado;
    }Celula;
    void imprimirMenuInicial();
    int somaLinReal(Celula **matriz, int tamMatriz, int poslin);
    int somaColReal(Celula **matriz, int tamMatriz, int poscol);
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
    int verificaComando(int *x, int *y);
    void adicionarPos(Celula **jogo, int lin, int col, int tam);
    void removerPos(Celula **jogo, int lin, int col, int tam);
    int verificaVitoria(Celula **matriz,const int *sumLin,const int *sumCol, int tam);
    void geraMatrizeDica(Celula **matriz1,int **matriz2,int *lin, int *col, const int tam);
    void mostrarDica(Celula **tabuleiro, int **mask,int tamMatriz);
    void resolverJogo(Celula **tabuleiro, int **mask, int tamMatriz);
    int contaRemovidos(int **mask, int tamMatriz);
#endif // GAME_H
