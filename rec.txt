#include <stdio.h>
#include <string.h>
#include <time.h>

int lcs_recursive(char *X, char *Y, int m, int n) {
    if (m == 0 || n == 0) {
        return 0;
    }
    if (X[m - 1] == Y[n - 1]) {
        return 1 + lcs_recursive(X, Y, m - 1, n - 1);
    } else {
        int exclude_last_X = lcs_recursive(X, Y, m - 1, n);
        int exclude_last_Y = lcs_recursive(X, Y, m, n - 1);
        return (exclude_last_X > exclude_last_Y) ? exclude_last_X : exclude_last_Y;
    }
}

void process_file_recursive(char *filename, int tamanho_txt) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char X[tamanho_txt + 1], Y[tamanho_txt + 1];

    if (fgets(X, sizeof(X), file) && fgets(Y, sizeof(Y), file)) {
        X[strcspn(X, "\n")] = 0;
        Y[strcspn(Y, "\n")] = 0;

        int m = strlen(X);
        int n = strlen(Y);

        // Início da medição de tempo
        clock_t start_time = clock();

        int result = lcs_recursive(X, Y, m, n);

        // Fim da medição de tempo
        clock_t end_time = clock();

        double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        printf("Comprimento da LCS (recursivo): %d\n", result);
        printf("Tempo de execução: %.6f segundos\n", execution_time);
    } else {
        printf("Erro ao ler as strings do arquivo.\n");
    }

    fclose(file);
}

int main() {
    char filename[] = "entrada.txt";
    int tamanho_txt = 50;
    process_file_recursive(filename, tamanho_txt);
    return 0;
}
