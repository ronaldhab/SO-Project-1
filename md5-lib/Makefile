md5lib.a: md5c.o
	ar -r libmd5.a md5c.o

md5c.o	: md5c.c md5.h global.h
	gcc -O2 -c md5c.c

