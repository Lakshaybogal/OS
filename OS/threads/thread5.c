#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define size 100
#define thread_max 10
int a[size];
int max = -9999;
int min = 9999;
void *find(void *args)
{
int tid = (int *)args;
int subarray_size = size / thread_max;
int s_index = tid * subarray_size;
int e_index = s_index + subarray_size;
int MAX = -9999;
int MIN = 9999;
for (int i = s_index; i < e_index; i++)
{
if (a[i] > MAX)
MAX = a[i];
else if (a[i] < MIN)
MIN = a[i];
}
if (MAX > max)
max = MAX;
if (MIN < min)
min = MIN;
pthread_exit(NULL);
}
int main()
{
pthread_t t[thread_max];
for (int i = 0; i < size; i++)
{
a[i] = rand() % 1000;
}
for (int i = 0; i < thread_max; i++)
{
pthread_create(&t[i], NULL, find, i);
}
for (int i = 0; i < thread_max; i++)
{
pthread_join(t[i], NULL);
}
printf("Maximum Number of the array is %d\n", max);
printf("Minimum Number of the array is %d\n", min);
}
