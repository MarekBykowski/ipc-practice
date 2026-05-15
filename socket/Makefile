.PHONY: all clean

CC      = gcc
CFLAGS  = -Wall

TARGETS = server client

all: $(TARGETS)

server: server.o
	$(CC) -o $@ $^   # $@ = target (server), $^ = all prerequisites (all .o files)

client: client.o
	$(CC) -o $@ $^   # $@ = target (client), $^ = all prerequisites (all .o files)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<   # $@ = target (.o file), $< = first prerequisite (.c file)

clean:
	rm -f $(TARGETS) *.o
