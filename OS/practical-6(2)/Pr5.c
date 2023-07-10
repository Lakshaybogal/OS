#include<stdio.h>
 #include<stdlib.h> 
main() 
{
 int p1[2],p2[2],n,pid;
 char buf1[25],buf2[25];
 pipe(p1); 
pipe(p2);
 printf("\n readfds=%d %d\n",p1[0],p2[0]);
 printf("\n writefds=%d %d\n",p1[1],p2[1]);
 pid=fork();
 if(pid==0)
 {
 close(p1[0]); 
printf("\n CHILD PROCESS SENDING DATA\n");
 write(p1[1],"where is GEC",25);
 close(p2[1]); 
read(p2[0],buf1,25);
 printf(" reply from parent:%s\n",buf1); 
sleep(2);
 } 
else
 {
 close(p1[1]); 
printf("\n parent process receiving data\n"); 
n=read(p1[0],buf2,sizeof(buf2));
 printf("\n data received from child through pipe:%s\n",buf2);
 sleep(3);
 close(p2[0]); 
write(p2[1]," in gudlavalleru",25);
 printf("\n reply send\n"); 
}}
