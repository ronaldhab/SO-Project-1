#define _DEFAULT_SOURCE
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*Contador provisional*/
int count = 0;

/*Funcion encargada de explorar los directorios y crear la pila de archivos "Por visitar"*/
int explora_dir(const char *directorio){

    DIR *carpeta;
    struct dirent *entrada_dir;

    carpeta = opendir(directorio);
    if(carpeta == NULL){
        return 1;
    }

    while((entrada_dir = readdir(carpeta))!=NULL){
        if(entrada_dir->d_type == DT_REG){

            /*Creamos el nombre del archivo concatenado con su ruta*/
            char nombre_archivo[NAME_MAX] = { 0 };
            strcat(nombre_archivo, directorio);
            strcat(nombre_archivo, "/");
            strcat(nombre_archivo, entrada_dir->d_name);

            /*Introducimos el nombre del archivo en la pila de "Por visitar"
            Al ser un recurso compartido debe manipularse dentro de una
            seccion critica*/
            //sem_wait(&pila_hash_mutex);
                if(!esta_contenido(nombre_archivo)){
                    push(nombre_archivo);
                }
            //sem_post(&pila_hash_mutex);
            
            count++;
            
        }else if(entrada_dir->d_type == DT_DIR && strcmp(entrada_dir->d_name, ".") != 0 && strcmp(entrada_dir->d_name, "..") != 0){

            /*Creamos el path del sub-directorio*/
            char path[NAME_MAX] = { 0 };
            
            strcat(path, directorio);
            strcat(path, "/");
            strcat(path, entrada_dir->d_name);

            explora_dir(path);
        }
    }
    closedir(carpeta);
    return 0;
}

void test_explora_dir(void) {

    // Caso valido
    CU_ASSERT(explora_dir("ProofCode") == 0);

    // Caso invalido
    CU_ASSERT(explora_dir("non_existing_directory") == 1);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Explorar Directorio Suite", 0, 0);
    CU_add_test(suite, "test_explora_dir", test_explora_dir);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}