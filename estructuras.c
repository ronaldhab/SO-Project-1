#include<stdlib.h>
#include<stdio.h>
#include<dirent.h>
#include"estructuras.h"

void push(char* nombre, struct Nodo* tope){
    struct Nodo *nuevo;
    nuevo = malloc(sizeof(struct Nodo));
    nuevo->nombre_archivo = nombre;

    if(tope == NULL){
        tope = nuevo;
        nuevo->siguiente = NULL;
    }else{
        nuevo->siguiente = tope;
        tope = nuevo;
    }

}

char* pop(struct Nodo* tope){

    char* nombre = tope->nombre_archivo;
    struct Nodo* eliminado = tope;
    tope = tope->siguiente;
    free(eliminado);
    return nombre;

}

//BORRAR LA PILA
void liberar_pila(struct Nodo* tope){
    struct Nodo *aux = tope;
    struct Nodo *borrado;
    while(aux!=NULL){
        borrado = aux;
        aux = aux->siguiente;
        free(borrado);
    }
}

//INSERTAR NODO EN LA LISTA 
void insertar_visitados(struct Nodo_visitados* cabeza, char* nombre, char codigo[33]){

    struct Nodo_visitados *nuevo;
    nuevo = malloc(sizeof(struct Nodo));
    nuevo->nombre_archivo = nombre;

    for(int i=0; i<33; i++){
        nuevo->valor_hash[i] = codigo[i];
    }
    
    if(cabeza == NULL){
        cabeza = nuevo;
        nuevo->siguiente = NULL;
    }else{
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }

}

//BORRAR LA LISTA
void liberar_lista(struct Nodo_visitados* cabeza){
    struct Nodo_visitados *aux = cabeza;
    struct Nodo_visitados *borrado;
    while(aux!=NULL){
        borrado = aux;
        aux = aux->siguiente;
        free(borrado);
    }
}