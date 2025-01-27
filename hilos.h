#ifndef _HILOS_H_
#define _HILOS_H_

#include <stdio.h>
#include <stdlib.h>
 
void *codifica_hashes(void* arg);

void *compara_hashes(void* arg);

void crear_hilos(int cant_hilos, int cant_archivos, char hash_modo); 

#endif