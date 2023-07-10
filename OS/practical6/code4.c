#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
int main(){
	pid_t pid;
	int *shared;
	int shmid;
	shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
	printf("Shared Memory ID=%d\n", shmid);
	if ((pid = fork()) == 0){ 
		shared = shmat(shmid, (void *)0, 0);
		printf("Child pointer %p\n", shared);
		*shared = 1;
		printf("Child value=%d\n", *shared);
		sleep(2);
		printf("Child value=%d\n", *shared);
	}
	else if (pid > 0){
		shared = shmat(shmid, (void *)0, 0);
		printf("Parent pointer %p\n", shared);
		printf("Parent value=%d\n", *shared);
		sleep(1);
		*shared = 42;
		printf("Parent value=%d\n", *shared);
		sleep(5);
		shmctl(shmid, IPC_RMID, 0);
	}
	else{
		perror("fork");
		return 1;
	}
	return 0;
}
