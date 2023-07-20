#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int opt;
    char *verbose = "false";
    char *archivo_entrada = NULL;
    char *archivo_salida = NULL;
    int workers;
    int chunks;
    
    while ((opt = getopt(argc, argv, "i:o:n:c:b")) != -1) {
        switch (opt) {
            case 'i':
                archivo_entrada = optarg;
                break;
            case 'o':
                archivo_salida = optarg;
                break;
            case 'n':
                workers = atoi(optarg);
                break;
            case 'c':
                chunks = atoi(optarg);
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
    if (archivo_entrada == NULL || archivo_salida == NULL || workers == 0 || chunks == 0) {
        printf("Datos ingresados de manera errònea.\n");
        return 1;
    }

    char numWorkers[20];
    char tamChunks[20];
    sprintf(numWorkers, "%d", workers);
    sprintf(tamChunks, "%d", chunks);

    // Crear el proceso "broker" utilizando fork()
    pid_t pid = fork();
    
    if (pid == -1) {
        // Error al crear el proceso hijo
        printf("Error al crear el proceso broker.\n");
        return 1;
    } else if (pid == 0) {
        // Proceso hijo (broker)
        
        // Ejecutar el proceso "broker" utilizando exec()
        char *broker_args[] = {"./broker", archivo_entrada, archivo_salida, numWorkers, tamChunks, verbose, NULL};
        execv(broker_args[0], broker_args);

        
        // En caso de que exec() falle, se imprimirá un mensaje de error
        printf("Error al ejecutar el proceso broker.\n");
        return 1;
    } else {
        // Proceso padre
        
        // Esperar a que el proceso hijo (broker) termine
        int status;
        waitpid(pid, &status, 0);
        
        // Verificar el estado de salida del proceso hijo
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            if (exit_status == 0) {
                printf("Proceso broker finalizado correctamente.\n");
            } else {
                printf("El proceso broker finalizó con un error: %d\n", exit_status);
            }
        } else {
            printf("El proceso broker finalizó de forma anormal.\n");
        }
    }

    return 0;
}