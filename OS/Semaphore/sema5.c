#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
sem_t empty1, empty2, full1, full2;
void *PA(void *args)
{
int *a = (int *)args;
int val = 32;
for (int i = 0; i < 3; i++)
{
sem_wait(&empty1);
sem_wait(&empty2);
printf("Process A is writing into the buffer 1 : %d\n", val * i);
*a = val * i;
sem_post(&empty2);
sem_post(&full1);
}
}
void *PB(void *args)
{
int *a = (int *)args;
int copy;
for (int i = 0; i < 3; i++)
{
sem_wait(&full1);
copy = *a;
sem_post(&empty1);
sem_wait(&empty2);
printf("Process B is copting contents from buffer 1 to buffer 2 :%d\n", copy);
*a = copy;
sem_post(&full2);
}
}
void *PC(void *args)
{
int *a = (int *)args;
for (int i = 0; i < 3; i++)
{
sem_wait(&full2);
printf("Process C takes data from buffer 2 : %d\n", *a);
sem_post(&empty2);
}
}
int main()
{
key_t key;
key = 5678;
pthread_t TA, TB, TC;
int *a; // shared variable
int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
a = shmat(shmid, NULL, 0);
sem_init(&empty1, 0, 1);
sem_init(&empty2, 0, 1);
sem_init(&full1, 0, 0);
sem_init(&full2, 0, 0);
pthread_create(&TA, NULL, PA, a);
pthread_create(&TB, NULL, PB, a);
pthread_create(&TC, NULL, PC, a);
pthread_join(TA, NULL);
pthread_join(TB, NULL);
pthread_join(TC, NULL);
shmdt(a);
shmctl(shmid, IPC_RMID, NULL);
return 0;
}

