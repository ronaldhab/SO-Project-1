#ifndef _SEMAFOROS_H_
#define _SEMAFOROS_H_

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

extern sem_t pila_hash_mutex;
extern sem_t visitados_mutex;
extern sem_t coord_hash;
extern sem_t compara_coord;

void inicializar_semaforos();

#endif
