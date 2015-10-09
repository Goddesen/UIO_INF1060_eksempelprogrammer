CC = gcc
CFLAGS = -Wall -Wextra -O2
all: client server

%.o: %.c
	$(CC) $^ -c -o $@ $(CFLAGS)

client: client.o
	$(CC) $^ -o $@ $(CFLAGS)

server: server.o
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f client server
