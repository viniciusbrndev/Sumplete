# 🧩 Sumplete — Jogo de Lógica Numérica em C

[![C Standard](https://img.shields.io/badge/c-c99-blue.svg)](https://en.wikipedia.org/wiki/C99)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey.svg)]()

Uma implementação completa, interativa em terminal e desenvolvida em C do popular jogo de lógica numérica **Sumplete** (originalmente concebido através de interações com o ChatGPT).

O projeto conta com alocação dinâmica de memória, sistema de persistência de estado (save/load), ranking de melhores tempos, suporte a múltiplos níveis de dificuldade e interface colorida via sequências de escape ANSI com bordas em caracteres Unicode.

---

## 📋 Sumário

- [Visão Geral](#-visão-geral)
- [Regras e Mecânica do Jogo](#-regras-e-mecânica-do-jogo)
- [Recursos do Projeto](#-recursos-do-projeto)
- [Arquitetura do Código](#-arquitetura-do-código)
- [Estrutura do Arquivo de Save (`.sum`)](#-estrutura-do-arquivo-de-save-sum)
- [Compilação e Execução](#-compilação-e-execução)
- [Como Jogar (Comandos)](#-como-jogar-comandos)
- [Autor e Créditos](#-autor-e-créditos)

---

## 🔍 Visão Geral

O **Sumplete** é um quebra-cabeça de lógica matemática. O jogador recebe uma grade de números inteiros aleatórios (1 a 9) e valores-alvo ("dicas") situados ao final de cada linha e coluna. 

O objetivo é **remover** ou **manter** números da grade de modo que a soma dos elementos ativos em cada linha e coluna corresponda exatamente aos valores-alvo das bordas.

---

## 🎯 Regras e Mecânica do Jogo

1. **Grade de Números:** Cada célula contém um número inteiro entre 1 e 9.
2. **Estados das Células:**
   - **Normal (Padrão):** O valor permanece na contagem da soma.
   - **Ativa (Verde):** Marcada pelo jogador como confirmada na soma.
   - **Removida (Vermelho):** Excluída da contagem da soma da linha e coluna.
3. **Indicadores de Soma (Dicas):**
   - Ao lado de cada linha e abaixo de cada coluna, é exibido o resultado esperado.
   - Quando a soma dos elementos mantidos em uma linha/coluna atinge exatamente a dica, o valor da dica é destacado em **verde**.
4. **Condição de Vitória:** O jogo é finalizado com vitória quando **todas** as linhas e colunas atingirem suas respectivas somas-alvo simultaneamente.

---

## ✨ Recursos do Projeto

- 🎮 **3 Níveis de Dificuldade:**
  - **Fácil (F):** Matriz $3 	imes 3$
  - **Médio (M):** Matriz $5 	imes 5$
  - **Difícil (D):** Matriz $7 	imes 7$
- 💾 **Gerenciamento de Saves:** Permite salvar e carregar o progresso a qualquer momento usando arquivos com extensão customizada `.sum`.
- 🏆 **Sistema de Ranking:** Registra os 10 melhores tempos de conclusão em arquivo permanente (`sumplete.rnk`).
- 💡 **Sistema de Dicas e Auto-Resolver:**
  - `dica`: Revela/remove automaticamente uma posição que deveria ser eliminada segundo a máscara da solução.
  - `resolver`: Exibe a solução completa do tabuleiro instantaneamente.
- 🎨 **Interface Rica no Terminal:** Renderização com tabelas formatadas em Unicode e cores dinâmicas via ANSI Escapes.
- ⏱️ **Cronometragem de Sessão:** Contagem do tempo total gasto no jogo (acumulado mesmo entre salvamentos).
- 🛡️ **Tratamento de Entradas:** Funções robustas para validação de comandos, prevenção de *overflow* de *buffer* e sanitização de strings.

---

## 📁 Arquitetura do Código

O projeto está organizado nos seguintes módulos:

```text
.
├── archives.c / archives.h # Persistência de dados (Salvar / Carregar jogo em disco)
├── game.c / game.h         # Lógica do jogo, manipulação da matriz, interface e comandos
├── main.c                  # Ponto de entrada, loop principal e gerenciamento de menus
├── ranking.c / ranking.h   # Leitura, ordenação, inserção e salvamento do ranking
├── types.h                 # Definições de estruturas, constantes e códigos ANSI/Unicode
└── sumplete.rnk            # Arquivo de persistência do ranking (gerado automaticamente)
```

### Principais Estruturas (`types.h`)

```c
typedef struct {
    int valor;  // Valor numérico da célula (1-9)
    int estado; // 0 = VAZIA/NORMAL, 1 = ATIVA, 2 = REMOVIDA
} Celula;

typedef struct {
    char nome[28];
    int tamMatriz;
    Celula **tabuleiro;
    int **mask;       // Máscara binária da solução gerada (1 = mantém, 0 = remove)
    int *dicalin;     // Vetor com as somas esperadas das linhas
    int *dicaCol;     // Vetor com as somas esperadas das colunas
    int tempoTotal;   // Tempo decorrido em segundos
} jogoSumplete;

typedef struct {
    char nome[28];
    int tempoTotal;
} PosRanking;
```

---

## 📄 Estrutura do Arquivo de Save (`.sum`)

Os arquivos de salvamento guardam o estado exato da partida para restauração posterior:

```text
<tamanho_matriz>
<valores_da_matriz_linha_por_linha>
<dicas_das_linhas>
<dicas_das_colunas>
<quantidade_de_celulas_removidas_na_solucao>
<posicoes_solucao_removidas_lin_col>
<quantidade_de_jogadas_efetuadas_pelo_usuario>
<estado_das_jogadas_'a'_ou_'r'_lin_col>
<nome_do_jogador>
<tempo_total_em_segundos>
```

---

## 🛠️ Compilação e Execução

### Pré-requisitos

- Compilador C compatível com C99 (`gcc`, `clang`, MSVC).
- Terminal com suporte a UTF-8 e cores ANSI (ex: Bash, Zsh, Windows Terminal, PowerShell moderno).

### Compilando via `gcc`

Para compilar todos os arquivos fonte em um único executável:

```bash
gcc -std=c99 main.c game.c archives.c ranking.c -o sumplete -Wall
```

### Executando

- **Linux / macOS:**
  ```bash
  ./sumplete
  ```
- **Windows (PowerShell / Prompt):**
  ```cmd
  sumplete.exe
  ```

---

## 🎮 Como Jogar (Comandos)

### Menu Principal

Ao iniciar o programa, escolha uma das opções:
- `novo` — Inicia uma nova partida (solicita nome do jogador e dificuldade).
- `carregar` — Carrega uma partida salva de um arquivo `.sum`.
- `exibir` — Exibe a tabela dos 10 melhores tempos do ranking.
- `ajuda` — Exibe o tutorial e regras do jogo.
- `salvar` — Salva a partida atualmente ativa.
- `continuar` — Retorna ao jogo em andamento.
- `sair` — Encerra a aplicação.

### Durante a Partida

Digite as instruções no prompt do jogador:

| Comando | Sintaxe | Descrição |
| :--- | :--- | :--- |
| **Adicionar** | `adicionar <LIN> <COL>` | Marca a célula como **ATIVA** (verde). Alterna para normal se já estiver ativa. |
| **Remover** | `remover <LIN> <COL>` | Marca a célula como **REMOVIDA** (vermelha). Alterna para normal se já estiver removida. |
| **Dica** | `dica` | Aplica automaticamente uma remoção correta com base na solução. |
| **Resolver** | `resolver` | Preenche o tabuleiro com a solução completa. |
| **Sair** | `sair` | Pausa a partida e retorna ao menu principal. |

> **Exemplo:** `adicionar 1 2` marca o elemento da **Linha 1, Coluna 2** como ativo.

---

## 👤 Autor e Créditos

- **Autor:** Vinícius Brandão de Souza Oliveira
- **Instituição:** Universidade Federal de Ouro Preto (UFOP)
- **Disciplina:** BCC201 — Introdução à Programação
- **Orientador:** Prof. Puca Huachi

---
*Projeto desenvolvido para fins acadêmicos.*
