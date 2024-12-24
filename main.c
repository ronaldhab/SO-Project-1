#include <stdio.h>
#include <string.h>
// #include "argumentos.h"
#include "operaciones.h"

int main(int argc, char *argv[]) {
    // identificar_argumentos(argc, argv);
    char *directorio = argv[4];
    insertar_visitados("Juancito", "1234567890");
    obtener_hashes_exec();
    return 0;
}
