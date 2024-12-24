#define _DEFAULT_SOURCE
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
// #include "md5-lib/md5.h"
#include "operaciones.h"

#define READ 0
#define WRITE 1


struct Nodo *tope_pila = NULL;
struct Nodo_visitados *cabeza = NULL;
struct Nodo_duplicados *duplicados = NULL;

//char *duplicados[];

/*Funcion para comparar los hash*/
void comparar_hash(char* archivo, char hash[33]) {
    int cont = 0;
    struct Nodo_visitados *aux = cabeza; 
    int es_duplicado = 0;

    while(aux != NULL && !es_duplicado){

        if(strcmp(aux->valor_hash, hash)){
            es_duplicado = 1;
            insertar_duplicados(aux->nombre_archivo, archivo);
        }
        aux = aux->siguiente;
    }
    insertar_visitados(archivo, hash);
}
/*
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
*/


/*Funcion para obtener los hash*/
// void obtener_hashes_libreria() {
//     struct Nodo_visitados *actual = cabeza;
//     while (actual != NULL) {
//         MDFile (actual->nombre_archivo, actual->valor_hash);
//         actual = actual->siguiente;
//     }
// }

void obtener_hashes_exec() {
    struct Nodo_visitados *actual = cabeza;
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();


    if (pid == 0) {  // Proceso Hijo
        printf("El pid es: %d\n", pid);

        close(fd[READ]);  //Cerrar extremo de lectura

        dup2(fd[WRITE], STDOUT_FILENO);
        close(fd[WRITE]);

        execlp("md5-app/md5", "./md5", actual->nombre_archivo, actual->valor_hash, NULL);
    }
    else {
        close(fd[WRITE]);
        read(fd[READ], actual->valor_hash, 33);
        // printf("El hash es: %s\n", actual->valor_hash);
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

void insertar_duplicados(char* nombre, char* nombre_duplicado){

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
        nuevo->siguiente = duplicados;
        duplicados = nuevo;
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