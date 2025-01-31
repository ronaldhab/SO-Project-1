#define _DEFAULT_SOURCE
#include <unistd.h>
#include <sys/types.h>
#include "md5-lib/md5c.c"
#include "operaciones_estructuras.h"
#include "obtener_hashes.h"

#define READ 0
#define WRITE 1

char hash[33] = { 0 }; //Variable global para almacenar el hash

/*Funcion para obtener los hash en modo libreria*/
void obtener_hashes_libreria(char* nombre_archivo) {

    MDFile(nombre_archivo, hash); //Obtenemos el hash del archivo en modo libreria
}

/*Funcion para obtener los hash en modo ejecutable*/
void obtener_hashes_exec(char* nombre_archivo) {

    pid_t pid;
    int fd[2];
    
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }
    
    pid = fork();

    if (pid == 0) {  // Proceso Hijo

        dup2(fd[WRITE], STDOUT_FILENO);//Redireccionamos la salida estandar al pipe
        close(fd[WRITE]);

        execlp("md5-app/md5", "./md5", nombre_archivo, NULL);// ejecutamos el programa md5    
        fflush(stdout);
    }
    else{        
        read(fd[READ], hash, 33); //Leemos el hash del pipe
        close(fd[READ]);
    }
    fflush(stdout);
}