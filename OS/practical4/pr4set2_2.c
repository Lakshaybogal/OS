#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<unistd.h>
void main()
{
int pid1,pid,ppid;
pid1 = fork();
if(pid1==0)

if(pid1>0){
	
	printf("Parent process\n");
	printf("parent pid is %d\n",getpid());
	printf("Parent ppid is %d\n",getppid());
	printf("\n");
	sleep(50);	
}
}
