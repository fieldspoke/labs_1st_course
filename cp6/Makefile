CC = gcc
CFLAGS = -g -std=c99 -w -pipe -O3

all: generate print task

generate: io.o generate.o
	$(CC) $^ -o $@

print:    io.o print.o
	$(CC) $^ -o $@

task:  io.o task.o
	$(CC) $^ -o $@

clean:
	rm -f *.o

cleanall:
	rm -f generate print task *.o

