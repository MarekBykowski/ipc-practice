.PHONY: all clean

CC      = gcc
CFLAGS  = -Wall

TARGETS = proc_a proc_b

all: $(TARGETS)

proc_a: proc_a.o
	$(CC) -o $@ $^ -lrt -lpthread   # -lrt for shm_open, -lpthread for sem_open

proc_b: proc_b.o
	$(CC) -o $@ $^ -lrt -lpthread

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<   # $@ = target (.o file), $< = first prerequisite (.c file)

clean:
	rm -f $(TARGETS) *.o
