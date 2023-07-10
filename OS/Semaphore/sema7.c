#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define readers 5
#define writers 2
int sharedData = 0;
sem_t rwMutex, mutex;
int readersCount = 0;
void *reader(void *arg)
{
int readerId = *(int *)arg;
while (1)
{
sem_wait(&mutex);
readersCount++;
if (readersCount == 1)
{
sem_wait(&rwMutex);
}
sem_post(&mutex);
printf("Reader %d reads shared data: %d\n", readerId, sharedData);
sem_wait(&mutex);
readersCount--;
if (readersCount == 0)
{
sem_post(&rwMutex);
}
sem_post(&mutex);
usleep(rand() % 1000000);
}
pthread_exit(NULL);
}
void *writer(void *arg)
{
int writerId = *(int *)arg;
while (1)
{
sem_wait(&rwMutex);
sharedData = writerId;
printf("Writer %d writes shared data: %d\n", writerId, sharedData);
sem_post(&rwMutex);
usleep(rand() % 1000000);
}
pthread_exit(NULL);
}
int main()
{
pthread_t readerThreads[readers];
pthread_t writerThreads[writers];
int readerIds[readers];
int writerIds[writers];
sem_init(&rwMutex, 0, 1);
sem_init(&mutex, 0, 1);
for (int i = 0; i < readers; i++)
{
readerIds[i] = i + 1;
pthread_create(&readerThreads[i], NULL, reader, &readerIds[i]);
}
for (int i = 0; i < writers; i++)
{
writerIds[i] = i + 1;
pthread_create(&writerThreads[i], NULL, writer, &writerIds[i]);
}
for (int i = 0; i < readers; i++)
{
pthread_join(readerThreads[i], NULL);
}
for (int i = 0; i < writers; i++)
{
pthread_join(writerThreads[i], NULL);
}
sem_destroy(&rwMutex);
sem_destroy(&mutex);
return 0;
}
