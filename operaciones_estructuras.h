#ifndef _OPERACIONES_H_
#define _OPERACIONES_H_

//#include "estructuras.h"
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
void liberar_lista_duplicados();

//IMPRIMIR ESTRUCTURAS
void imprimir_pila();
void imprimir_lista();
void imprimir_lista_duplicados();

void comparar_hash(char* archivo, char hash[33]);

//PROVISIONAL
void runner(char modo);

/******************************************************************************/

#endif