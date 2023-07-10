#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *producer(); 
void *consumer(); 

int main() {

pthread_t ptid, ctid; 
int n = 20;      
pthread_create(&ptid,NULL,producer,(void*)n);
pthread_create(&ctid,NULL,consumer,(void*)n);
pthread_join(ptid, NULL);
pthread_join(ctid, NULL);
     }


void *producer(void *param) {
int n = (int )param;
do{
printf("I m producer\n");
}while(n--);
pthread_exit(0);
}


void *consumer(void *param) {
int n = (int)param;
do{
printf("I m consumer\n");
}while(n--);
pthread_exit(0);
}

