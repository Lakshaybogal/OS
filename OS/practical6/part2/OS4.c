#include<stdio.h>
#include<stdlib.h>
main()
{
int pipefd[2],n,pid;
char buff[100];
pipe(pipefd);
printf("\n readfd=%d\n",pipefd[0]);
printf("\n writefd=%d\n",pipefd[1]);
pid=fork();
if(pid==0)
{
close(pipefd[0]);
printf("\n CHILD PROCESS SENDING DATA\n");
write(pipefd[1],"\nhello world\n",12);
}
else
{
close(pipefd[1]);
printf("PARENT PROCESS RECEIVES DATA\n");
n=read(pipefd[0],buff,sizeof(buff));
printf("\n size of data%d",n);
printf("\n data received from child throughpipe:%s\n",buff);

}
}
