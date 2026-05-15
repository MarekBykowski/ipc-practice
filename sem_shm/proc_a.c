#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

/*
 * sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
 *   creates or opens a named semaphore
 *   value = 1 — binary semaphore (acts as a mutex): 1 = unlocked, 0 = locked
 *
 * int sem_wait(sem_t *sem);
 *   decrements the semaphore — if already 0, blocks until another process calls sem_post()
 *   this is the "lock" — only one process can be past this point at a time
 *
 * int sem_post(sem_t *sem);
 *   increments the semaphore — unblocks a waiting process if any
 *   this is the "unlock"
 *
 * int sem_close(sem_t *sem);
 *   closes the semaphore handle in this process (does not remove it)
 *
 * int sem_unlink(const char *name);
 *   removes the semaphore from the system — proc_a is responsible for cleanup
 */

#define SHM_NAME  "/race_shm"
#define SEM_NAME  "/race_sem"
#define ITERATIONS 100000

int main(void)
{
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0644);
    ftruncate(fd, sizeof(int));
    int *counter = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    *counter = 0;

    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0644, 1);

    printf("proc_a ready — run proc_b in another terminal, then press enter\n");
    getchar();

    for (int i = 0; i < ITERATIONS; i++) {
        sem_wait(sem);
        (*counter)++;
        sem_post(sem);
    }

    printf("proc_a done — final counter: %d (expected %d)\n", *counter, ITERATIONS * 2);

    munmap(counter, sizeof(int));
    sem_close(sem);
    shm_unlink(SHM_NAME);
    sem_unlink(SEM_NAME);

    return 0;
}
