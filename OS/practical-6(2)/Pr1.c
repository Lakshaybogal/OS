
#include <unistd.h>
///#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>

	int main()
	{
		int pid, pip[2];
		char instring[20];
		pipe(pip); 
		pid = fork();
		if (pid == 0)          
		{	
		write(pip[1], "Hi Lakshay!", 7);  
		}
		else			
		{
		read(pip[0], instring, 7);
		}
}

