CC = gcc
CFLAGS = -Wall -Wextra -O2
LIBRARY_OUT = safefork.a safefork-cyg.a safefork-linux.a safefork-unix.a

all: $(LIBRARY_OUT)

%.a: %.o
	ar rcs $@ $<

%.o: %.c
	$(CC) $^ -c -o $@ $(CFLAGS)

clean:
	rm -f $(LIBRARY_OUT) *.o
