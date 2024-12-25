#include <stdio.h>
#include <string.h>
#include <pthread.h>
// #include "argumentos.h"
#include "operaciones_estructuras.h"
#include "explora_dir.h"
#include "estructuras.h"

int main(int argc, char *argv[]) {
    // identificar_argumentos(argc, argv);
    char *directorio = argv[4];
    
    explora_dir(".");

    runner('l');

    imprimir_lista();
    imprimir_lista_duplicados();

    struct Nodo *aux = tope_pila;

    liberar_lista();
    liberar_pila();
    liberar_lista_duplicados();
    return 0;
}
