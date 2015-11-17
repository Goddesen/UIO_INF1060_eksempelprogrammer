CC = gcc
CFLAGS = -Wall -Wextra -O2
BINARIES = client server

all: $(BINARIES)

%.o: %.c
	$(CC) $^ -c -o $@ $(CFLAGS)

client: client.o
	$(CC) $^ -o $@ $(CFLAGS)

server: server.o
	$(CC) $^ -o $@ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(BINARIES) *.o
