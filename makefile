TARGET = main
SRC = operaciones.c main.c explora_dir.c 
OBJ = $(SRC:.c=.o)
INCLUDE = estructuras.h operaciones.h
CC = gcc

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c $(INCLUDE)
	$(CC) -c -o $@ $< 

.PHONY: clean
clean:
	@rm -f *.o $(TARGET)