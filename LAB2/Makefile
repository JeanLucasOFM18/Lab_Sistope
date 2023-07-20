CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -std=c99 -Wno-unused-parameter -Wno-unused-variable

EXEC1=lab2
EXEC2=worker
EXEC3=broker

SRCS1=lab2.c fbroker.c fworker.c
SRCS2=worker.c fworker.c
SRCS3=broker.c fbroker.c

DEPS=fbroker.h fworker.h

all: $(EXEC1) $(EXEC2) $(EXEC3)

$(EXEC1): $(SRCS1) $(DEPS)
	$(CC) $(CFLAGS) $(SRCS1) -o $@

$(EXEC2): $(SRCS2) $(DEPS)
	$(CC) $(CFLAGS) $(SRCS2) -o $@

$(EXEC3): $(SRCS3) $(DEPS)
	$(CC) $(CFLAGS) $(SRCS3) -o $@

clean:
	rm -f $(EXEC1) $(EXEC2) $(EXEC3)