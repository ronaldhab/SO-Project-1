TARGET = main
SRC = explora_dir.c operaciones.c 
OBJ = $(SRC:.c=.o)
INCLUDE = estructuras.h operaciones.h
CC = gcc

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c $(INCLUDE)
	$(CC) -c -o $@ $< 

.PHONY: clear
clear:
	@rm -f *.o $(TARGET)