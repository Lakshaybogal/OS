
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
void main()
{
int pid1, pid, ppid;
pid1 = fork();
if (pid1 == 0)
{
printf("I am child process \n");
printf("child pid is %d\n", getpid());
printf("child ppid is %d\n", getppid());
printf("\n");
//system("ps -el");
sleep(5);
printf("now child pid is %d\n", getpid());
printf("now child ppid is %d\n", getppid());
//system("ps -el");
}
if (pid1 > 0)
{
sleep(2);
printf("I am parent process \n");
printf("parent pid is %d\n", getpid());
printf("parent's ppid is %d\n", getppid());
printf("\n");
}
}
