# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# define BufferSize 10

void *Producer();
void *Consumer();

int BufferIndex= -1;
char BUFFER[10];

pthread_cond_t  Buffer_Empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t  Buffer_Full =PTHREAD_COND_INITIALIZER;
pthread_mutex_t mVar=PTHREAD_MUTEX_INITIALIZER;

int main()
{    
pthread_t ptid,ctid;


pthread_create(&ptid,NULL,Producer,NULL);
pthread_create(&ctid,NULL,Consumer,NULL);

pthread_join(ptid,NULL);
pthread_join(ctid,NULL);

return 0;
}

void *Producer()
{    

    //do
int i;
for(i=0; i<15 ; i++)
    {
pthread_mutex_lock(&mVar);
if(BufferIndex==BufferSize-1)                       
pthread_cond_wait(&Buffer_Empty,&mVar);

BUFFER[++BufferIndex]='#';
printf("Produce : %d \n",BufferIndex);
pthread_mutex_unlock(&mVar);
pthread_cond_signal(&Buffer_Full);  
	
    }//while(1);    

}

void *Consumer()
{

    //do
int i;
for(i=0; i<15 ; i++)
    {
pthread_mutex_lock(&mVar);
if(BufferIndex==-1) {          
pthread_cond_wait(&Buffer_Full,&mVar);
}
printf("Consume : %d \n",BufferIndex--);        
pthread_mutex_unlock(&mVar);        
pthread_cond_signal(&Buffer_Empty);                
	
    }//while(1);
}

