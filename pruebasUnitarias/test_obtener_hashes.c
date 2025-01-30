#define _DEFAULT_SOURCE
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include <stdlib.h>
#include "../md5-lib/md5c.c"


#define READ 0
#define WRITE 1

char hash[33];

// char hash[33] = { 0 };
// char hash[33] = "0e6f4cd16a3b7f89e6dbb2cc365d3964";

/*Funcion para obtener los hash en modo libreria*/
void obtener_hashes_libreria(char* nombre_archivo) {
    MDFile(nombre_archivo, hash);
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

void test_obtener_hashes_exec (){
    // Caso valido
    obtener_hashes_exec("ProofCode/prueba.txt");
    CU_ASSERT((strcmp("0e6f4cd16a3b7f89e6dbb2cc365d3964", hash) == 0) == 0);

    // Caso invalido
    CU_ASSERT(!(strcmp("0e6f4cd16a3b7f89e6dbb2cc365d3964", hash) == 0) == 0);
}

void test_obtener_hashes_libreria (){

    // Caso valido
    obtener_hashes_libreria("ProofCode/prueba.txt");
    CU_ASSERT((strcmp("0e6f4cd16a3b7f89e6dbb2cc365d3964", hash) == 0) == 0);

    // Caso invalido
    CU_ASSERT(!(strcmp("0e6f4cd16a3b7f89e6dbb2cc365d3964", hash) == 0) == 0);
}

int main() {

    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Hashes", 0, 0);
    CU_add_test(suite, "test_obtener_hashes_exec", test_obtener_hashes_exec);
    CU_add_test(suite, "test_obtener_hashes_libreria", test_obtener_hashes_libreria);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}