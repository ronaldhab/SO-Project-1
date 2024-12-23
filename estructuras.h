#ifndef estructuras_h
#define estructuras_h
#include <stdio.h>

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

#endif