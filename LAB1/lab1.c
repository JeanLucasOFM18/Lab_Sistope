#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include "funciones.h"

int main(int argc, char *argv[]) {
    int opt;
    bool verbose = false;
    char *archivo_entrada = NULL;
    char *archivo_salida = NULL;
    
    while ((opt = getopt(argc, argv, "i:o:b")) != -1) {
        switch (opt) {
            case 'i':
                archivo_entrada = optarg;
                break;
            case 'o':
                archivo_salida = optarg;
                break;
            case 'b':
                verbose = true;
                break;    
            case '?':
                if (optopt == 'i' || optopt == 'o') {
                    printf("Opcion -%c requiere un argumento.\n", optopt);
                } else if (isprint(optopt)) {
                    printf("Opcion desconocida '-%c'.\n", optopt);
                } else {
                    printf("Caracter de opcion desconocida '\\x%x'.\n", optopt);
                }
                return 1;
            default:
                abort();
        }
    }

    // Si no se ingresa archivo de entrada y/o salida
    if (archivo_entrada == NULL || archivo_salida == NULL) {
        printf("Debe ingresar el nombre del archivo de entrada y de salida.\n");
        return 1;
    }

    // Se llama a la funcion encargada de obtener la cantidad de expresiones regulares
    int cantidad_regulares = leerArchivo(archivo_entrada, archivo_salida);
    
    // Se imprime la cantidad de expresiones regulares encontradas
    if (verbose) {
        printf("Cantidad de expresiones regulares encontradas: %i: ", cantidad_regulares);
    }
    
    return 0;
}
