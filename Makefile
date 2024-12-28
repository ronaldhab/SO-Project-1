TARGET = main
SRC = main.c obtener_hashes.c semaforos.c hilos.c  operaciones_estructuras.c  explora_dir.c  
OBJ = $(SRC:.c=.o)
INCLUDE = semaforos.h estructuras.h operaciones_estructuras.h obtener_hashes.h explora_dir.h hilos.h 
CFLAGS = -g 
LDLIBS = -pthread -lm
CC = gcc

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDLIBS) $(OBJ) -o $(TARGET) 

%.o: %.c $(INCLUDE) 
	$(CC) -c $(LDLIBS) -o $@ $< 

.PHONY: clean
clean:
	@rm -f *.o $(TARGET)