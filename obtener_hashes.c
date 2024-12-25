#define _DEFAULT_SOURCE
#include <unistd.h>
#include <sys/types.h>
#include "md5-lib/md5c.c"
#include "operaciones_estructuras.h"

#define READ 0
#define WRITE 1

/*Funcion para obtener los hash en modo libreria*/
void obtener_hashes_libreria(char* nombre_archivo) {
   
    char hash_code[33] = { 0 };

    MDFile(nombre_archivo, hash_code);

    comparar_hash(nombre_archivo, hash_code);
    insertar_visitados(nombre_archivo, hash_code);

}

/*Funcion para obtener los hash en modo ejecutable*/
void obtener_hashes_exec(char* nombre_archivo) {
    char hash_code[33] = { 0 };
    pid_t pid;
    int fd[2];
    
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }
    
    pid = fork();

    if (pid == 0) {  // Proceso Hijo

        close(fd[READ]);  //Cerrar extremo de lectura

        dup2(fd[WRITE], STDOUT_FILENO);
        close(fd[WRITE]);

        execlp("md5-app/md5", "./md5", nombre_archivo, NULL);    
    }
    else{
        close(fd[WRITE]);
        
        read(fd[READ], hash_code, 33);

        comparar_hash(nombre_archivo, hash_code);
        insertar_visitados(nombre_archivo, hash_code);
    }
}