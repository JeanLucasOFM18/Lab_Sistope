#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analisisSecuencias(int num_secuencias, char **secuencias, char *archivo_salida){
	
	FILE *archivo2;
	archivo2 = fopen(archivo_salida, "w");
	int etapa = 1;
	int i = 0;
	int j = 0;
	int si = 0;
	int no = 0;
		
	printf("%s", secuencias[0]);
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
			fprintf(archivo2, "%s si\n",secuencias[i]);
			si = si + 1;
		}
		else{
			fprintf(archivo2, "%s no\n",secuencias[i]);
			no = no + 1;
		}
		i = i + 1;
		j = 0;
		etapa = 1;
	}
	
	fprintf(archivo2, "Total de expresiones que Si son regulares: %i \n", si);
	fprintf(archivo2, "Total de expresiones que No son regulares: %i \n", no);
	fprintf(archivo2, "Total de lineas leidas: %i \n", num_secuencias);
}

void leerArchivo(char *archivo_entrada, char *archivo_salida){
	
	char **secuencias = NULL; // definir la lista de secuencias de ADN como un puntero
    int num_secuencias = 0; // definir el número inicial de secuencias como cero
    
    FILE *archivo = fopen(archivo_entrada, "r"); // abrir el archivo para leer
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
	
		analisisSecuencias(num_secuencias, secuencias, archivo_salida);
	}
    
}

int main(int argc, char *argv[]) {
	
	if (argc != 3) {
        printf("Debe ingresar el nombre del archivo de texto como argumento.\n");
        return 1;
    }
	
	leerArchivo(argv[1], argv[2]);
	
    return 0;
}