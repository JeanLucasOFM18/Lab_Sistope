CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -std=c99
DEPS=funciones.h
EXEC=lab3

all: $(EXEC)

$(EXEC): lab3.c funciones.c $(DEPS)
	$(CC) $(CFLAGS) lab3.c funciones.c -o $@

clean:
	rm -f $(EXEC)