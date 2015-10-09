CC = gcc
CFLAGS = -Wall -Wextra -O2
BINARIES = msgctl msgrcv msgsnd
all: $(BINARIES)

%.o: %.c
	$(CC) $^ -c -o $@ $(CFLAGS)

msgctl: msgctl.o
	$(CC) $^ -o $@ $(CFLAGS)

msgrcv: msgrcv.o msg.h
	$(CC) $^ -o $@ $(CFLAGS)

msgsnd: msgsnd.o msg.h
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f $(BINARIES) *.o
