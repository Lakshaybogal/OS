#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#define readers 5
#define writers 2
typedef struct
{
int sharedData;
sem_t rwMutex;
sem_t mutex;
int readersCount;
} SharedMemory;
void readerProcess(SharedMemory *sharedMemory, int readerId)
{
while (1)
{
sem_wait(&(sharedMemory->mutex));
sharedMemory->readersCount++;
if (sharedMemory->readersCount == 1)
{
sem_wait(&(sharedMemory->rwMutex));
}
sem_post(&(sharedMemory->mutex));
printf("Reader %d reads shared data: %d\n", readerId, sharedMemory->sharedData);
sem_wait(&(sharedMemory->mutex));
sharedMemory->readersCount--;
if (sharedMemory->readersCount == 0)
{
sem_post(&(sharedMemory->rwMutex));
}
sem_post(&(sharedMemory->mutex));
usleep(rand() % 1000000);
}
}
void writerProcess(SharedMemory *sharedMemory, int writerId)
{
while (1)
{
sem_wait(&(sharedMemory->rwMutex));
sharedMemory->sharedData = writerId;
printf("Writer %d writes shared data: %d\n", writerId, sharedMemory->sharedData);
sem_post(&(sharedMemory->rwMutex));
usleep(rand() % 1000000);
}
}
int main()
{
int shmid;
SharedMemory *sharedMemory;
shmid = shmget(IPC_PRIVATE, sizeof(SharedMemory), IPC_CREAT | 0666);
sharedMemory = (SharedMemory *)shmat(shmid, NULL, 0);
sharedMemory->sharedData = 0;
sem_init(&(sharedMemory->rwMutex), 1, 1);
sem_init(&(sharedMemory->mutex), 1, 1);
sharedMemory->readersCount = 0;
for (int i = 0; i < readers; i++)
{
pid_t pid = fork();
if (pid < 0)
{
perror("fork error");
exit(1);
}
else if (pid == 0)
{
readerProcess(sharedMemory, i + 1);
exit(0);
}
}
for (int i = 0; i < writers; i++)
{
pid_t pid = fork();
if (pid < 0)
{
perror("fork error");
exit(1);
}
else if (pid == 0)
{
writerProcess(sharedMemory, i + 1);
exit(0);
}
}
for (int i = 0; i < readers + writers; i++)
{
wait(NULL);
}
shmdt(sharedMemory);
shmctl(shmid, IPC_RMID, NULL);
return 0;
}

