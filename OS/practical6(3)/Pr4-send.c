#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct message {
    long mtype;
    int data;
};
void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
int main() {
    key_t key;
    int msgid;
    struct message msg;

    key = ftok(".", 'a');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    bubbleSort(arr, n);
    msg.mtype = 1;
    for (int i = 0; i < n; i++) {
        msg.data = arr[i];
        if (msgsnd(msgid, &msg, sizeof(msg.data), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
    }
    printf("Sorted array sent to receiver process.\n");
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }
    return 0;
}
