#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
# include <stdlib.h>
int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
typedef struct{
	int min;
	int max;
} find;
void main(){
	int N;
	find *ans;
	pid_t pid;
	int segment_id = shmget(IPC_PRIVATE, sizeof(find), IPC_CREAT | 0666);
	ans = (find *)shmat(segment_id, NULL, 0);
	
	ans->min = A[0];
	ans->max = A[0];
	pid = fork();
	if (pid == 0){
	// Child Process which finds minimum
		for (int i = 1; i < 20; i++){
			if (A[i] < ans->min)
			ans->min = A[i];
		}
		exit(0);
	}
	else{
		for (int i = 1; i < 20; i++){
			if (A[i] > ans->max) ans->max = A[i];
		}
		wait(NULL);
		}
		printf("Minimum Element in the array is %d\n\n", ans->min);
		printf("Maximum Element in the array is %d\n\n", ans->max);
}		
