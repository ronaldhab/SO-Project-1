TARGET = main
OBJS = main.o 
CC = gcc

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c 
	$(CC) -c $< -o $@

.PHONY: clear
clear:
	@rm -f *.o $(TARGET)