#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Entrada: Numero de secuencias (int), secuencias (char **) y el archivo de salida (char *)
// Salida: La cantidad de expresiones regulares encontradas (int)
// Descripcion: Se encarga de analizar las expresiones y determinar si son o no regulares
// Ademas de retornar la cantidad de expresiones que SI son regulares
int analisisSecuencias(int num_secuencias, char **secuencias, char *archivo_salida);

// Entrada: Archivo de entrada (char *) y el archivo de salida (char *)
// Salida: La cantidad de expresiones regulares encontradas (int)
// Descripcion: Se encarga de obtener las secuencias del archivo de entrada para despues poder
// realizar el llamado a la funcion de analisis y obtener el numero de expresiones regulares
int leerArchivo(char *archivo_entrada, char *archivo_salida);
