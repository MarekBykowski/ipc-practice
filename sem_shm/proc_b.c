#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

/*
 * sem_open without O_CREAT — opens an existing semaphore created by proc_a
 * proc_b does not create or clean up — it just uses what proc_a set up
 *
 * sem_wait / sem_post — same lock/unlock as proc_a
 * without these, both processes would read-modify-write counter simultaneously:
 *   proc_a reads counter = 5
 *   proc_b reads counter = 5   (before proc_a wrote back)
 *   proc_a writes counter = 6
 *   proc_b writes counter = 6  (increment lost — should be 7)
 * semaphore prevents this by allowing only one process at a time into the critical section
 */

#define SHM_NAME  "/race_shm"
#define SEM_NAME  "/race_sem"
#define ITERATIONS 100000

int main(void)
{
    int fd = shm_open(SHM_NAME, O_RDWR, 0);
    int *counter = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    sem_t *sem = sem_open(SEM_NAME, 0);

    for (int i = 0; i < ITERATIONS; i++) {
        sem_wait(sem);
        (*counter)++;
        sem_post(sem);
    }

    printf("proc_b done — counter so far: %d\n", *counter);

    munmap(counter, sizeof(int));
    sem_close(sem);

    return 0;
}
