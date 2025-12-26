CC = gcc
CFLAGS = -Wall -Wextra -O3 -I./include

all: slpool.o

slpool.o: src/slpool.c
	$(CC) $(CFLAGS) -c src/slpool.c -o slpool.o

example: examples/example.c src/slpool.c
	$(CC) $(CFLAGS) examples/example.c src/slpool.c -o example

clean:
	rm -f *.o example
