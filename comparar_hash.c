#include "operaciones.h"

char *duplicados[];

void comparar_hash() {
    int cont = 0;
    for(int i = 0; i < (strlen(cabeza) + 1); i++) {
        for(int j = 0; j < (strlen(cabeza) + 1); j++) {
            if(i != j) {
                if(cabeza[i].valor_hash == cabeza[j].valor_hash) {
                    duplicados[cont] = cabeza[j].nombre_archivo;
                    cont++;
                }
            }
        }
    }
}