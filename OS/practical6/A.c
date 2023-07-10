#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
void main(){
	int count = 0,n;
	key_t key = ftok("inpfile",1);
	int shmid = shmget(key,10 * sizeof(int),IPC_CREAT | 0666);
	int *array = (int *)shmat(shmid,NULL,0);
	FILE *f = fopen("inpfile.txt","r");
	if(f == NULL){
		printf("File cannot be opened.\n");
		exit(1);
	}
	while(fscanf(f,"%d ",&n) == 1 && count < 10){
		array[count] = n;
		count++;
	}
	fclose(f);
	printf("Read %d integers from A.c\n",count);
	sleep(10);
	shmdt(array);
}
