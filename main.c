#include <stdlib.h>
#include <stdio.h>
#include "argumentos.h"
#include "operaciones_estructuras.h"
#include "explora_dir.h"
#include "estructuras.h"
#include "hilos.h"

int main(int argc, char *argv[]) {

    identificar_argumentos(argc, argv);

    int num_threads;
    int archivos = 0;
    char modo_MD5;

    num_threads = atoi(argv[2]);
    archivos = explora_dir(argv[4]);
    modo_MD5 = argv[6][0];

    if(num_threads>=2){
        crear_hilos(num_threads, archivos, modo_MD5);
    }else if(num_threads==1){
        runner(modo_MD5);
    }else{
        printf("Cantidad de hilos inválida, por favor intente de nuevo\n");
        exit(1);
    }



    //runner('e');

    imprimir_lista_duplicados();


    liberar_lista();
    liberar_pila();
    liberar_lista_duplicados();

    return 0;
}