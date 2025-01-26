#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
// #include "argumentos.h"
#include "operaciones_estructuras.h"
#include "explora_dir.h"
#include "estructuras.h"
#include "hilos.h"

int main(int argc, char *argv[]) {

    int archivos = 0;
    archivos = explora_dir("ProofCode");
    crear_hilos(200, archivos, "ProofCode", 'l');


    //runner('e');

    imprimir_lista();
    imprimir_lista_duplicados();


    liberar_lista();
    liberar_pila();
    liberar_lista_duplicados();

    return 0;
}