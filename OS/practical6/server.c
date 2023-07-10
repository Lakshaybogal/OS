#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define SHMSZ 27
void main(){
	char c;
	int shmid;
	key_t key;
	char *shm, *s;
	key = 5678;
	if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0){
		perror("shmget");
		exit(1);
	}
	if ((shm = shmat(shmid, NULL, 0)) == (char *)-1){
		perror("shmat");
		exit(1);
	}
	s = shm;
	for (c = 'a'; c <= 'z'; c++) *s++ = c;
	*s = '\0';
	while (*shm != '*') sleep(1);
	if (shmdt(shm) == -1){
		perror("shmdt");
		exit(1);
	}
	if (shmctl(shmid, IPC_RMID, 0) == -1){
		perror("shmctl");
		exit(1);
	}
	exit(0);
}
