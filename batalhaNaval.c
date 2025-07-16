#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

int main() {
    // Declaração da matriz do tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa todas as posições do tabuleiro com 0 (água)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Navio 1: posição horizontal (linha 2, coluna 1 até 3)
    int linhaNavio1 = 2;
    int colunaNavio1 = 1;

    // Validação: garantir que caiba horizontalmente
    if (colunaNavio1 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linhaNavio1][colunaNavio1 + i] = 3;
        }
    } else {
        printf("Erro: navio 1 fora dos limites.\n");
        return 1;
    }

    // Navio 2: posição vertical (linha 5 a 7, coluna 4)
    int linhaNavio2 = 5;
    int colunaNavio2 = 4;

    // Validação: garantir que caiba verticalmente
    if (linhaNavio2 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        // Validação: garantir que não haja sobreposição
        int sobreposicao = 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaNavio2 + i][colunaNavio2] != 0) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaNavio2 + i][colunaNavio2] = 3;
            }
        } else {
            printf("Erro: navio 2 sobreposto ao navio 1.\n");
            return 1;
        }

    } else {
        printf("Erro: navio 2 fora dos limites.\n");
        return 1;
    }

    // Impressão do tabuleiro final
    printf("\nTabuleiro Batalha Naval (0 = água, 3 = navio):\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}

