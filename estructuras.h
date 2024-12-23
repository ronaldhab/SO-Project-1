#ifndef estructuras_h

#define estructuras_h
#include <stdio.h>

//Estructura de datos de tipo pila que contendra los archivos "por visitar"
struct Nodo{
    char* nombre_archivo;
    struct Nodo *siguiente;
};

//Estructura de datos de tipo lista, que contendra los archivos "visitados"
struct Nodo_visitados{
    char* nombre_archivo;
    char valor_hash[33];
    struct Nodo_visitados *siguiente;
} *cabeza;

#endif