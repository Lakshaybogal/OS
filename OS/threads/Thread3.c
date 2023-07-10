#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define size 3
int A[size][size] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
int B[size][size] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int C[size][size];
typedef struct
{
int row;
int col;
} m;
void *mult(void *args)
{
m *index = (m *)args;
int r = index->row;
int c = index->col;
for (int i = 0; i < size; i++)
{
C[r][c] += A[r][i] * B[i][c];
}
}
int main()
{
pthread_t t[size][size];
printf("A matrix :\n");
for (int i = 0; i < size; i++)
{
for (int j = 0; j < size; j++)
{
printf("%d ", A[i][j]);
}
printf("\n");
}
printf("B matrix :\n");
for (int i = 0; i < size; i++)
{
for (int j = 0; j < size; j++)
{
printf("%d ", B[i][j]);
}
printf("\n");
}
for (int i = 0; i < size; i++)
{
for (int j = 0; j < size; j++)
{
m *index = (m *)malloc(sizeof(m));
index->row = i;
index->col = j;
pthread_create(&t[i][j], NULL, mult, (void *)index);
}
}
for (int i = 0; i < size; i++)
{
for (int j = 0; j < size; j++)
{
pthread_join(t[i][j], NULL);
}
}
printf("Answer of Multiplication :\n");
for (int i = 0; i < size; i++)
{
for (int j = 0; j < size; j++)
{
printf("%d ", C[i][j]);
}
printf("\n");
}
}
