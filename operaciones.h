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
void liberar_lista_duplicados();

//IMPRIMIR ESTRUCTURAS
void imprimir_pila();
void imprimir_lista();
void imprimir_lista_duplicados();

void comparar_hash(char* archivo, char hash[33]);

//FUNCIONES PARA OBTENER LOS HASHES
void obtener_hashes_libreria(char* nombre_archivo);
void obtener_hashes_exec(char* nombre_archivo);

//PROVISIONAL
void runner(char modo);

/******************************************************************************/

#endif