#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "fbroker.h"

int main(int argc, char *argv[]) {
    // Obtener los argumentos del proceso padre
    char *archivo_entrada = argv[1];
    char *archivo_salida = argv[2];
    int numWorkers = atoi(argv[3]); // Convertir el argumento a entero
    int tamChunks = atoi(argv[4]); // Convertir el argumento a entero
    char *verbose = argv[5];
    FILE *archivo = fopen(archivo_entrada, "r");
    FILE *archivo2 = fopen(archivo_salida, "w");
    char **secuencias = leerArchivo(archivo_entrada);
    int largo = obtenerLargo(secuencias);
    int aux = 0;
    int contador_si = 0;
    int contador_no = 0;

    // En caso de que los chunks excedan el tamaño del txt
    if(tamChunks > largo){
        return 1;
    }  

    // En caso de necesitar repetir la ejecuciòn de workers para recorrer la totalidad de lineas
    int total = numWorkers * tamChunks;
    int vecesARepetir = 1;
    while(total < largo){
        total = total * 2;
        vecesARepetir = vecesARepetir + 1;
    }   

    int veces = 0;
    while (veces < vecesARepetir){
        // Crear los workers y establecer la comunicación mediante pipes
        for (int i = 0; i < numWorkers; i++) {
            if(aux >= largo){
                break;
            }
            int pipe_fd[2];
            if (pipe(pipe_fd) == -1) {
                printf("Error al crear el pipe\n");
                return 1;
            }

            // Crear el proceso worker utilizando fork()
            pid_t pid = fork();

            if (pid == -1) {
                // Error al crear el proceso hijo
                printf("Error al crear el proceso worker %d\n", i);
                return 1;
            } else if (pid == 0) {
                // Proceso hijo (worker)

                // Cerrar el extremo de lectura del pipe en el proceso hijo
                close(pipe_fd[0]);

                // Redirigir la salida estándar del worker al extremo de escritura del pipe
                dup2(pipe_fd[1], STDOUT_FILENO);

                int startLine = aux;
                char buffer[1000000] = ""; // Definimos un buffer para almacenar las líneas concatenadas
                obtenerLineas(startLine, secuencias, tamChunks, buffer, largo);

                // Ejecutar el proceso "worker" utilizando exec()
                char worker_args[] = "./worker";
                char *worker_argv[] = {worker_args, buffer, NULL};
                execv(worker_args, worker_argv);

                // En caso de que exec() falle, se imprimirá un mensaje de error
                printf("Error al ejecutar el proceso worker %d\n", i);
                return 1;
            } else {
                // PROCESO PADRE

                /// Cerrar el extremo de escritura del pipe en el proceso padre después de escribir los datos
                close(pipe_fd[1]);

                // Leer la respuesta del worker desde el pipe
                char respuestas[100000];
                int bytes_read = read(pipe_fd[0], respuestas, sizeof(respuestas));

                // Cerrar el extremo de lectura del pipe en el proceso padre después de leer los datos
                close(pipe_fd[0]);

                if (bytes_read == -1) {
                    printf("Error al leer la respuesta del worker\n");
                    return 1;
                }
                
                int starLine = aux;

                char* token;
                // Obtener cada frase usando strtok
                token = strtok(respuestas, "\n");
                while (token != NULL && starLine < largo) {
                    fprintf(archivo2, "%s \n", token);
                    // Buscar "si" después de la frase
                    char* siguiente_si = strstr(token, "si");
                    if (siguiente_si != NULL) {
                        contador_si++;
                    }

                    // Buscar "no" después de la frase
                    char* siguiente_no = strstr(token, "no");
                    if (siguiente_no != NULL) {
                        contador_no++;
                    }

                    // Obtener el siguiente token como la siguiente frase
                    token = strtok(NULL, "\n");
                    starLine = starLine + 1;
                }

                int status;
                waitpid(pid, &status, 0);
            }

            aux += tamChunks;
        }
        veces = veces + 1;
    }

    // Esperar a que todos los workers terminen
    for (int i = 0; i < numWorkers; i++) {
        int status;
        wait(&status);
    }

    // Printeo en pantalla si se pone la bandera -b
    if(aux >= largo){
        if (strcmp(verbose, "true") == 0) {
            printf("Total de expresiones que SI son regulares: %i\n", contador_si);
            printf("Total de expresiones que NO son regulares: %i\n", contador_no);
            printf("Total de lineas leidas: %i\n", contador_si + contador_no);
        }
        fprintf(archivo2, "\nTotal de expresiones que SI son regulares: %i\n", contador_si);
        fprintf(archivo2, "Total de expresiones que NO son regulares: %i\n", contador_no);
        fprintf(archivo2, "Total de lineas leidas: %i\n", contador_si + contador_no);
        fclose(archivo2);
        fclose(archivo);
    }

    return 0;
}