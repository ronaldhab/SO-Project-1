#define _DEFAULT_SOURCE
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "operaciones.h"

int count = 0;

void explora_dir(const char *directorio){

    DIR *carpeta;
    struct dirent *entrada_dir;

    printf("Reading files in: %s\n", directorio);

    carpeta = opendir(directorio);
    if(carpeta == NULL){
        printf("Error al intentar abrir la carpeta\n");
        return;
    }

    while((entrada_dir = readdir(carpeta))!=NULL){
        if(entrada_dir->d_type == DT_REG){

            //printf("El nombre del archivo es: %s\n", entrada_dir->d_name);
            char nombre_archivo[NAME_MAX] = { 0 };
            strcat(nombre_archivo, directorio);
            strcat(nombre_archivo, "/");
            strcat(nombre_archivo, entrada_dir->d_name);

            push(nombre_archivo);
            count++;
            
        }else if(entrada_dir->d_type == DT_DIR && strcmp(entrada_dir->d_name, ".") != 0 && strcmp(entrada_dir->d_name, "..") != 0){

            char path[100] = { 0 };
            
            strcat(path, directorio);
            strcat(path, "/");
            strcat(path, entrada_dir->d_name);

            explora_dir(path);
        }
    }
    closedir(carpeta);
}

int main(){
    
    char* dir = "/home/ronald/Desktop/ProofCode";
    explora_dir(dir);

    imprimir_pila();
    liberar_pila();

    insertar_visitados("avecxesdario", "123456789112345678911234567891234");

    return 0;
}