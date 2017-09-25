.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g -std=c99 -O0
BIN=deque
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
deque:deque.o test.o
	$(CC) $(CFLAGS) $^ -o $@
clean:
	rm -f *.o $(BIN)