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

    crear_hilos(5, "ProofCode", 'l');

    //explora_dir(".");

    //runner('e');

    imprimir_lista();
    imprimir_lista_duplicados();


    liberar_lista();
    liberar_pila();
    liberar_lista_duplicados();

    return 0;
}
