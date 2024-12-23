#include "argumentos.h"

int es_directorio_valido(const char *ruta) {
    struct stat info;

    if (stat(ruta, &info) != 0) {
        // Error al obtener información del archivo/directorio
        if (errno == ENOENT) {
          fprintf(stderr,"Error: El directorio no existe\n");
        } else if(errno == EACCES){
          fprintf(stderr,"Error: No tienes permisos para acceder a este directorio\n");
        } else {
          fprintf(stderr,"Error desconocido al acceder al directorio\n");
        }
        return 0; // No es un directorio válido
    }

    if (S_ISDIR(info.st_mode)) {
        return 1; // Es un directorio
    } else {
        fprintf(stderr,"Error: La ruta proporcionada no es un directorio\n");
        return 0; // No es un directorio
    }
}

int numero_de_hilos_validos(char *argv, const char *endptr, long num) {
    if (errno == ERANGE) { // Overflow o underflow
        fprintf(stderr, "Error: El número está fuera del rango representable.\n");
        return 0;
    }
    else if (endptr == argv[2]) { // No se pudo convertir ningún carácter
        fprintf(stderr, "Error: No se ingresó un número válido.\n");
        return 0;
    }
    else if (*endptr != '\0') { // Caracteres no numéricos después del número
        fprintf(stderr, "Error: Caracteres no numéricos en el segundo argumento.\n");
        return 0;
    }
    else if(num < 1) {
        printf("El numero debe ser entero positivo\n");
        return 0;
    }
    
    return 1;  
}

// ./duplicados -t <numero de threads> -d <directorio de inicio> -m <e | l >
void identificar_argumentos(int argc, char *argv[]) {

    //Comprobar que hay 7 argumentos
    if(argc > 7) {
        printf("Hay muchos argumentos\n");
        exit(1);
    } 
    else if(argc < 7) {
        printf("Faltan argumentos\n");
        exit(1);
    }

    //Comprobacion segundo argumento
    if(strcmp(argv[1], "-t") != 0) {
        printf("Usa: %s -t <numero de threads> -d <directorio de inicio> -m <e | l >\n", argv[0]);
        exit(1);
    } 
    
    //Comprobacion tercer argumento
    char *endptr;
    long num = strtol(argv[2], &endptr, 10);
    if(numero_de_hilos_validos(argv[2], endptr, num) == 0) {
        exit(1);
    }

    //Comprobacion cuarto argumento
    if(strcmp(argv[3], "-d") != 0) {
        printf("Usa: %s -t %ld -d <directorio de inicio> -m <e | l >\n", argv[0], num);
        exit(1);
    }

    //Comprobacion quinto argumento
    if(es_directorio_valido(argv[4]) == 0) {
        exit(1);
    }

    //Comprobacion sexto argumento
    if(strcmp(argv[5], "-m") != 0) {
        printf("Usa: %s -t %ld -d %s -m <e | l >\n", argv[0], num, argv[4]);
        exit(1);
    }

    //Comprobacion septimo argumento
    if((strcmp(argv[6], "e") != 0) && (strcmp(argv[6], "l") != 0)) {
        printf("Usa: %s -t %ld -d %s -m <e | l >\n", argv[0], num, argv[4]);
        exit(1);
    }
}