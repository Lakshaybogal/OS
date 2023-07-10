#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	
	int pid = fork();
	if(pid<0)
		printf("Fail\n");
	else if(pid==0)
		printf("child\n");
	else
		printf("parent\n");
	return 0;
}
