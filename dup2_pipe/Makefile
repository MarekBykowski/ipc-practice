.PHONY: all clean

CC      = gcc
CFLAGS  = -Wall

TARGETS = dup2_pipe
OBJS    = main.o

all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) -o $@ $^   # $@ = target (dup2_pipe), $^ = all prerequisites (all .o files)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<   # $@ = target (.o file), $< = first prerequisite (.c file)

clean:
	rm -f $(TARGETS) $(OBJS)
