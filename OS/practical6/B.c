#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
void sort(int A[], int m){
	int temp;
	for (int i = 0; i < m; i++){
		for (int j = i + 1; j < m; j++){
			if (A[j] < A[i]){
				temp = A[i];
				A[i] = A[j];
				A[j] = temp;
			}
		}
	}
}
void main(){
	int count = 0;
	key_t key = ftok("inpfile", 1);
	int shmid = shmget(key, 10 * sizeof(int), IPC_CREAT | 0666);
	int *array = (int *)shmat(shmid, NULL, 0);
	while (array[count] != 0 && count < 10) count++;
	sort(array, count);
	FILE *f = fopen("outfile.txt", "w");
	if (f == NULL){
		printf("File cannot be opened.\n");
		exit(1);
	}
	for (int i = 0; i < count; i++) fprintf(f, "%d ", array[i]);
	fclose(f);
	printf("Sorted %d integers from B.c\n", count);

	shmdt(array);
	shmctl(shmid, IPC_RMID, NULL);
}
