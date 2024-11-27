#include <stdio.h>
#include <string.h>
#include <time.h>

int teste = 0;

// Função para calcular o comprimento da subsequência comum mais longa (LCS)
int lcs_dp(char *X, char *Y) {
    int m = strlen(X);
    int n = strlen(Y);
    int L[m+1][n+1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                L[i][j] = 0;
            } else if (X[i-1] == Y[j-1]) {
                L[i][j] = L[i-1][j-1] + 1;
            } else {
                L[i][j] = (L[i-1][j] > L[i][j-1]) ? L[i-1][j] : L[i][j-1];
            }
        }
    }

    return L[m][n];
}

// Função para ler o arquivo de entrada e passar para a função LCS
void process_file(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char X[teste + 1], Y[teste + 1];

    if (fgets(X, sizeof(X), file) && fgets(Y, sizeof(Y), file)) {
        X[strcspn(X, "\n")] = 0;
        Y[strcspn(Y, "\n")] = 0;

        clock_t start_time = clock();  // Início da medição de tempo

        int result = lcs_dp(X, Y);

        clock_t end_time = clock();  // Fim da medição de tempo
        double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        printf("Comprimento da LCS: %d\n", result);
        printf("Tempo de execução: %.6f segundos\n", execution_time);
    } else {
        printf("Erro ao ler as strings do arquivo.\n");
    }

    fclose(file);
}

int main() {
    char filename[] = "entrada.txt";
    teste = 1000;  // Definir o tamanho máximo das strings
    process_file(filename);
    return 0;
}
