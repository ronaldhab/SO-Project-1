#ifndef _OBTENER_HASHES_H_
#define _OBTENER_HASHES_H_

//Variable para almacenar el valor del hash obtenido
extern char hash[33];

//Función para obtener los hashes en modo ejecutable
void obtener_hashes_exec(char* nombre_archivo);

//Función para obtener los hashes en modo librería
void obtener_hashes_libreria(char* nombre_archivo);

#endif