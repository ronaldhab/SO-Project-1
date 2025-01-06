#define _DEFAULT_SOURCE
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include "md5-lib/md5c.c"
#include "operaciones_estructuras.h"
#include "obtener_hashes.h"

#define READ 0
#define WRITE 1

char hash[33] = { 0 };

/*Funcion para obtener los hash en modo libreria*/
void obtener_hashes_libreria(char* nombre_archivo) {

    //char hash_code[33] = { 0 };

    MDFile(nombre_archivo, hash);

    //sem_wait(&visitados_mutex);
        //insertar_visitados(nombre_archivo, hash);
    //sem_post(&visitados_mutex);

}

/*Funcion para obtener los hash en modo ejecutable*/
void obtener_hashes_exec(char* nombre_archivo) {

    // char hash_code[40] = { 0 };
    pid_t pid;
    int fd[2];
    
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }
    
    pid = fork();

    if (pid == 0) {  // Proceso Hijo

        dup2(fd[WRITE], STDOUT_FILENO);
        close(fd[WRITE]);

        execlp("md5-app/md5", "./md5", nombre_archivo, NULL);    
        fflush(stdout);
    }
    else{        
        read(fd[READ], hash, 33);
        close(fd[READ]);
    }
    fflush(stdout);
}