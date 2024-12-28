#define _DEFAULT_SOURCE
#include <dirent.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "hilos.h"
#include "semaforos.h"
#include "estructuras.h"
#include "explora_dir.h"
#include "operaciones_estructuras.h"
#include "obtener_hashes.h"

void *explora_directorios(void* arg){
    
    char* dir = (char*)arg;

    explora_dir(dir);

    sem_post(&coord_hash);

    pthread_exit(NULL);

}

void *codifica_hashes(void* arg){

    char modo = *(char*)arg;

    sem_wait(&coord_hash);
    sem_post(&coord_hash);

    while (tope_pila!=NULL)
    {
        if(modo == 'e'){

            obtener_hashes_exec(tope_pila->nombre_archivo);

        }else if(modo == 'l'){

            obtener_hashes_libreria(tope_pila->nombre_archivo);
            //printf("HOLAAAA\n");

        }

        sem_wait(&visitados_mutex);
            insertar_visitados(tope_pila->nombre_archivo, hash);   
        sem_post(&visitados_mutex);

        
        //imprimir_lista();

        sem_post(&compara_coord);
        sem_wait(&coord_hash);
        //sem_post(&coord_hash);

        pop();
        
        
        //imprimir_lista();
    }

    pthread_exit(NULL);
}

void *compara_hashes(void* arg){

    sem_wait(&compara_coord);

    while(tope_pila!=NULL){
        sem_wait(&visitados_mutex);
            comparar_hash(cabeza->nombre_archivo, cabeza->valor_hash);
            //imprimir_lista_duplicados();
        sem_post(&visitados_mutex);
        sem_post(&coord_hash);
        sem_wait(&compara_coord);
    }

    
    
    pthread_exit(NULL);
}

void crear_hilos(int cant, char* dir, char hash_modo) {

    //Inicializamos los semaforos que usaremos
    inicializar_semaforos();

    pthread_t hilos[cant];
    pthread_attr_t atributos;
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_DETACHED);

    int i;
    int j;
    int resto;

    if((cant%2)!=0){
        resto = 0;
    }else if((cant%2)==0 && cant!=2){
        resto = 1;
    }

    char* directorio = (char*)malloc(sizeof(NAME_MAX));
    directorio = dir;
    char* modo = malloc(sizeof(char));
    modo = &hash_modo;

    printf("el char es %s\n", modo);

    if(pthread_create(hilos + i, NULL, &explora_directorios, directorio) != 0) {
        perror("Error al crear el hilo");
        exit(1);
    }

    for(i = 0; i < cant - 2; i++) {
        
        if(pthread_create(hilos + i, NULL, &codifica_hashes, modo) != 0) {
            perror("Error al crear el hilo");
            exit(1);
        } 
    }


    if(pthread_create(hilos + i, NULL, &compara_hashes, NULL) != 0) {
        perror("Error al crear el hilo");
        exit(1);

    }

    //pthread_detach(hilos[j]);

    for(j = 0; j < cant; j++) {
        pthread_join(hilos[j], NULL);
    }

   

    sem_destroy(&coord_hash);
    sem_destroy(&compara_coord);
    sem_destroy(&pila_hash_mutex);
    sem_destroy(&visitados_mutex);
} 