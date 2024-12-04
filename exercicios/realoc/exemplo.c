#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = malloc(3 * sizeof(int));
    if (!arr) {
        perror("malloc failed");
        return 1;
    }

    // Inicializa os valores
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    for (int i = 0; i < 3; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    // Redimensiona para 5 inteiros
    arr = realloc(arr, 5 * sizeof(int));
    if (!arr) {
        perror("realloc failed");
        return 1;
    }

    // Preenche os novos espaços
    arr[3] = 40;
    arr[4] = 50;

    // Imprime os valores
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr); // Libera a memória alocada
    return 0;
}
