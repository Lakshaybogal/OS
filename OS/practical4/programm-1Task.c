#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	
	int pid = fork();
	printf("Started\n");
	if(pid<0)
	{	
		
		printf("Fail\n");
		printf("Process Id : %d\n",getpid());
		}
	else if(pid==0)
	{	
		sleep(5);
		printf("Child\n");
		printf("Process Id : %d\n",getpid());
		int n;
		printf("Enter Number to check\n");
		scanf("%d",&n);
		sleep(5);
		if(n%2!=0)
		{
			printf("Odd\n");
		}
		else
		{
			printf("Even\n");
		}
		}
	else
	{
		
		printf("Parent\n");
		printf("Process Id : %d\n",getpid());
		int n;
		printf("Enter Number to check\n");
		scanf("%d",&n);
		sleep(5);
		if(n%2==0)
		{
			printf("Even\n");
		}
		else
		{
		printf("Odd\n");
		}
		}
		printf("\n");
	
	return 0;
}
