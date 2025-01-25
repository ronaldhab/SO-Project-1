#define _DEFAULT_SOURCE
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <dirent.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "../hilos.h"
#include "../semaforos.h"
#include "../estructuras.h"
#include "../explora_dir.h"
#include "../operaciones_estructuras.h"
#include "../obtener_hashes.h"

int finish = 0;

void *explora_directorios(void* arg){// DE MOMENTO SIN PROBLEMAS
    
    char* dir = (char*)arg;

    explora_dir(dir); //La funcion esta en el .c que se llama igual
    // printf("La direccion es: %s\n", dir);

    //sem_post(&coord_hash); //Pasamos el control al codificador de hashes

    pthread_exit(NULL);

}

void *codifica_hashes(void* arg){// EN CONSTRUCCION (PRIORIDAD)

    char modo = *(char*)arg;

    sleep(0.5f);
    //sem_wait(&coord_hash); //Esperamos por el explorador de directorios
    //sem_post(&coord_hash); //Liberamos todos los hilos que estaban en espera

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

    finish = 1;
    pthread_exit(NULL);
}

void *compara_hashes(void* arg){// EN CONSTRUCCION 

    /*SE ESTA AGREGANDO MAS DE UNA VEZ EL MISMO ELEMENTO A LA LISTA DE DUPLICADOS OJO!*/

    //sem_wait(&compara_coord);//Esperamos por el codificador de hashes

    while(!finish){
        sem_wait(&compara_coord);//Esperamos por el codificador de hashes

        sem_wait(&visitados_mutex);//Seccion critica, recorremos la lista de visitados
            comparar_hash(cabeza->nombre_archivo, cabeza->valor_hash);
            //imprimir_lista_duplicados();
        sem_post(&visitados_mutex);
        sem_post(&coord_hash);//Liberamos al codificador de hashes
    }

    pthread_exit(NULL);
}

int crear_hilos(int cant, char* dir, char hash_modo) {

    //Inicializamos los semaforos que usaremos
    inicializar_semaforos();

    //Arreglo de hilos
    pthread_t hilos[cant];
    //Atributos para colocar detached al hilo del comparador (SOLO PARA PRUEBAS)
    pthread_attr_t atributos;
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_DETACHED);

    int i = 0;
    int resto;

    //Apuntadores para poder pasarle los argumentos a los hilos
    char* directorio = (char*)malloc(sizeof(NAME_MAX));
    directorio = dir;
    char* modo = malloc(sizeof(char));
    modo = &hash_modo;


    // A PARTIR DE AQUI DA EL ERROR DE VIOLACION DE SEGMENTO
    
    //Creamos el hilo de explorar directorio (DE MOMENTO SERÁ ÚNICO)
    if(pthread_create(hilos + i, NULL, &explora_directorios, directorio) != 0) {
        perror("Error al crear el hilo");
        return 1;
    }
    i++;

    //Creamos los hilos de codificar los hashes (LA LOGICA ES QUE TENGA TODOS LOS HILOS MENOS 2)
    for(; i <= cant - 2; i++) {      
        if(pthread_create(hilos + i, NULL, &codifica_hashes, modo) != 0) {
            perror("Error al crear el hilo");
            return 1;
        } 
    }

    //Creamos el hilo para el comparador
    if(pthread_create(hilos + i, NULL, &compara_hashes, NULL) != 0) {
        perror("Error al crear el hilo");
        return 1;

    }

    //Join de los hilos creados
    for(int i = 0; i < cant-1; i++) {
        pthread_join(hilos[i], NULL);
    }

    //Destruimos los semaforos
    sem_destroy(&coord_hash);
    sem_destroy(&compara_coord);
    sem_destroy(&pila_hash_mutex);
    sem_destroy(&visitados_mutex);
    return 0;
} 

void test_crear_hilos() {
    crear_hilos(3, "ProofCode", 'e');
    CU_ASSERT(crear_hilos(4, "ProofCode", 'e') == 0);
    CU_ASSERT(crear_hilos(4, "ProofCode", 'e') == 1);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Hilos Suite", 0, 0);
    CU_add_test(suite, "test_crear_hilos", test_crear_hilos);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}