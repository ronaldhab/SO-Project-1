#include <stdio.h>
#include <string.h>
// #include "argumentos.h"
#include "operaciones.h"

int main(int argc, char *argv[]) {
    // identificar_argumentos(argc, argv);
    char *directorio = argv[4];
    insertar_visitados("/home/brhandon/Documentos/SO-Project-1/explora_dir.c", "0");
    // insertar_visitados("readme.md", NULL);
    // insertar_visitados("argumentos.c", NULL);
    // insertar_visitados("operaciones.h", NULL);

    obtener_hashes_exec();
    return 0;
}
