CC = gcc
CFLAGS = -Wall -Wextra -O2
BINARIES = testfork testfork2
all: $(BINARIES)

%.o: %.c
	$(CC) $^ -c -o $@ $(CFLAGS)

testfork: testfork.o
	$(CC) $^ -o $@ $(CFLAGS)

testfork2: testfork2.o
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f $(BINARIES) *.o
