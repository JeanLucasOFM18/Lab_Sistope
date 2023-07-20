#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>

extern int arreglo_global[1000000];
extern char* secuenciasGlobal[1000000];
extern int contador_si;
extern int contador_no;
extern int aux;
extern int num_secuencias2;
extern int secuencia_actual;
extern int chunks_global;
extern pthread_mutex_t lock;

// Entrada: Secuencias (char **)
// Salida: No retorna nada
// Descripcion: Se encarga de analizar las expresiones y determinar si son o no regulares
void analisisSecuencias(char **secuencias);

// Entrada: Archivo de entrada (char *)
// Salida: NO retorna nada
// Descripcion: Se encarga de obtener las secuencias del archivo de entrada para despues poder
// realizar el llamado a la funcion de analisis y obtener el numero de expresiones regulares
void * leerArchivo(void * archivo_entrada);