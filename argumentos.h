#ifndef _ARGUMENTOS_H_
#define _ARGUMENTOS_H_

#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

/***********************VERIFICAR ARGUMENTOS*************************/
void identificar_argumentos(int argc, char *argv[]);
int es_directorio_valido(const char *ruta);
int numero_de_hilos_validos(char *argv, const char *endptr, long num);
/********************************************************************/

#endif