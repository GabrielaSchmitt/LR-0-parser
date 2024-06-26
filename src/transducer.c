#include "transducer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isLowerCaseLetter(char c) {
    return (c >= 'a' && c <= 'z');
}

char *transducer() {
    char input[100];
    char *output = (char *)malloc(100 * sizeof(char));
    if (output == NULL) {
        printf("Erro de alocação de memória\n");
        exit(1);
    }

    int i = 0;
    int j = 0;

    printf("Digite a cadeia de entrada: ");
    fgets(input, sizeof(input), stdin);

    while (input[i] != '\0' && input[i] != '\n') {
        if (isspace(input[i])) {
            i++;
            continue;
        } else if (isLowerCaseLetter(input[i])) {
            output[j++] = 'x';
            while (isLowerCaseLetter(input[i])) {
                i++;
            }
        } else if (input[i] == '+' || input[i] == '(' || input[i] == ')') {
            output[j++] = input[i++];
        } else {
            printf("<REJEITAR>\n");
            exit(1);
        }
    }

    output[j] = '\0';
    printf("Saida: %s\n", output);

    output[j] = '$';
    output[j + 1] = '\0';

    return output;
}
