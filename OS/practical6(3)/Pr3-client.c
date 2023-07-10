#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


struct mesgq
{
long type;
char text[200];
} mq;


main()
{
int msqid, len;
key_t key = 2016;
if ((msqid = msgget(key, 0644)) == -1)
{
printf("Server not active\n");
exit(1);
}
printf("Client ready :\n");
while (msgrcv(msqid, &mq, sizeof(mq.text), 1, 0) != -1)
{
printf("From Server: \"%s\"\n", mq.text);
fgets(mq.text, sizeof(mq.text),stdin);
len = strlen(mq.text);
if (mq.text[len-1] == '\n')
mq.text[len-1] = '\0';
msgsnd(msqid, &mq, len+1, 0);
}
printf("Server Disconnected\n");
}
