.PHONY: all clean

CC      = gcc
CFLAGS  = -Wall

TARGETS = pipe_hello
OBJS    = main.o parent.o child.o

all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) -o $@ $^   # $@ = target (pipe_hello), $^ = all prerequisites (all .o files)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<   # $@ = target (.o file), $< = first prerequisite (.c file)

clean:
	rm -f $(TARGETS) $(OBJS)
