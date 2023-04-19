#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void analisisSecuencias(int num_secuencias, char **secuencias, char *archivo_salida){
    FILE *archivo2;
    archivo2 = fopen(archivo_salida, "w");
    int etapa, i, j, si, no;
    etapa = i = j = si = no = 0;
    while(i < num_secuencias){
        int largo_elemento = strlen(secuencias[i]);
        j = 0; // se reinicia j en cada iteración
        while(j < largo_elemento){
            if(etapa == 0){
                if(secuencias[i][j] == 'G'){
                    etapa = 1;
                }
                else{
                    etapa = 0;
                }
            }
            else if(etapa == 1){
                if(secuencias[i][j] == 'T'){
                    etapa = 2;
                }
                else{
                    etapa = 0;
                }
            }
            else if(etapa == 2){
                if(secuencias[i][j] == 'C'){
                    etapa = 3;
                }
                else if(secuencias[i][j] == 'T'){
                    etapa = 2;
                }
                else{
                    etapa = 0;
                }
            }
            else if(etapa == 3){
                etapa = 4; // se eliminó la condición if para pasar a la etapa 4 directamente
            }
            j = j + 1;
        }
        if(etapa == 4){
            fprintf(archivo2, "%s si\n",secuencias[i]);
            si = si + 1;
        }
        else{
            fprintf(archivo2, "%s no\n",secuencias[i]);
            no = no + 1;
        }
        i = i + 1;
        etapa = 0; // se reinicia etapa en cada iteración
    }
    fprintf(archivo2, "Total de expresiones que Si son regulares: %i \n", si);
    fprintf(archivo2, "Total de expresiones que No son regulares: %i \n", no);
    fprintf(archivo2, "Total de lineas leidas: %i \n", num_secuencias);
    fclose(archivo2); // se cierra el archivo al finalizar su uso
}

void leerArchivo(char *archivo_entrada, char *archivo_salida){
	
	char **secuencias = NULL; // definir la lista de secuencias de ADN como un puntero
    int num_secuencias = 0; // definir el número inicial de secuencias como cero
    
    FILE *archivo = fopen(archivo_entrada, "r"); // abrir el archivo para leer
    if (archivo == NULL) {
        printf("Error: no se pudo abrir el archivo.\n");
        return;
    }
    
    char linea[101];
    while (fgets(linea, 101, archivo) != NULL) { // leer cada línea desde el archivo
        linea[strcspn(linea, "\n")] = '\0'; // eliminar el carácter de nueva línea
        num_secuencias++; // incrementar el número de secuencias
        
        char **nuevo_secuencias = realloc(secuencias, num_secuencias * sizeof(char*)); // asignar memoria para la nueva secuencia
        if (nuevo_secuencias == NULL) {
            printf("Error: no se pudo asignar memoria.\n");
            return;
        }
        secuencias = nuevo_secuencias;
        
        secuencias[num_secuencias-1] = malloc(strlen(linea) + 1); // asignar memoria para la nueva secuencia
        if (secuencias[num_secuencias-1] == NULL) {
            printf("Error: no se pudo asignar memoria.\n");
            return;
        }
        strcpy(secuencias[num_secuencias-1], linea); // copiar la secuencia en la nueva memoria
    }
    
    fclose(archivo);
    
    if (num_secuencias == 0) {
        printf("No se encontraron secuencias en el archivo.\n");
        return;
    }
    
    analisisSecuencias(num_secuencias, secuencias, archivo_salida);
    
    for (int i = 0; i < num_secuencias; i++) {
        free(secuencias[i]);
    }
    free(secuencias);
}

int main(int argc, char *argv[]) {
	
	if (argc != 3) {
        printf("Debe ingresar el nombre del archivo de texto y el nombre del archivo de salida como argumentos.\n");
        return 1;
    }
	
	char *archivo_salida = argv[2];
	
	leerArchivo(argv[1], archivo_salida);
	
    return 0;
}
