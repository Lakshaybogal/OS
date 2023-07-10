#include<stdio.h>
#include<unistd.h>
int main()
{
pid_t p;
/* create child process */
p=fork();
if(p==0){
/* fork() returns Zero to child */
sleep(5);
}
printf("The child process PID is %d\nAnd Parent PID is %d\n\n", getpid(),
getppid());
/* parent/child waits for 20 secs and exits */
sleep(10);
printf("Process %d is done its Parent pid %d...\n", getpid(), getppid());
return 0;
}
