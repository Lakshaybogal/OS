#include <stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	int s,pid_t,fr;
	fr =fork();
	if(fr == 0)
	{
		sleep(2);
		printf("Child\n");
		exit(0);
	}
	else
	{
		printf("Parent\n");
		wait(&s);
		printf("Im the parent!");
		if (WIFEXITED(s))
		printf("\n Child returned: %d\n", WEXITSTATUS(s));
		
	}
}
