#include <stdio.h>
#include <stdlib.h>  // Necessário para abs()

#define TAMANHO_TABULEIRO 10
#define TAMANHO_HABILIDADE 5
#define NAVIO 3
#define HABILIDADE 5

// Inicializa o tabuleiro com água (0)
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Exibe o tabuleiro com representação visual
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) printf(". ");
            else if (tabuleiro[i][j] == NAVIO) printf("N ");
            else if (tabuleiro[i][j] == HABILIDADE) printf("* ");
            else printf("? "); // Caso especial
        }
        printf("\n");
    }
}

// Posiciona navios simples (para visualização)
void posicionar_navios(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Navio horizontal
    for (int i = 0; i < 3; i++)
        tabuleiro[2][2 + i] = NAVIO;

    // Navio vertical
    for (int i = 0; i < 3; i++)
        tabuleiro[5 + i][5] = NAVIO;
}

// Cria matriz de habilidade CONE (forma triangular para baixo)
void criar_cone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (j >= (TAMANHO_HABILIDADE - 1) / 2 - i &&
                j <= (TAMANHO_HABILIDADE - 1) / 2 + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria matriz de habilidade CRUZ (horizontal + vertical com centro)
void criar_cruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == TAMANHO_HABILIDADE / 2 || j == TAMANHO_HABILIDADE / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria matriz de habilidade OCTAEDRO (losango)
void criar_octaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (abs(i - TAMANHO_HABILIDADE / 2) + abs(j - TAMANHO_HABILIDADE / 2) <= TAMANHO_HABILIDADE / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Sobrepõe a matriz de habilidade no tabuleiro, com origem (lin,col)
void aplicar_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                        int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                        int origem_linha, int origem_coluna) {
    int offset = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linha = origem_linha + i - offset;
                int coluna = origem_coluna + j - offset;

                // Verifica se está dentro dos limites do tabuleiro
                if (linha >= 0 && linha < TAMANHO_TABULEIRO &&
                    coluna >= 0 && coluna < TAMANHO_TABULEIRO &&
                    tabuleiro[linha][coluna] == 0) {
                    tabuleiro[linha][coluna] = HABILIDADE;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // Inicializa o tabuleiro com água
    inicializar_tabuleiro(tabuleiro);

    // Posiciona navios fixos
    posicionar_navios(tabuleiro);

    // Cria as formas das habilidades
    criar_cone(cone);
    criar_cruz(cruz);
    criar_octaedro(octaedro);

    // Aplica as habilidades em posições fixas no tabuleiro
    aplicar_habilidade(tabuleiro, cone, 2, 4);      // Cone a partir da linha 2, coluna 4
    aplicar_habilidade(tabuleiro, cruz, 5, 2);      // Cruz no centro-esquerda
    aplicar_habilidade(tabuleiro, octaedro, 7, 7);  // Octaedro canto inferior direito

    // Exibe o tabuleiro final
    exibir_tabuleiro(tabuleiro);

    return 0;
}
