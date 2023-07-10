#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <math.h>

struct message {
    long mtype;
    int data;
};

int main() {
    key_t key;
    int msgid;
    struct message msg;
    
    key = ftok(".", 'a');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }
    
    msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Received array from sender process:\n");
    while (msgrcv(msgid, &msg, sizeof(msg.data), 1, IPC_NOWAIT) != -1) {
        printf("%d ", msg.data);
        int square = msg.data * msg.data;
        printf("Square: %d\n", square);
    }
    
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }
    
    return 0;
}

