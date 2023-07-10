#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	
	int pid = fork();
	printf("Jai Shree Ram\n");
	if(pid<0)
	{	printf("Fail\n");
		printf("Process Id : %d\n",getpid());
		}
	else if(pid==0)
	{
		printf("child\n");
		printf("Process Id : %d\n",getpid());
		}
	else
	{
		printf("parent\n");
		printf("Process Id : %d\n",getpid());
		}
	return 0;
}
