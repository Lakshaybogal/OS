
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
void main(){
int pid1,i;
pid1 =fork();
if(pid1==0)
{
printf("I am child process \n");
for(i=0;i<10;i++){
printf("%d\n",i);
sleep(1);

}
exit(0);
}
else{
wait(0);
sleep(5);
printf("I am parent process\n");
wait(0);
sleep(5);
printf("I am parent process\n");
}
}

