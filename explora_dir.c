#define _DEFAULT_SOURCE
#include <dirent.h>
#include <stdio.h>
#include "estructuras.h"

struct Nodo* tope = NULL;

void explora_dir(const char *directorio){

    DIR *carpeta;
    struct dirent *entradaDir;

    carpeta = opendir(directorio);
    if(carpeta == NULL){
        printf("Error al intentar abrir la carpeta");
        exit (0);
    }

    while((entradaDir = readdir(carpeta))!=NULL){
        if(entradaDir->d_type == DT_REG){
            push(entradaDir->d_name, tope);
        }else if(entradaDir->d_type == DT_DIR){
            explora_dir(entradaDir->d_name);
        }
    }
    closedir(carpeta);
}

int main(){
    
    char* dir = "/home/ronald/Desktop/ProofCode";
    explora_dir(dir);

    struct Nodo *impreso = tope; 
    while(impreso!=NULL){

        printf("%s\n", impreso->nombre_archivo);
        impreso = impreso->siguiente;
    }
    return 0;
}