#include "funcion.h"

void analisisSecuencias(int num_secuencias, char **secuencias){
	
	int etapa = 1;
	int i = 0;
	int j = 0;
	int si = 0;
	int no = 0;
	
	printf("El largo es: %i \n", num_secuencias);
	
	while(i < num_secuencias){
		int largo_elemento = strlen(secuencias[i]); // Cálculo del largo del primer elemento
		while(j < largo_elemento){
			if(etapa == 1){
				if(secuencias[i][j] == 'G'){
					etapa = 2;
				}
				else{
					etapa = 1;
				}
			}
			else if(etapa == 2){
				if(secuencias[i][j] == 'T'){
					etapa = 3;
				}
				else{
					etapa = 1;
				}
			}
			else if(etapa == 3){
				if(secuencias[i][j] == 'C'){
					etapa = 4;
				}
				else if(secuencias[i][j] == 'T'){
					etapa = 3;
				}
				else{
					etapa = 1;
				}
			}
			else{
				etapa = 4;
			}
			j = j + 1;
		}
		if(etapa == 4){
			printf("La %i : SI \n", i);
			si = si + 1;
		}
		else{
			printf("La %i : NO \n", i);
			no = no + 1;
		}
		i = i + 1;
		j = 0;
		etapa = 1;
	}
	
	printf("Total de expresiones que Si son regulares: %i \n", si);
	printf("Total de expresiones que No son regulares: %i \n", no);
	printf("Total de lineas leidas: %i \n", num_secuencias);
}

void leerArchivo(){
	
	char **secuencias = NULL; // definir la lista de secuencias de ADN como un puntero
    int num_secuencias = 0; // definir el número inicial de secuencias como cero
    
    FILE *archivo = fopen("pruebas.txt", "r"); // abrir el archivo para leer
    if (archivo == NULL) {
        printf("Error: no se pudo abrir el archivo.\n");
    }
    
    char linea[101];
    while (fgets(linea, 101, archivo) != NULL) { // leer cada línea desde el archivo
        linea[strcspn(linea, "\n")] = '\0'; // eliminar el carácter de nueva línea
        num_secuencias++; // incrementar el número de secuencias
        
        char **nuevo_secuencias = realloc(secuencias, num_secuencias * sizeof(char*)); // asignar memoria para la nueva secuencia
        if (nuevo_secuencias == NULL) {
            printf("Error: no se pudo asignar memoria.\n");
        }
        secuencias = nuevo_secuencias;
        
        secuencias[num_secuencias-1] = malloc(strlen(linea) + 1); // asignar memoria para la nueva secuencia
        if (secuencias[num_secuencias-1] == NULL) {
            printf("Error: no se pudo asignar memoria.\n");
        }
        strcpy(secuencias[num_secuencias-1], linea); // copiar la secuencia en la nueva memoria
    }
    
    fclose(archivo);
    
    if (num_secuencias == 0) {
        printf("No se encontraron secuencias en el archivo.\n");
    }
    
	else{
		for (int i = 0; i < num_secuencias; i++) {
			free(secuencias[i]);
		}
		free(secuencias);
	
		analisisSecuencias(num_secuencias, secuencias);
	}
    
}