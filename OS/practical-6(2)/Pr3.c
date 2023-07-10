#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define N 10
int main()
{
    int pipefd[2], n, pid;
    int buff[100];
    pipe(pipefd);
    pid = fork();
    if (pid == 0)
    {
        
        close(pipefd[0]);
        
        int a[N], sum;
        printf("The fibonacci series:\n");
        for(int i=0;i<N;i++){
            if(i==0)
                a[i] = 0;
            else if(i==1)
                a[i] = 1;
            else
                a[i]=a[i-1]+a[i-2];
            printf("%d ",a[i]);
        }
        printf("\n");
        write(pipefd[1], a, sizeof(a));
    }
    else
    {   
        
        close(pipefd[1]);
        n = read(pipefd[0], buff,N*4);

    
        int even[N], odd[N];
        int e=0, o=0;
        for(int i=0;i<N;i++){
            if(buff[i]%2==0){
                even[e]=buff[i];
                e++;
            }
            else{
                odd[o] = buff[i];
                o++;
            }
        }
        
        
        printf("\nEven Elements:\n");
        for(int i=0;i<e;i++)
            printf("%d ",even[i]);
        printf("\nOdd Elements:\n");
        for(int i=0;i<o;i++)
            printf("%d ",odd[i]);
    }
    return 0;
}

