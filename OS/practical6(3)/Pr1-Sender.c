#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX_TEXT 512
 
struct my_msg_st
{
    	long int my_msg_type;
    	char some_text[MAX_TEXT];
};
 
int main()
{
        	int running = 1;
        	int msgid;
        	char sender[3] = "end";
        	struct my_msg_st some_data;
        	char buffer[BUFSIZ];
        	system("clear");
        	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
        	if (msgid == -1)
        	{
        	  fprintf(stderr,"msgget failed with error : %d", errno);
        	  exit(EXIT_FAILURE);
        	}
 
 while(running)
 {
		printf("Enter some text : ");
		fgets(buffer, BUFSIZ, stdin);
        	if (strncmp(buffer, sender,3) == 0 )
        	{ running = 0; }
		printf("Text sent : %s ", buffer);
		some_data.my_msg_type = 1;
		strcpy(some_data.some_text, buffer);
        	if (msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1)
        	{

        	fprintf(stderr,"msgsnd failed ");
        	  exit(EXIT_FAILURE);
        	}
 
}       	
        	exit(EXIT_SUCCESS);
}
 
