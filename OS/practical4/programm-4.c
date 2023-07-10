#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void main()
{
int pid1,pid,ppid;
pid1 =fork();
if(pid1>0)
{
printf("I am parent process \n");
printf("parent pid is %d\n",getpid());
printf("parent's ppid is %d\n",getppid());
printf("\n");
sleep(10);
printf("Hello\n");
}
else if(pid1==0){
sleep(5);
printf("Child\n");
}
}
