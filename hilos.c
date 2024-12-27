#define _DEFAULT_SOURCE
#include <dirent.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "estructuras.h"
#include "explora_dir.h"

sem_t pila_hash_mutex;
sem_t visitados_mutex;
sem_t coord_hash;
sem_t compara_coord;

void *explora_directorios(void* arg){
    sem_init(&coord_hash, 0, 0);
    char* dir = (char*)arg;
    explora_dir(dir);
    sem_post(&coord_hash);
}

void *codifica_hashes(void* arg){

    char modo = *(char*)arg;

    sem_init(&compara_coord, 0, 0);
    sem_wait(&coord_hash);
        sem_init(&pila_hash_mutex, 0, 1);
        sem_init(&visitados_mutex, 0, 1);

        while (tope_pila!=NULL)
        {
            if(modo == 'e'){

                obtener_hashes_exec(tope_pila->nombre_archivo);

                sem_wait(&pila_hash_mutex);
                    pop();
                sem_post(&pila_hash_mutex);    
            }else 
                if(modo == 'l'){
                obtener_hashes_libreria(tope_pila->nombre_archivo);
                pop();
            }
            
            tope_pila = tope_pila->siguiente;
        }

}

void *compara_hashes(void* arg){

    sem_wait(&compara_coord);
    sem_wait(&visitados_mutex);
        comparar_hash(cabeza->nombre_archivo, cabeza->valor_hash);
    sem_post(&visitados_mutex);

}

void crear_hilos(int cant, char* dir, char hash_modo) {
    pthread_t hilos[cant];
    int i;
    int resto;

    if((cant%2)!=0){
        resto = 0;
    }else if((cant%2)==0 && cant!=2){
        resto = 1;
    }

    char* directorio = (char*)malloc(sizeof(NAME_MAX));
    directorio = dir;
    char* modo = malloc(sizeof(char));
    modo = hash_modo;

    for(i = 0; i < (cant - resto)/2; i++) {
        
        // REVISAR
        // Algo me dice que la logica de aqui no esta aplicada del todo bien
        // fijate que puedes crear un hilo, por ejemplo, hilo 1 para explorar directorios e hilo 1 para codificar hash
        // No se si es que, al crear el explorar directorios, da fallos cuando intente crear codificar hash y por eso esta asi
        if(pthread_create(hilos + i, NULL, &explora_directorios, directorio) != 0) {
            perror("Error al crear el hilo");
            exit(1);
        }
        if(pthread_create(hilos + i, NULL, &codifica_hashes, modo) != 0) {
            perror("Error al crear el hilo");
            exit(1);
        } 
    }

    if(pthread_create(hilos + i, NULL, &compara_hashes, NULL) != 0) {
        perror("Error al crear el hilo");
        exit(1);

    }

    for(int i = 0; i < cant; i++) {
        pthread_join(hilos[i], NULL);
    }
} 