#include "funciones.h"

// Declaracion de variables globales
int arreglo_global[1000000];
char* secuenciasGlobal[1000000];
int contador_si = 0;
int contador_no = 0;
int aux = 0;
int num_secuencias2 = 0;
int secuencia_actual = 0;
int chunks_global = 0;
pthread_mutex_t lock;

char* strdup(const char* str);

void analisisSecuencias(char **secuencias){

    int etapa, j, k;
    j = 0;
    etapa = 1;
    k = 0;
    // Se restringe la entrada, ya que, se modifica variables globales
    pthread_mutex_lock(&lock);
    while(secuencia_actual < num_secuencias2 && k < chunks_global){
        int largo_elemento = strlen(secuencias[secuencia_actual]);
        j = 0; // Se reinicia j en cada iteracion
        while(j < largo_elemento){
            if(etapa == 1){
                if(secuencias[secuencia_actual][j] == 'G'){
                    etapa = 2;
                }
                else{
                    etapa = 1;
                }
            }
            else if(etapa == 2){
                if(secuencias[secuencia_actual][j] == 'T'){
                    etapa = 3;
                }
                else if(secuencias[secuencia_actual][j] == 'G'){
                    etapa = 2;
                }
                else{
                    etapa = 1;
                }
            }
            else if(etapa == 3){
                if(secuencias[secuencia_actual][j] == 'C'){
                    etapa = 4;
                }
                else if(secuencias[secuencia_actual][j] == 'T'){
                    etapa = 3;
                }
                else if(secuencias[secuencia_actual][j] == 'G'){
                    etapa = 2;
                }
                else{
                    etapa = 1;
                }
            }
            else if(etapa == 4){
                j = largo_elemento;
            }
            j = j + 1;
        }
        if(etapa == 4){
            arreglo_global[secuencia_actual] = 1;
            contador_si = contador_si + 1;
        }
        else{
            arreglo_global[secuencia_actual] = 0;
            contador_no = contador_no + 1;
        }
        secuencia_actual = secuencia_actual + 1;
        k = k + 1;
        etapa = 1; // Se reinicia etapa en cada iteracion
    }
    // Se permite volver a ingresar a esta seccion del codigo
    pthread_mutex_unlock(&lock);
    
}

void * leerArchivo(void * archivo_entrada){
	
	char **secuencias = NULL;
    int num_secuencias = 0;
    
    FILE *archivo = fopen(archivo_entrada, "r");
    // Caso en que no se puede obtener el archivo de entrada
    if (archivo == NULL) {
        printf("Error: no se pudo abrir el archivo.\n");
        return NULL;
    }
    
    char linea[101];
    while (fgets(linea, 101, archivo) != NULL) { // Lee cada linea del archivo
        linea[strcspn(linea, "\n")] = '\0'; // Elimina el caracter de la nueva linea
        num_secuencias++; // Incrementa el numero de secuencias
        
        char **nuevo_secuencias = realloc(secuencias, num_secuencias * sizeof(char*)); // Asigna memoria para la nueva secuencia
        // Caso en que no se puede asigar memoria correctamente
        if (nuevo_secuencias == NULL) {
            printf("Error: no se pudo asignar memoria.\n");
            return NULL;
        }
        secuencias = nuevo_secuencias;
        
        secuencias[num_secuencias-1] = malloc(strlen(linea) + 1); // Asigna memoria para la nueva secuencia
        // Caso en que no se puede asigar memoria correctamente
        if (secuencias[num_secuencias-1] == NULL) {
            printf("Error: no se pudo asignar memoria.\n");
            return NULL;
        }
        strcpy(secuencias[num_secuencias-1], linea); // Copia la secuencia en la nueva memoria
    }
    
    fclose(archivo);
    
    // Si hay 0 secuencias, significa que el archivo esta vacio
    if (num_secuencias == 0) {
        printf("No se encontraron secuencias en el archivo.\n");
        return NULL;
    }
    
    // Se restringe la entrada, ya que, se modifica variables globales
    pthread_mutex_lock(&lock);
    if (aux == 0) {
        aux = aux + 1;
        num_secuencias2 = num_secuencias;
        for (int i = 0; i < num_secuencias2; i++) {
            secuenciasGlobal[i] = strdup(secuencias[i]);
        }
    }
    // Se permite volver a ingresar a esta seccion del codigo
    pthread_mutex_unlock(&lock);

    // Se llama a la funcion encargada del analisis de las secuencias
    analisisSecuencias(secuencias);
    
    for (int i = 0; i < num_secuencias; i++) { // Se libera la memoria
        free(secuencias[i]);
    }
    free(secuencias);

    return NULL;
}