#include "argumentos.h"
#include "enlaces.h"

int main(int argc, char *argv[]) {
    identificar_argumentos(argc, argv);
    char *directorio = argv[4];
    identificar_enlaces_simbolicos(directorio);
    return 0;
}
