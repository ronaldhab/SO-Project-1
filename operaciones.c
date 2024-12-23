#define _DEFAULT_SOURCE
#include <dirent.h>
#include <string.h>
#include "md5-lib/md5.h"
#include "operaciones.h"

struct Nodo *tope_pila = NULL;
struct Nodo_visitados *cabeza = NULL;
char *duplicados[];

/*Funcion para comparar los hash*/
void comparar_hash() {
    int cont = 0;
    for(int i = 0; i < (strlen(cabeza) + 1); i++) {
        for(int j = 0; j < (strlen(cabeza) + 1); j++) {
            if(i != j) {
                if(cabeza[i].valor_hash == cabeza[j].valor_hash) {
                    duplicados[cont] = cabeza[j].nombre_archivo;
                    cont++;
                }
            }
        }
    }
}

/*Funcion para obtener los hash*/
void obtener_hashes(char modo) {
    struct Nodo_visitados *actual = cabeza;
    if(modo == 'l') {
        while (actual != NULL) {
            MDFile (actual->nombre_archivo, actual->valor_hash);
            actual = actual->siguiente;
        }
    }
}

/*Funcion para apilar*/
void push(char* nombre){
    struct Nodo *nuevo;
    nuevo = malloc(sizeof(struct Nodo));
    
    //Inicializamos el nuevo nodo
    nuevo->nombre_archivo = (char*)malloc(NAME_MAX);
    strcpy(nuevo->nombre_archivo, nombre);

    if(tope_pila == NULL){ 
        tope_pila = nuevo;
        nuevo->siguiente = NULL;

    }else{
        nuevo->siguiente = tope_pila;
        tope_pila = nuevo;
    }
}

/*Funcion para desapilar*/
char* pop(){

    char* nombre = tope_pila->nombre_archivo;
    struct Nodo* eliminado = tope_pila;
    tope_pila = tope_pila->siguiente;
    free(eliminado);
    return nombre;

}

void liberar_pila(){
    struct Nodo *aux = tope_pila;
    struct Nodo *borrado;
    while(aux!=NULL){
        borrado = aux;
        aux = aux->siguiente;
        free(borrado);
    }
}

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