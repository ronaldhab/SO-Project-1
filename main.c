#include <stdio.h>
#include <string.h>
// #include "argumentos.h"
#include "operaciones.h"

int main(int argc, char *argv[]) {
    // identificar_argumentos(argc, argv);
    char *directorio = argv[4];
    insertar_visitados("explora_dir.c", "0");
    insertar_visitados("readme.md", "0");
    insertar_visitados("argumentos.c", "0");
    insertar_visitados("operaciones.h", "0");

    obtener_hashes_exec();
    return 0;
}
