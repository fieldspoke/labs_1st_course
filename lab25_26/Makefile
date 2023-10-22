CC = gcc
CFLAGS = -std=c99 -Wall -Werror
DEBUG = gdb
FILEOUT = deque.out
SOURCES = deque.c main.c

all:
	$(CC) $(CFLAGS) $(SOURCES)  -o $(FILEOUT)
clean:
	rm -f *.out
debug:
	$(CC) $(CFLAGS) -g $(SOURCES)
	sudo $(DEBUG) $(FILEOUT)
cmp:
	$(CC) $(CFLAGS) $(SOURCES) -o $(FILEOUT)
run:
	./$(FILEOUT)