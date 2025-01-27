#include <stdio.h>
#include <stdlib.h>
#include "semaforos.h"


sem_t coord_hash;
sem_t hash_mutex;
sem_t compara_mutex;
sem_t compara_coord;
sem_t pila_hash_mutex;
sem_t visitados_mutex;

void inicializar_semaforos(){
    sem_init(&coord_hash, 0, 0);
    sem_init(&hash_mutex, 0, 1);
    sem_init(&compara_mutex, 0, 1);
    sem_init(&compara_coord, 0, 0);
    sem_init(&pila_hash_mutex, 0, 1);
    sem_init(&visitados_mutex, 0, 1);
}

