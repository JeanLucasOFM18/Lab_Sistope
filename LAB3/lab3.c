#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include "funciones.h"

int main(int argc, char *argv[]) {
     // Declaracion de variables
    int opt;
    char *verbose = "false";
    char *archivo_entrada = NULL;
    char *archivo_salida = NULL;
    int hebras;
    int chunks;
    
    while ((opt = getopt(argc, argv, "i:o:c:n:b")) != -1) {
        switch (opt) {
            case 'i':
                archivo_entrada = optarg;
                break;
            case 'o':
                archivo_salida = optarg;
                break;
            case 'c':
                chunks = atoi(optarg);
                break;
            case 'n':
                hebras = atoi(optarg);
                break;
            case 'b':
                verbose = "true";
                break;    
            case '?':
                if (optopt == 'i' || optopt == 'o'|| optopt == 'n'|| optopt == 'c'|| optopt == 'b') {
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
    if (archivo_entrada == NULL || archivo_salida == NULL || hebras == 0 || chunks == 0) {
        printf("Datos ingresados de manera erronea.\n");
    }

    FILE *archivo = fopen(archivo_entrada, "r");
    // Caso en que no se puede obtener el archivo de entrada
    if (archivo == NULL) {
        printf("Error: no se pudo abrir el archivo.\n");
        return 1;
    }
    fclose(archivo);

     // Se almacena en la variable global los chunks x hebra
    chunks_global = chunks;
    
    // Se inicia el mutex
    pthread_mutex_init(&lock, NULL);

     // Se crea las hebras y realizan la lectura del archivo y el analisis de la expresion
    pthread_t tids[hebras];
    for(int i=0;i<hebras;i++){
        pthread_create(&tids[i], NULL, leerArchivo, (void*)archivo_entrada);
    }
    for(int i=0;i<hebras;i++){
        pthread_join(tids[i], NULL);
    }

     // En caso de que la cantidad de hebras no sea suficiente para cubrir todo el txt
    while(secuencia_actual < num_secuencias2){
        for(int i=0;i<hebras;i++){
            pthread_create(&tids[i], NULL, leerArchivo, (void*)archivo_entrada);
        }
        for(int i=0;i<hebras;i++){
            pthread_join(tids[i], NULL);
        }
    }

    // Se destruye el mutex
    pthread_mutex_destroy(&lock);

     // Se abre el archivo de salida en modo escritura
    FILE *archivo2 = fopen(archivo_salida, "w");

    for (int i = 0; i < num_secuencias2; i++) {
        if(arreglo_global[i] == 1){
            fprintf(archivo2, "%s si\n", secuenciasGlobal[i]);
        }
        else{
            fprintf(archivo2, "%s no\n", secuenciasGlobal[i]);
        }
    }

    fprintf(archivo2, "\nTotal de expresiones que Si son regulares: %i \n", contador_si);
    fprintf(archivo2, "Total de expresiones que No son regulares: %i \n", contador_no);
    fprintf(archivo2, "Total de lineas leidas: %i \n", contador_si + contador_no);

    if((strcmp(verbose, "true") == 0)){
        printf("\nTotal de expresiones que Si son regulares: %i \n", contador_si);
        printf("Total de expresiones que No son regulares: %i \n", contador_no);
        printf("Total de lineas leidas: %i \n", contador_si + contador_no);
    }

    return 0;
}