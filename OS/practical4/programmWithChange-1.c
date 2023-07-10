#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int findmax(int *A, int L, int R)
{
int max = A[L];
for (int i = L + 1; i <= R; i++)
{
if (A[i] > max)
{
max = A[i];
}
}
return max;
}
void process(int *A, int L, int R)
{
if (R - L + 1 < 10)
{
int max = findmax(A, L, R);
printf("Process Id : %d (Parent Process Id : %d) - Max: %d\n",
getpid(), getppid(), max);
exit(max);
}
else
{
int M = (L + R) / 2;
int left_child, right_child;
int left_status, right_status;
left_child = fork();
if (left_child == 0)
{
process(A, L, M);
}
else
{
right_child = fork();
if (right_child == 0)
{
process(A, M + 1, R);
}
else
{
waitpid(left_child, &left_status, 0);
waitpid(right_child, &right_status, 0);
int max_l = WEXITSTATUS(left_status);
int max_r = WEXITSTATUS(right_status);
int max;
if (max_l > max_r)
max = max_l;
else
printf("Process Id : %d (Parent Process Id : %d) - Max:
%d\n", getpid(), getppid(), max);
exit(max);
}
}
}
}
void main()
{
int n = 50;
int A[n];
printf("Array is : \n");
for (int i = 0; i < n; i++)
{
A[i] = rand() % 128;
printf("%d ", A[i]);
}
printf("\n");
process(A, 0, n - 1);
}

