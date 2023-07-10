#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<unistd.h>
void main()
{
int pid1,pid,ppid;
pid1 = fork();
if(pid1==0)
{
	printf("Child process\n");
	printf("Child pid is %d\n",getpid());
	
	printf("Child ppid is %d\n",getppid());
	printf("\n");
	//system("ps -el");
	sleep(10);
	printf("Child pid is %d\n",getpid());
	printf("Child ppid is %d\n",getppid());
	printf("\n");
	system("ps -el");
	
	
	
}
if(pid1>0){
	sleep(5);
	printf("Parent process\n");
	printf("parent pid is %d\n",getpid());
	printf("Parent ppid is %d\n",getppid());
	printf("\n");	
}
}
