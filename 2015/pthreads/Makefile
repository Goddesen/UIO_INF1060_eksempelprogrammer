CC = gcc
LIBS = -lpthread
CFLAGS = -Wall -Wextra -O2
BINARIES = pthread_hello

all: $(BINARIES)

%.o: %.c
	$(CC) $^ -c -o $@ $(CFLAGS)

pthread_hello: pthread_hello.o
	$(CC) $^ -o $@ $(CFLAGS) $(LIBS)

clean:
	rm -f $(BINARIES) *.o
