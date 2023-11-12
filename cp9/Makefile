CC = gcc
CFLAGS = -std=c99 -Wall -Werror

all: cp9
cp9: main.o vector.o sort.o
	$(CC) $(CFLAGS) -o cp9 main.o vector.o sort.o
main.o: main.c vector.h
	$(CC) $(CFLAGS) -c main.c
vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c
sort.o: sort.c vector.h
	$(CC) $(CFLAGS) -c sort.c
clean:
	rm -f cp9 *.o