#define _DEFAULT_SOURCE
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <dirent.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include "../estructuras.h"
#include "../obtener_hashes.h"

// sem_t coord_hash;
// sem_t hash_mutex;
// sem_t compara_mutex;
// sem_t compara_coord;
// sem_t pila_hash_mutex;
// sem_t visitados_mutex;

//Apuntadores de las estructuras
struct Nodo *tope_pila = NULL;
struct Nodo_visitados *cabeza = NULL;
struct Nodo_duplicados *duplicados = NULL;

int cantidad_total = 0; //Variable global para manejar la cantidad de archivos
pthread_mutex_t mutex_list;
char hash_g[33] = { 0 };

// void inicializar_semaforos(){
//     sem_init(&coord_hash, 0, 0);
//     sem_init(&hash_mutex, 0, 1);
//     sem_init(&compara_mutex, 0, 1);
//     sem_init(&compara_coord, 0, 0);
//     sem_init(&pila_hash_mutex, 0, 1);
//     sem_init(&visitados_mutex, 0, 1);
// }

void pop(){
    
    if(tope_pila != NULL){
        struct Nodo* eliminado = tope_pila;
        tope_pila = tope_pila->siguiente;
        free(eliminado->nombre_archivo);
        free(eliminado);
    }
}

int comparar_hash(char* archivo, char hash[33]) {
    struct Nodo_visitados *aux = cabeza->siguiente; 
    int es_duplicado = 0;

    while(aux != NULL && !es_duplicado){

        if(strcmp(aux->valor_hash, hash) == 0){
            es_duplicado = 1;
            insertar_duplicados(aux->nombre_archivo, archivo);
            return 1;
        }
        aux = aux->siguiente;
    }
    return 0;
}

//Función para insertar los archivos en la lista de visitados
void insertar_visitados(char* nombre, char codigo[33]){

    int insertado = 0;
    struct Nodo_visitados *nuevo;
    nuevo = malloc(sizeof(struct Nodo_visitados));
    nuevo->nombre_archivo = (char*)malloc(NAME_MAX);
    strcpy(nuevo->nombre_archivo, nombre);
    strcpy(nuevo->valor_hash, codigo);
    
    if(cabeza == NULL){
        cabeza = nuevo;
        nuevo->siguiente = NULL;
    }else{

        struct Nodo_visitados *aux = cabeza;
        while(aux != NULL && !insertado){ 
            if(strcmp(aux->nombre_archivo, nombre) == 0){
                nuevo->siguiente = aux->siguiente;
                aux->siguiente = nuevo;

                insertado = 1;
            }
            aux = aux->siguiente;
        }
        
        if(!insertado){
            nuevo->siguiente = cabeza;
            cabeza = nuevo;
        }
        
    }

}

//Función para insertar los archivos en la lista de duplicados
void insertar_duplicados(char* nombre, char* nombre_duplicado){

    int insertado = 0;
    struct Nodo_duplicados *nuevo;
    nuevo = malloc(sizeof(struct Nodo_duplicados));

    //Inicializamos cada uno de los campos del nuevo nodo
    nuevo->archivo = (char*)malloc(NAME_MAX);
    nuevo->duplicado = (char*)malloc(NAME_MAX);
    strcpy(nuevo->archivo, nombre);
    strcpy(nuevo->duplicado, nombre_duplicado);
    
    if(duplicados == NULL){
        duplicados = nuevo;
        nuevo->siguiente = NULL;
    }else{
        struct Nodo_duplicados *aux = duplicados;

        while(aux != NULL && !insertado){ 
            if((strcmp(aux->archivo, nombre) == 0) && (strcmp(aux->duplicado, nombre_duplicado) == 0) ){

                insertado = 1;
            }
            aux = aux->siguiente;
        }
        
        if(!insertado){
            nuevo->siguiente = duplicados;
            duplicados = nuevo;
        }
    }
}


int *codifica_hashes(void* arg){

    char modo = *(char*)arg;

    while (tope_pila!=NULL)
    {
        //Sección crítica para manipular la pila de archivos
        // sem_wait(&hash_mutex);    
            if(tope_pila!=NULL){
                if(modo == 'e'){

                    //Obtenemos el hash del archivo en moodo ejecutable
                    obtener_hashes_exec(tope_pila->nombre_archivo);
                    return 1;

                }else if(modo == 'l'){

                    //Obtenemos el hash del archivo en moodo libreria
                    obtener_hashes_libreria(tope_pila->nombre_archivo);
                    return 2;
                }

                //Insertamos el nombre y el hash del archivo en la lista de visitados 
                insertar_visitados(tope_pila->nombre_archivo, hash_g);   

                // sem_post(&compara_coord);//Le pasamos el control al hilo del comparador
                // sem_wait(&coord_hash);//Esperamos por el comparador

                pop();//Sacamos el nombre del archivo de la pila
            }

        // sem_post(&hash_mutex);
    }
    pthread_exit(NULL);
    return 0;
}

void *compara_hashes(void* arg){

    //Compara hasta que la cantidad de archivos por comparar sea 0
    while(cantidad_total>0){

        // sem_wait(&compara_coord);//Esperamos por el codificador de hashes  

        pthread_mutex_lock(&mutex_list);//Seccion critica, recorremos la lista de visitados
            comparar_hash(cabeza->nombre_archivo, cabeza->valor_hash);
        pthread_mutex_unlock(&mutex_list);   

        cantidad_total--; //Decrementamos la cantidad de archivos
        // sem_post(&coord_hash); //Liberamos al codificador de hashes
    }

    // sem_post(&compara_coord); //liberamos los hilos restantes que puedan estar bloqueados
    pthread_exit(NULL);
}

int crear_hilos(int cant_hilos, int cant_archivos, char hash_modo) {

    //Guardamos en cantidad_total la cantidad de archivos
    cantidad_total = cant_archivos;

    //Inicializamos los semaforos que usaremos
    // inicializar_semaforos();

    pthread_mutex_init(&mutex_list, NULL);

    //Arreglo de hilos
    pthread_t hilos[cant_hilos];

    //Apuntadores para poder pasarle los argumentos a los hilos
    char* modo = malloc(sizeof(char));
    modo = &hash_modo;

    int cuenta_hilos = 0;
    //Creamos los hilos de codificar los hashes y de comparar los hashes
    for(int i=0; i < cant_hilos; i++) {   
        if(i%2==0){

            //Hilos de codificar hashes
            if(pthread_create(hilos + i, NULL, &codifica_hashes, modo) != 0) {
                perror("Error al crear el hilo");
                cuenta_hilos++;
            } 
            

        }else{
            
            //Hilos de comparar hashes
            if(pthread_create(hilos + i, NULL, &compara_hashes, NULL) != 0) {
                perror("Error al crear el hilo");
                cuenta_hilos++;
            }
            
        }   
    }

    //Join de los hilos creados
    for(int i = 0; i < cant_hilos; i++) {
        pthread_join(hilos[i], NULL);
    }

    //destruimos el mutex
    pthread_mutex_destroy(&mutex_list);

    return cuenta_hilos;
}

void test_crear_hilos() {
    // crear_hilos(3, "ProofCode", 'e');
    CU_ASSERT(crear_hilos(4, 3, 'e') == 4);
    CU_ASSERT(crear_hilos(7, 3, 'e') == 7);
    CU_ASSERT(crear_hilos(4, 3, 'e') == 2);
}

int main() {
    insertar_visitados("archivo1", "hash1");
    insertar_visitados("archivo2", "hash2");
    insertar_visitados("archivo3", "hash1");
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Hilos Suite", 0, 0);
    CU_add_test(suite, "test_crear_hilos", test_crear_hilos);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}

