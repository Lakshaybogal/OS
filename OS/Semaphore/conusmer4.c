
#include "sema4.h"
void consumer()
{
int n;
MEM *S = memory();
while (1)
{
sem_wait(&S->full); // Semaphore down operation
sem_wait(&S->mutex); // Semaphore for mutual exclusion
sem_getvalue(&S->full, &n); // Assign value of semaphore full to

printf("[CONSUMER] Removed item [%d]\n", S->buff[n]);
sem_post(&S->mutex); // Mutex up operation
sem_post(&S->empty); // Semaphore up operation
sleep(CONSUMER_SLEEP_SEC);
}
}
int main()
{
consumer();
return 0;
}
