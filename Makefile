.PHONY: all clean

SUBDIRS = pipe fifo dup2_pipe socket shm sem_shm signals

all clean:
	for dir in $(SUBDIRS); do $(MAKE) -C $$dir $@; done
