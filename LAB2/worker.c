#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "fworker.h"

int main(int argc, char *argv[]) {
    // Obtener los argumentos necesarios
    char *buffer = argv[1];

    char *token = strtok(buffer, ",");
    int i = 0;
    char respuestas[100000] = ""; // Almacenar las respuestas separadas por salto de linea

    while (token != NULL) {
        strcat(respuestas, token);
        i = analisisSecuencias(token);
        if (i == 1) {
            strcat(respuestas, " si\n");
        } else {
            strcat(respuestas, " no\n");
        }
        token = strtok(NULL, ",");
    }

    strcat(respuestas, " ");

    // Eliminar el ultimo elemento, en este caso para dejarlo limpio para el broker evitando que sea el salto de linea
    respuestas[strlen(respuestas) - 1] = '\0';

    // Escribir la lista de respuestas en la salida estándar
    printf("%s", respuestas);

    return 0;
}