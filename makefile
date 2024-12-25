TARGET = main
SRC = operaciones_estructuras.c obtener_hashes.c main.c explora_dir.c 
OBJ = $(SRC:.c=.o)
INCLUDE = estructuras.h operaciones_estructuras.h obtener_hashes.h explora_dir.h 
CC = gcc

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c $(INCLUDE)
	$(CC) -c -o $@ $< 

.PHONY: clean
clean:
	@rm -f *.o $(TARGET)