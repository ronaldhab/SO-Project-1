#include <stdio.h>
#include <string.h>
// #include "argumentos.h"
#include "operaciones.h"
#include "explora_dir.h"

int main(int argc, char *argv[]) {
    // identificar_argumentos(argc, argv);
    char *directorio = argv[4];
    
    explora_dir(".");

    runner();

    imprimir_lista();
    imprimir_lista_duplicados();

    liberar_lista();
    liberar_pila();
    liberar_lista_duplicados();
    return 0;
}
