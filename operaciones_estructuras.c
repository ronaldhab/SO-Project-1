#define _DEFAULT_SOURCE
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include "operaciones_estructuras.h"
#include "estructuras.h"
#include "obtener_hashes.h"

#define READ 0
#define WRITE 1

//Apuntadores de las estructuras
struct Nodo *tope_pila = NULL;
struct Nodo_visitados *cabeza = NULL;
struct Nodo_duplicados *duplicados = NULL;

/*Funcion para comparar los hash*/
void comparar_hash(char* archivo, char hash[33]) {
    int cont = 0;
    struct Nodo_visitados *aux = cabeza; 
    int es_duplicado = 0;

    while(aux != NULL && !es_duplicado){

        if(strcmp(aux->valor_hash, hash) == 0){
            es_duplicado = 1;
            insertar_duplicados(aux->nombre_archivo, archivo);
        }
        aux = aux->siguiente;
    }
}

/*FUNCION PROVISIONAL PARA CORRER obtener_hashes*/
void runner(char modo){
    struct Nodo* stack_runner = tope_pila;

    while (stack_runner!=NULL)
    {
        if(modo == 'e'){
            obtener_hashes_exec(stack_runner->nombre_archivo);
        }else 
            if(modo == 'l'){
                obtener_hashes_libreria(stack_runner->nombre_archivo);
        }
        
        stack_runner = stack_runner->siguiente;
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
    nuevo = malloc(sizeof(struct Nodo_visitados));
    nuevo->nombre_archivo = (char*)malloc(NAME_MAX);
    strcpy(nuevo->nombre_archivo, nombre);
    strcpy(nuevo->valor_hash, codigo);
    
    if(cabeza == NULL){
        cabeza = nuevo;
        nuevo->siguiente = NULL;
    }else{
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }

}

void insertar_duplicados(char* nombre, char* nombre_duplicado){

    int insertado = 0;
    struct Nodo_duplicados *nuevo;
    nuevo = malloc(sizeof(struct Nodo_duplicados));

    //Inicializamos cada uno de los campos del nuevo nodo
    nuevo->archivo = (char*)malloc(NAME_MAX);
    nuevo->duplicado = (char*)malloc(NAME_MAX);
    strcpy(nuevo->archivo, nombre);
    strcpy(nuevo->duplicado, nombre_duplicado);
    
    if(duplicados == NULL){
        duplicados = nuevo;
        nuevo->siguiente = NULL;
    }else{
        struct Nodo_duplicados *aux = duplicados;

        while(aux != NULL && insertado == 0){ 
            if(strcmp(aux->archivo, nombre) == 0){
                nuevo->siguiente = aux->siguiente;
                aux->siguiente = nuevo;

                insertado = 1;
            }
            aux = aux->siguiente;
        }
        
        if(!insertado){
            nuevo->siguiente = duplicados;
            duplicados = nuevo;
        }
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

void liberar_lista_duplicados(){
    struct Nodo_duplicados *aux = duplicados;
    struct Nodo_duplicados *borrado;
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

void imprimir_lista(){ 

    struct Nodo_visitados *impreso = cabeza;
    
    while(impreso != NULL){

        printf("-------------------------------------------------\n");
        printf("%s\n", impreso->nombre_archivo);
        printf("%s", impreso->valor_hash);
        printf("-------------------------------------------------\n\n");

        impreso = impreso->siguiente;
    }
}

void imprimir_lista_duplicados(){ 

    struct Nodo_duplicados *impreso = duplicados;
    
    printf("\n*****************LISTA DE DUPLICADOS*************************\n\n\n");

    while(impreso != NULL){

        printf("-------------------------------------------------\n");
        printf("%s, es duplicado de ", impreso->duplicado);
        printf("%s\n", impreso->archivo);
        printf("-------------------------------------------------\n\n");

        impreso = impreso->siguiente;
    }
}