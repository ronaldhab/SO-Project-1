#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "estructuras.h"

struct Nodo *tope_pila = NULL;
struct Nodo_visitados *cabeza = NULL;

//APILAR ARCHIVOS
void push(char* nombre){
    struct Nodo *nuevo;
    nuevo = malloc(sizeof(struct Nodo));
    //printf("El nombre del archivo es: %s\n", nombre);
    nuevo->nombre_archivo = (char*)malloc(NAME_MAX);
    strcpy(nuevo->nombre_archivo, nombre);

    if(tope_pila == NULL){
        tope_pila = nuevo;
        nuevo->siguiente = NULL;

    }else{
        nuevo->siguiente = tope_pila;
        tope_pila = nuevo;
    }

   // imprimir_pila();
    //printf("\n");

}

//DESAPILAR ARCHIVOS
char* pop(){

    char* nombre = tope_pila->nombre_archivo;
    struct Nodo* eliminado = tope_pila;
    tope_pila = tope_pila->siguiente;
    free(eliminado);
    return nombre;

}

//BORRAR LA PILA
void liberar_pila(){
    struct Nodo *aux = tope_pila;
    struct Nodo *borrado;
    while(aux!=NULL){
        borrado = aux;
        aux = aux->siguiente;
        free(borrado);
    }
}

//INSERTAR NODO EN LA LISTA 
void insertar_visitados(char* nombre, char codigo[33]){

    struct Nodo_visitados *nuevo;
    nuevo = malloc(sizeof(struct Nodo));
    nuevo->nombre_archivo = nombre;

    strcpy(nuevo->valor_hash, codigo);
    
    if(cabeza == NULL){
        cabeza = nuevo;
        nuevo->siguiente = NULL;
    }else{
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }

}

//BORRAR LA LISTA
void liberar_lista(){
    struct Nodo_visitados *aux = cabeza;
    struct Nodo_visitados *borrado;
    while(aux!=NULL){
        borrado = aux;
        aux = aux->siguiente;
        free(borrado);
    }
}

void imprimir_pila(){
    struct Nodo *impreso = tope_pila; 
    while(impreso != NULL){

        printf("%s\n", impreso->nombre_archivo);
        impreso = impreso->siguiente;
    }
}