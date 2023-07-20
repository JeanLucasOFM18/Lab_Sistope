#include "fbroker.h"

char ** leerArchivo(char *archivo_entrada){
	
	char **secuencias = NULL;
    int num_secuencias = 0;
    
    FILE *archivo = fopen(archivo_entrada, "r");
    
    char linea[101];
    while (fgets(linea, 101, archivo) != NULL) { // Lee cada linea del archivo
        linea[strcspn(linea, "\n")] = '\0'; // Elimina el caracter de la nueva linea
        num_secuencias++; // Incrementa el numero de secuencias
        
        char **nuevo_secuencias = realloc(secuencias, num_secuencias * sizeof(char*)); // Asigna memoria para la nueva secuencia
        // Caso en que no se puede asigar memoria correctamente
        if (nuevo_secuencias == NULL) {
            printf("Error: no se pudo asignar memoria.\n");
        }
        secuencias = nuevo_secuencias;
        
        secuencias[num_secuencias-1] = malloc(strlen(linea) + 1); // Asigna memoria para la nueva secuencia
        // Caso en que no se puede asigar memoria correctamente
        if (secuencias[num_secuencias-1] == NULL) {
            printf("Error: no se pudo asignar memoria.\n");
        }
        strcpy(secuencias[num_secuencias-1], linea); // Copia la secuencia en la nueva memoria
    }
    
    secuencias[num_secuencias] = NULL; // Establece el último elemento como NULL

    fclose(archivo);

    return secuencias;
}

int obtenerLargo(char **secuencia) {
    int largo = 0;

    while (secuencia[largo] != NULL) {
        largo++;
    }

    return largo;
}

void obtenerLineas(int aux, char** secuencias, int tamChunks, char* buffer, int largo) {

    // Se obtiene las lineas para el worker
    int j = 0;
    while (j < tamChunks && aux < largo) {
        if (j > 0) {
            strcat(buffer, ",");
        }
        strcat(buffer, secuencias[aux]);
        aux++;
        j++;
    }

    if(j == 1){
        strcat(buffer, ",");
    }

}