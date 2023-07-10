#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define max 20
#define thread_max 4
int a[max] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
19, 20};
int key = 15;
int flag = 0, i;
int current_thread = 0;
void *LinearSearch(void *args)
{
int num = current_thread++;
for (num *(max / 4); i < ((num + 1) * (max / 4)); i++)
{
if (a[i] == key)
flag = 1;
}
}
int main()
{
pthread_t thread[thread_max];
for (int i = 0; i < thread_max; i++)
pthread_create(&thread[i], NULL, LinearSearch, (void *)NULL);
for (int i = 0; i < thread_max; i++)
pthread_join(thread[i], NULL);
if (flag == 1)
printf("Element found (%d)\n", key);
else
printf("Element not present(%d)\n", key);
}

