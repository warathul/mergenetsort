CC=gcc
CFLAGS=-I. -O3 -Wall
LDFLAGS=
DEPS=mergenetsort.h
OBJ=main.o mergenetsort.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mergenetsort: $(OBJ)
	gcc -o $@ $^ $(LDFLAGS)

clean:
	rm -rf mergenetsort *.o
