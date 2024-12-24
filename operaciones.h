#ifndef operaciones_h
#define operaciones_h

#include "estructuras.h"
#include <stdlib.h>

/***********************OPERACIONES PARA LAS ESTRUCTURAS***********************/
//INSERTAR ELEMENTO EN LA PILA
void push(char* nombre);

//SACAR ELEMENTO DE LA PILA
char* pop();

//BORRAR LA PILA
void liberar_pila();

//INSERTAR NODO EN LA LISTA 
void insertar_visitados(char* nombre, char codigo[33]);

//INSERTAR NODO EN LA LISTA DE DUPLICADOS
void insertar_duplicados(char* archivo, char* duplicado);

//BORRAR LA LISTA
void liberar_lista();

//IMPRIMIR LA PILA
void imprimir_pila();

//COMPARAR LOS CODIGOS HASH EN LA LISTA DE VISITADOS
void comparar_hash(char* archivo, char hash[33]);
void obtener_hashes_libreria();
void obtener_hashes_exec();

/******************************************************************************/

#endif