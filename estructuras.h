#ifndef estructuras_h
#define estructuras_h

#include<stdlib.h>
#include<stdio.h>

//estructura de pila de archivos por visitar
struct Nodo{
    char* nombre_archivo;
    struct Nodo *siguiente;
};

//estructura de datos lista archivos visitados
struct Nodo_visitados{
    char* nombre_archivo;
    char valor_hash[33];
    struct Nodo_visitados *siguiente;
};

/***********************OPERACIONES PARA LAS ESTRUCTURAS***********************/
//INSERTAR ELEMENTO EN LA PILA
void push(char* nombre, struct Nodo* tope);

//SACAR ELEMENTO DE LA PILA
char* pop(struct Nodo* tope);

//BORRAR LA PILA
void liberar_pila(struct Nodo* tope);

//INSERTAR NODO EN LA LISTA 
void insertar_visitados(struct Nodo_visitados* cabeza, char* nombre, char codigo[33]);

//BORRAR LA LISTA
void liberar_lista(struct Nodo_visitados* cabeza);
/******************************************************************************/

#endif