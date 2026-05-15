.PHONY: all clean

CC      = gcc
CFLAGS  = -Wall

TARGETS = writer reader

all: $(TARGETS)

writer: writer.o
	$(CC) -o $@ $^ -lrt   # -lrt links the POSIX real-time library (needed for shm_open/shm_unlink)

reader: reader.o
	$(CC) -o $@ $^ -lrt

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<   # $@ = target (.o file), $< = first prerequisite (.c file)

clean:
	rm -f $(TARGETS) *.o
