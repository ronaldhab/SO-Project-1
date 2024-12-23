#include <stdio.h>
#include <string.h>
#include "argumentos.h"
#include "comparar_hash.h"

int main(int argc, char *argv[]) {
    identificar_argumentos(argc, argv);
    char *directorio = argv[4];
    return 0;
}
