#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "argumentos.h"

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


int main(int argc, char *argv[]) {
    identificar_argumentos(argc, argv);
    char directorio[] = argv[4];
    identificar_enlaces_simbolicos(directorio);
    return 0;
}
