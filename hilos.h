#ifndef _HILOS_H_
#define _HILOS_H_

#include <stdio.h>
#include <stdlib.h>


void *explora_directorios(void* arg);
 
void *codifica_hashes(void* arg);

void *compara_hashes(void* arg);

void crear_hilos(int cant, char* dir, char hash_modo); 

#endif