#include "funciones.h"

int analisisSecuencias(int num_secuencias, char **secuencias, char *archivo_salida){
    FILE *archivo2;
    archivo2 = fopen(archivo_salida, "w");
    int etapa, i, j, si, no;
    etapa = i = j = si = no = 0;
    while(i < num_secuencias){
        int largo_elemento = strlen(secuencias[i]);
        j = 0; // Se reinicia j en cada iteracion
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
                etapa = 4; // Se elimina la condicion if para pasar a la etapa 4 directamente
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
        etapa = 0; // Se reinicia etapa en cada iteracion
    }
    fprintf(archivo2, "\nTotal de expresiones que Si son regulares: %i \n", si);
    fprintf(archivo2, "Total de expresiones que No son regulares: %i \n", no);
    fprintf(archivo2, "Total de lineas leidas: %i \n", num_secuencias);
    fclose(archivo2); // Se cierra el archivo al finalizar su uso
    
    // Se retorna la cantidad de expresiones regulares
    return si;
}

int leerArchivo(char *archivo_entrada, char *archivo_salida){
	
	char **secuencias = NULL;
    int num_secuencias = 0;
    
    FILE *archivo = fopen(archivo_entrada, "r");
    // Caso en que no se puede obtener el archivo de entrada
    if (archivo == NULL) {
        printf("Error: no se pudo abrir el archivo.\n");
        return -1;
    }
    
    char linea[101];
    while (fgets(linea, 101, archivo) != NULL) { // Lee cada linea del archivo
        linea[strcspn(linea, "\n")] = '\0'; // Elimina el caracter de la nueva linea
        num_secuencias++; // Incrementa el numero de secuencias
        
        char **nuevo_secuencias = realloc(secuencias, num_secuencias * sizeof(char*)); // Asigna memoria para la nueva secuencia
        // Caso en que no se puede asigar memoria correctamente
        if (nuevo_secuencias == NULL) {
            printf("Error: no se pudo asignar memoria.\n");
            return -1;
        }
        secuencias = nuevo_secuencias;
        
        secuencias[num_secuencias-1] = malloc(strlen(linea) + 1); // Asigna memoria para la nueva secuencia
        // Caso en que no se puede asigar memoria correctamente
        if (secuencias[num_secuencias-1] == NULL) {
            printf("Error: no se pudo asignar memoria.\n");
            return -1;
        }
        strcpy(secuencias[num_secuencias-1], linea); // Copia la secuencia en la nueva memoria
    }
    
    fclose(archivo);
    
    // Si hay 0 secuencias, significa que el archivo esta vacio
    if (num_secuencias == 0) {
        printf("No se encontraron secuencias en el archivo.\n");
        return -1;
    }
    
    // Se llama a la funcion encargada del analisis de las secuencias
    int cantidad_regulares = analisisSecuencias(num_secuencias, secuencias, archivo_salida);
    
    for (int i = 0; i < num_secuencias; i++) { // Se libera la memoria
        free(secuencias[i]);
    }
    free(secuencias);
    
    // Se retorna la cantidad de expresiones regulares
    return cantidad_regulares;
}

