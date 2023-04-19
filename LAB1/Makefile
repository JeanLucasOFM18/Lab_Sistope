CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -std=c99
OBJ=funciones.o lab1.o
DEPS=funciones.h
EXEC=lab1

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

funciones.o: funciones.c $(DEPS)
	$(CC) $(CFLAGS) -c $<

lab1.o: lab1.c $(DEPS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(EXEC)