.PHONY: all clean

CC      = gcc
CFLAGS  = -Wall

TARGETS = receiver sender

all: $(TARGETS)

receiver: receiver.o
	$(CC) -o $@ $^   # $@ = target (receiver), $^ = all prerequisites (all .o files)

sender: sender.o
	$(CC) -o $@ $^   # $@ = target (sender), $^ = all prerequisites (all .o files)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<   # $@ = target (.o file), $< = first prerequisite (.c file)

clean:
	rm -f $(TARGETS) *.o
