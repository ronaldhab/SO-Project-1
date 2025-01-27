#define _DEFAULT_SOURCE
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "hilos.h"
#include "semaforos.h"
#include "estructuras.h"
#include "operaciones_estructuras.h"
#include "obtener_hashes.h"

int cantidad_total = 0; //Variable global para manejar la cantidad de archivos

pthread_mutex_t mutex_list;

void *codifica_hashes(void* arg){

    char modo = *(char*)arg;

    while (tope_pila!=NULL)
    {
        //Sección crítica para manipular la pila de archivos
        sem_wait(&hash_mutex);    
            if(tope_pila!=NULL){
                if(modo == 'e'){

                    //Obtenemos el hash del archivo en moodo ejecutable
                    obtener_hashes_exec(tope_pila->nombre_archivo);

                }else if(modo == 'l'){

                    //Obtenemos el hash del archivo en moodo libreria
                    obtener_hashes_libreria(tope_pila->nombre_archivo);
                }

                //Insertamos el nombre y el hash del archivo en la lista de visitados 
                insertar_visitados(tope_pila->nombre_archivo, hash);   

                sem_post(&compara_coord);//Le pasamos el control al hilo del comparador
                sem_wait(&coord_hash);//Esperamos por el comparador

                pop();//Sacamos el nombre del archivo de la pila
            }

        sem_post(&hash_mutex);
    }
    pthread_exit(NULL);
}

void *compara_hashes(void* arg){

    //Compara hasta que la cantidad de archivos por comparar sea 0
    while(cantidad_total>0){

        sem_wait(&compara_coord);//Esperamos por el codificador de hashes  

        pthread_mutex_lock(&mutex_list);//Seccion critica, recorremos la lista de visitados
            comparar_hash(cabeza->nombre_archivo, cabeza->valor_hash);
        pthread_mutex_unlock(&mutex_list);   

        cantidad_total--; //Decrementamos la cantidad de archivos
        sem_post(&coord_hash); //Liberamos al codificador de hashes
    }

    sem_post(&compara_coord); //liberamos los hilos restantes que puedan estar bloqueados
    pthread_exit(NULL);
}

void crear_hilos(int cant_hilos, int cant_archivos, char hash_modo) {

    //Guardamos en cantidad_total la cantidad de archivos
    cantidad_total = cant_archivos;

    //Inicializamos los semaforos que usaremos
    inicializar_semaforos();

    pthread_mutex_init(&mutex_list, NULL);

    //Arreglo de hilos
    pthread_t hilos[cant_hilos];

    //Apuntadores para poder pasarle los argumentos a los hilos
    char* modo = malloc(sizeof(char));
    modo = &hash_modo;


    //Creamos los hilos de codificar los hashes y de comparar los hashes
    for(int i=0; i < cant_hilos; i++) {   
        if(i%2==0){

            //Hilos de codificar hashes
            if(pthread_create(hilos + i, NULL, &codifica_hashes, modo) != 0) {
                perror("Error al crear el hilo");
                exit(1);
            } 
            

        }else{
            
            //Hilos de comparar hashes
            if(pthread_create(hilos + i, NULL, &compara_hashes, NULL) != 0) {
                perror("Error al crear el hilo");
                exit(1);
            }
            
        }   
    }

    //Join de los hilos creados
    for(int i = 0; i < cant_hilos; i++) {
        pthread_join(hilos[i], NULL);
    }

    //destruimos el mutex
    pthread_mutex_destroy(&mutex_list);

    //Destruimos los semaforos
    sem_destroy(&coord_hash);
    sem_destroy(&hash_mutex);
    sem_destroy(&compara_coord);
    sem_destroy(&pila_hash_mutex);
    sem_destroy(&visitados_mutex);
} 