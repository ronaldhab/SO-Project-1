#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int es_directorio_valido(const char *ruta) {
    struct stat info;

    if (stat(ruta, &info) != 0) {
        // Error al obtener información del archivo/directorio
        if (errno == ENOENT) {
        } else if(errno == EACCES){
        } else {
        }
        return 0; // No es un directorio válido
    }

    if (S_ISDIR(info.st_mode)) {
        return 1; // Es un directorio
    } else {
        return 0; // No es un directorio
    }
}

int numero_de_hilos_validos(char *argv, const char *endptr, long num) {
    if (errno == ERANGE) { // Overflow o underflow
        return 0;
    }
    else if (endptr == argv[2]) { // No se pudo convertir ningún carácter
        return 0;
    }
    else if (*endptr != '\0') { // Caracteres no numéricos después del número
        return 0;
    }
    else if(num < 1) {
        return 0;
    }
    
    return 1;  
}

int identificar_argumentos(int argc, char *argv[]) {

    //Comprobar que hay 7 argumentos
    if(argc > 7) {
        return 1;
    } 
    else if(argc < 7) {
        return 1;
    }

    //Comprobacion segundo argumento
    if(strcmp(argv[1], "-t") != 0) {
        return 1;
    } 
    
    //Comprobacion tercer argumento
    char *endptr;
    long num = strtol(argv[2], &endptr, 10);
    if(numero_de_hilos_validos(argv[2], endptr, num) == 0) {
        return 1;
    }

    //Comprobacion cuarto argumento
    if(strcmp(argv[3], "-d") != 0) {
        return 1;
    }

    //Comprobacion quinto argumento
    if(es_directorio_valido(argv[4]) == 0) {
        return 1;
    }

    //Comprobacion sexto argumento
    if(strcmp(argv[5], "-m") != 0) {
        return 1;
    }

    //Comprobacion septimo argumento
    if((strcmp(argv[6], "e") != 0) && (strcmp(argv[6], "l") != 0)) {
        return 1;
    }

    return 0;
}

void test_es_directorio_valido(void) {
    // Caso valido
    CU_ASSERT(es_directorio_valido("ProofCode") == 1);

    // Caso invalido
    CU_ASSERT(es_directorio_valido("non_existing_directory") == 0);
}

void test_numero_de_hilos_validos(void) {
    char *endptr;
    
    // Caso valido
    char *argv = "5";
    long num = strtol(argv, &endptr, 10);
    CU_ASSERT(numero_de_hilos_validos(argv, endptr, num) == 1);

    // Caso invalido
    argv = "m";
    num = strtol(argv, &endptr, 10);
    CU_ASSERT(numero_de_hilos_validos("m", endptr, 0) == 0);
}

void test_identificar_argumentos(void) {
    // Ambos casos son correctos
    char *argv[] = {{"./TEST"},{"-t"}, {"5"}, {"-d"}, {"ProofCode"}, {"-m"}, {"e"}};
    CU_ASSERT(identificar_argumentos(7, argv) == 0);  

    argv[6] = "l";
    CU_ASSERT(identificar_argumentos(7, argv) == 0);

    // Casos incorrectos (faltan argumentos o sobran argumentos)
    CU_ASSERT(identificar_argumentos(5, argv) == 1);
    CU_ASSERT(identificar_argumentos(9, argv) == 1);

    // Casos incorrectos (argumentos incorrectos)
    argv[1] = "-H";
    CU_ASSERT(identificar_argumentos(7, argv) == 1);

    argv[1] = "-t";
    argv[2] = "-9";
    CU_ASSERT(identificar_argumentos(7, argv) == 1);

    argv[2] = "5";
    argv[3] = "-q";
    CU_ASSERT(identificar_argumentos(7, argv) == 1);

    argv[3] = "-d";
    argv[4] = "non_existing_directory";
    CU_ASSERT(identificar_argumentos(7, argv) == 1);

    argv[4] = "ProofCode";
    argv[5] = "-n";
    CU_ASSERT(identificar_argumentos(7, argv) == 1);

    argv[5] = "-m";
    argv[6] = "p";
    CU_ASSERT(identificar_argumentos(7, argv) == 1);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Argumentos Suite", 0, 0);
    CU_add_test(suite, "test_es_directorio_valido", test_es_directorio_valido);
    CU_add_test(suite, "test_numero_de_hilos_validos", test_numero_de_hilos_validos);
    CU_add_test(suite, "test_identificar_argumentos", test_identificar_argumentos);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}