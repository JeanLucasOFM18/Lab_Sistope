#include "fworker.h"

int analisisSecuencias(char *linea){

    int etapa, i, j;
    i = j = 0;
    etapa = 1;
    while(i == 0){
        int largo_elemento = strlen(linea);
        while(j < largo_elemento){
            if(etapa == 1){
                if(linea[j] == 'G'){
                    etapa = 2;
                }
                else{
                    etapa = 1;
                }
            }
            else if(etapa == 2){
                if(linea[j] == 'T'){
                    etapa = 3;
                }
                else if(linea[j] == 'G'){
                    etapa = 2;
                }
                else{
                    etapa = 1;
                }
            }
            else if(etapa == 3){
                if(linea[j] == 'C'){
                    etapa = 4;
                }
                else if(linea[j] == 'T'){
                    etapa = 3;
                }
                else if(linea[j] == 'G'){
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
            return 1;
        }
        else{
            return 0;
        }
        i = 1;
    }
    
    return 0;
}