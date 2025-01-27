#ifndef _OPERACIONES_H_
#define _OPERACIONES_H_

#include <stdlib.h>

//Compara un código hash con los hashes que se encuentren en la lista de visitados
void comparar_hash(char* archivo, char hash[33]);

//Ejecutar el programa en caso de que se requiera 1 hilo
void runner(char modo);

/***********************OPERACIONES PARA LAS ESTRUCTURAS***********************/

//Insertar elemento en la pila
void push(char* nombre);

//Sacar elemento de la pila
void pop();

//Verificar si un elemento se encuentra en la pila
int esta_contenido(char* nombre);

//Insertar nodo en la lista 
void insertar_visitados(char* nombre, char codigo[33]);

//Insertar nodo en la lista de duplicados
void insertar_duplicados(char* archivo, char* duplicado);

//Borrar la pila
void liberar_pila();

//Borrar la lista de visitados
void liberar_lista();

//Borrar la lista de duplicados
void liberar_lista_duplicados();

//Imprimir pila
void imprimir_pila();

//Imprimir lista de visitados
void imprimir_lista();

//Imprimir lista de duplicados
void imprimir_lista_duplicados();

/******************************************************************************/

#endif