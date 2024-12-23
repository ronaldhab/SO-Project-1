#ifndef operaciones_h
#define operaciones_h

#include "estructuras.h"
#include <stdlib.h>
#include <stdio.h>

/***********************OPERACIONES PARA LAS ESTRUCTURAS***********************/
//INSERTAR ELEMENTO EN LA PILA
void push(char* nombre);

//SACAR ELEMENTO DE LA PILA
char* pop();

//BORRAR LA PILA
void liberar_pila();

//INSERTAR NODO EN LA LISTA 
void insertar_visitados(char* nombre, char codigo[33]);

//BORRAR LA LISTA
void liberar_lista();

//IMPRIMIR LA PILA
void imprimir_pila();

/******************************************************************************/

#endif