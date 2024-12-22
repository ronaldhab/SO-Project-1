#include <stdio.h>
#include "argumentos.h"
#include "enlaces.h"

struct lista_visitado {
    char *archivo;
    char hash[33];
} *lista_visitado;

char *duplicados;

void comparar_hash() {
    int cont = 0;
    for(int i = 0; i < (strlen(lista_visitado) + 1); i++) {
        for(int j = 0; j < (strlen(lista_visitado) + 1); j++) {
            if(i != j) {
                if(lista_visitado[i].hash == lista_visitado[j].hash) {
                    duplicados[cont] = lista_visitado[j].archivo;
                    cont++;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    identificar_argumentos(argc, argv);
    // printf("El tamanio es: %ld", strlen(argv));
    char *directorio = argv[4];
    identificar_enlaces_simbolicos(directorio);
    comparar_hash();
    return 0;
}
