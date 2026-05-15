.PHONY: all clean

CC      = gcc
CFLAGS  = -Wall

TARGETS = fifo_hello
OBJS    = main.o writer.o reader.o

all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) -o $@ $^   # $@ = target (fifo_hello), $^ = all prerequisites (all .o files)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<   # $@ = target (.o file), $< = first prerequisite (.c file)

clean:
	rm -f $(TARGETS) $(OBJS)
