#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

#define SHM_KEY 12345

int main() {
    int shmid;
    int *shared_var;
    sem_t *semaphore;

    // Create shared memory segment
    shmid = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory segment
    shared_var = (int *)shmat(shmid, NULL, 0);
    if (shared_var == (int *)-1) {
        perror("shmat");
        exit(1);
    }

    // Create semaphore
    semaphore = (sem_t *)shmat(shmid, NULL, 0);
    if (semaphore == (sem_t *)-1) {
        perror("shmat");
        exit(1);
    }
    if (sem_init(semaphore, 1, 1) == -1) {
        perror("sem_init");
        exit(1);
    }

    // Initialize shared variable
    *shared_var = 0;

    // Fork two processes
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process
        for (int i = 0; i < 1000; i++) {
            sem_wait(semaphore);
            *shared_var += 1;
            sem_post(semaphore);
        }
        exit(0);
    } else {
        // Parent process
        for (int i = 0; i < 1000; i++) {
            sem_wait(semaphore);
            *shared_var += 1;
            sem_post(semaphore);
        }

        // Wait for child process to finish
        wait(NULL);

        // Print the final value of the shared variable
        printf("Final value of shared variable: %d\n", *shared_var);

        // Detach shared memory
        shmdt(shared_var);

        // Remove shared memory segment
        shmctl(shmid, IPC_RMID, NULL);

        // Destroy semaphore
        sem_destroy(semaphore);
    }

    return 0;
}
