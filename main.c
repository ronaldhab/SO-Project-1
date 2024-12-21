#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void identificar_enlaces_simbolicos(const char *directorio) {
    DIR *dir;
    struct dirent *ent;
    struct stat st;

    if ((dir = opendir(directorio)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", directorio, ent->d_name);

            if (lstat(path, &st) == 0) {
                if (S_ISLNK(st.st_mode)) {
                    printf("%s es un enlace simbólico\n", path);
                }
            } else {
                perror("lstat");
            }
        }
        closedir(dir);
    } else {
        perror("opendir");
    }
}

// ./duplicados -t <numero de threads> -d <directorio de inicio> -m <e | l >
void identificar_argumentos(int argc, char *argv[]){

    //Comprobar que hay 7 argumentos
    if(argc > 7){
        printf("Hay muchos argumentos\n");
        exit(1);
    } 
    else if(argc < 7){
        printf("Faltan argumentos\n");
        exit(1);
    }

    //Comprobacion segundo argumento
    if(strcmp(argv[1], "-t") != 0){
        printf("Usa: %s -t <numero de threads> -d <directorio de inicio> -m <e | l >\n", argv[0]);
        exit(1);
    } 
    
    //Comprobacion tercer argumento
    char *endptr;
    long num = strtol(argv[2], &endptr, 10);
    if (errno == ERANGE) { // Overflow o underflow
        fprintf(stderr, "Error: El número está fuera del rango representable.\n");
        exit(1);
    }

    if (endptr == argv[2]) { // No se pudo convertir ningún carácter
        fprintf(stderr, "Error: No se ingresó un número válido.\n");
        exit(1);
    }

    if (*endptr != '\0') { // Caracteres no numéricos después del número
        fprintf(stderr, "Error: Caracteres no numéricos en el segundo argumento.\n");
        exit(1);
    }

    if(num < 1){
        printf("El numero debe ser entero positivo\n");
        exit(1);
    }

    //Comprobacion cuarto argumento
    if(strcmp(argv[3], "-d") != 0){
        printf("Usa: %s -t %ld -d <directorio de inicio> -m <e | l >\n", argv[0], num);
        exit(1);
    } 
}


int main(int argc, char *argv[]) {
    identificar_argumentos(argc, argv);
    char directorio[] = "/home/brhandon/Documentos/SO-Project-1"; // Reemplaza con la ruta del directorio a analizar
    identificar_enlaces_simbolicos(directorio);
    return 0;
}
