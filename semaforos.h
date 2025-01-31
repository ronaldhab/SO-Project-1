#ifndef _SEMAFOROS_H_
#define _SEMAFOROS_H_

#include <semaphore.h>

extern sem_t coord_hash; //Semaforo para coordinar codifica_hash con compara_hash
extern sem_t hash_mutex; //Semaforo mutex para la pila de archivos
extern sem_t compara_coord; //Semaforo para coordinar compara_hash con codifica_hash

//Inicializa los semaforos coord_hash, hash_mutex y compara_coord
void inicializar_semaforos();

#endif
