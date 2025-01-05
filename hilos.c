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

void *explora_directorios(void* arg){// DE MOMENTO SIN PROBLEMAS
    
    char* dir = (char*)arg;

    explora_dir(dir);

    sem_post(&coord_hash); //Pasamos el control al codificador de hashes

    pthread_exit(NULL);

}

void *codifica_hashes(void* arg){// EN CONSTRUCCION

    char modo = *(char*)arg;

    sem_wait(&coord_hash); //Esperamos por el explorador de directorios
    sem_post(&coord_hash); //Liberamos todos los hilos que estaban en espera

    while (tope_pila!=NULL)
    {
        if(modo == 'e'){

            obtener_hashes_exec(tope_pila->nombre_archivo);

        }else if(modo == 'l'){

            obtener_hashes_libreria(tope_pila->nombre_archivo);
        }

        sem_wait(&visitados_mutex); //Seccion critica lista de visitados
            insertar_visitados(tope_pila->nombre_archivo, hash);   
        sem_post(&visitados_mutex);

        
        //imprimir_lista();

        sem_post(&compara_coord); //Le pasamos el control al hilo del comparador
        sem_wait(&coord_hash); //Esperamos por el comparador
        //sem_post(&coord_hash);

        pop();
        
        
        //imprimir_lista();
    }

    pthread_exit(NULL);
}

void *compara_hashes(void* arg){// EN CONSTRUCCION (PRIORIDAD)

    sem_wait(&compara_coord);//Esperamos por el codificador de hashes

    while(tope_pila!=NULL){
        sem_wait(&visitados_mutex);//Seccion critica, recorremos la lista de visitados
            comparar_hash(cabeza->nombre_archivo, cabeza->valor_hash);
            //imprimir_lista_duplicados();
        sem_post(&visitados_mutex);
        sem_post(&coord_hash);//Liberamos al codificador de hashes
        sem_wait(&compara_coord);//Esperamos por el codificador de hashes
    }

    
    
    pthread_exit(NULL);
}

void crear_hilos(int cant, char* dir, char hash_modo) {

    //Inicializamos los semaforos que usaremos
    inicializar_semaforos();

    //Arreglo de hilos
    pthread_t hilos[cant];
    //Atributos para colocar detached al hilo del comparador (SOLO PARA PRUEBAS)
    pthread_attr_t atributos;
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_DETACHED);

    int i;
    int resto;

//Logica para repartir los hilos (EN ESPERA A MEJORAS)
/*
    if((cant%2)!=0){
        resto = 0;
    }else if((cant%2)==0 && cant!=2){
        resto = 1;
    }
    */

//Apuntadores para poder pasarle los argumentos a los hilos
    char* directorio = (char*)malloc(sizeof(NAME_MAX));
    directorio = dir;
    char* modo = malloc(sizeof(char));
    modo = &hash_modo;

    //Creamos el hilo de explorar directorio (DE MOMENTO SERÁ ÚNICO)
    if(pthread_create(hilos + i, NULL, &explora_directorios, directorio) != 0) {
        perror("Error al crear el hilo");
        exit(1);
    }

    //Creamos los hilos de codificar los hashes (LA LOGICA ES QUE TENGA TODOS LOS HILOS MENOS 2)
    for(i = 0; i < cant - 2; i++) {
        
        if(pthread_create(hilos + i, NULL, &codifica_hashes, modo) != 0) {
            perror("Error al crear el hilo");
            exit(1);
        } 
    }

    //Creamos el hilo para el comparador
    if(pthread_create(hilos + i, NULL, &compara_hashes, NULL) != 0) {
        perror("Error al crear el hilo");
        exit(1);

    }

    //Join de los hilos creados
    for(int i = 0; i < cant; i++) {
        pthread_join(hilos[i], NULL);
    }

    //Destruimos los semaforos
    sem_destroy(&coord_hash);
    sem_destroy(&compara_coord);
    sem_destroy(&pila_hash_mutex);
    sem_destroy(&visitados_mutex);
} 