#ifndef _SEMAFOROS_H_
#define _SEMAFOROS_H_

#include <semaphore.h>

extern sem_t coord_hash;
extern sem_t hash_mutex;
extern sem_t compara_coord;

void inicializar_semaforos();

#endif
