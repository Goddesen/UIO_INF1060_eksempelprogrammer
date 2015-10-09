CC = gcc
CFLAGS = -Wall -Wextra -O2
BINARIES = pipe

all: $(BINARIES)

%.o: %.c
	$(CC) $^ -c -o $@ $(CFLAGS)

pipe: pipe.o
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f $(BINARIES) *.o
