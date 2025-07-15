#include <stdio.h>

#define TAMANHO 10
#define TAMANHO_NAVIO 3
#define NAVIO 3

// Função para verificar se as posições estão livres
int posicao_livre(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    return tabuleiro[linha][coluna] == 0;
}

// Função para verificar se há espaço para posicionar o navio
int pode_posicionar(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int direcao, char tipo) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;

        if (tipo == 'H') c += i;
        else if (tipo == 'V') l += i;
        else if (tipo == 'D') { l += i; c += i; }      // ↘ diagonal crescente
        else if (tipo == 'I') { l += i; c -= i; }      // ↙ diagonal inversa

        if (l >= TAMANHO || c < 0 || c >= TAMANHO || !posicao_livre(tabuleiro, l, c))
            return 0;
    }
    return 1;
}

// Função para posicionar navios no tabuleiro
void posicionar_navio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char tipo) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;

        if (tipo == 'H') c += i;
        else if (tipo == 'V') l += i;
        else if (tipo == 'D') { l += i; c += i; }  // ↘
        else if (tipo == 'I') { l += i; c -= i; }  // ↙

        tabuleiro[l][c] = NAVIO;
    }
}

// Função para exibir o tabuleiro
void exibir_tabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\nTabuleiro (0 = água, 3 = navio):\n\n");

    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Declaração e inicialização do tabuleiro
    int tabuleiro[TAMANHO][TAMANHO] = {0};

    // Coordenadas e direções dos 4 navios
    // Navios retos
    if (pode_posicionar(tabuleiro, 1, 1, 0, 'H'))  // horizontal
        posicionar_navio(tabuleiro, 1, 1, 'H');

    if (pode_posicionar(tabuleiro, 4, 2, 0, 'V'))  // vertical
        posicionar_navio(tabuleiro, 4, 2, 'V');

    // Navios diagonais
    if (pode_posicionar(tabuleiro, 6, 6, 0, 'D'))  // diagonal ↘
        posicionar_navio(tabuleiro, 6, 6, 'D');

    if (pode_posicionar(tabuleiro, 0, 4, 0, 'I'))  // diagonal ↙
        posicionar_navio(tabuleiro, 0, 4, 'I');

    // Exibe o tabuleiro final
    exibir_tabuleiro(tabuleiro);

    return 0;
}
