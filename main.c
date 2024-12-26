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

    runner('e');

    imprimir_lista();
    imprimir_lista_duplicados();

    liberar_lista();
    liberar_pila();
    liberar_lista_duplicados();
    return 0;
}
