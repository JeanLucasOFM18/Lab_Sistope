#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Entrada: Archivo de entrada (char *)
// Salida: Expresiones almacenadas (Char **)
// Descripcion: Se encarga de obtener las secuencias del archivo de entrada para poder disponerlas a los workers despues
char ** leerArchivo(char *archivo_entrada);

// Entrada: Secuencias (char **)
// Salida: La cantidad de secuencias (int)
// Descripcion: Se encarga de obtener la cantidad de expresiones a analizar
int obtenerLargo(char **secuencia);

// Entrada: Auxiliar (int), Secuencias (char **), tamaño Chunks (int), Buffer (char *) y largo (int)
// Salida: No tiene return
// Descripcion: Internamente le proporciona al buffer las lineas que le corresponde analizar al worker
void obtenerLineas(int aux, char** secuencias, int tamChunks, char* buffer, int largo);