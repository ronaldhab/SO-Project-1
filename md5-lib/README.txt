Instrucciones de uso:

1) Construir la librería haciendo uso del Makefile
2) Enlazar la librería estática (archivo de extensión .a) a su proyecto
3) La librería se utiliza en el código fuente a través de la función MDFile cuya firma es:

int MDFile(char* filename, char hashValue[33]);

Y la cual se debe incluir en el proyecto para su posterior uso. Sus parámetros son:
filename = nombre del archivo al cual se le calculará el hash md5
hashValue = arreglo de tipo char donde se almacenara el valor del hash md5 del archivo filename
