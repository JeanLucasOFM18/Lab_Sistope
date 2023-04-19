CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99

all: programa

programa: main.o funciones.o
	$(CC) $(CFLAGS) -o programa main.o funciones.o

main.o: main.c funciones.h definiciones.h
	$(CC) $(CFLAGS) -c main.c

funciones.o: funciones.c funciones.h
	$(CC) $(CFLAGS) -c funciones.c

clean:
	rm -f programa *.o