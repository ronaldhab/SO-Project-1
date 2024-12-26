#include <pthread.h>

void *rutina(void* arg){

}

void crear_hilos(int m) {
    pthread_t hilos[m];
    for(int i = 0; i < m; i++) {
        if(pthread_create(hilos + i, NULL, &rutina, NULL) != 0) {
            perror("Error al crear el hilo");
            exit(1);
        }
    }

    for(int i = 0; i < m; i++) {
        pthread_join(hilos[i], NULL);
    }
} 