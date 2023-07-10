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
	for(int i=0;i<30;i++)
	{
		printf("%d\n",i);
		sleep(1);
		//system("ps -el");
	}
	exit(0);
	
}
else{
	//wait(0);
	//sleep(10);
	printf("Parent process\n");
	wait(0);
	sleep(10);
	printf("Parent process\n");
	//wait(0);
	printf("\n");	
}
}
