#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int arrival;
    int burst, holdBurst;
    int tat, wt;
} P;

typedef struct Node {
    P p;
    struct Node* next;
} Node;

void initializeProcess(P* p, int b, int a) {
    p->arrival = a;
    p->burst = b;
    p->holdBurst = b;
}

void initializeNode(Node* newNode, P* p) {
    newNode->p = *p;
    newNode->next = NULL;
}

void addNode(Node** head, P* p) {
    Node* new = (Node*)malloc(sizeof(Node));
    if (new == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    initializeNode(new, p);

    if (*head == NULL) {
        *head = new;
    }
    else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new;
    }
}

Node* removeNode(Node** head) {
    if (*head == NULL) {
        printf("Queue is empty.\n");
        return NULL;
    }
    Node* temp = *head;
    *head = temp->next;
    temp->next = NULL;
    return temp;
}

void display(Node** head) {
    Node* temp = *head;
    if (temp == NULL) {
        return;
    }
    while (temp != NULL) {
        printf("%d %d\n", temp->p.burst, temp->p.arrival);
        temp = temp->next;
    }
}

int main() {
    Node* head = NULL;

    P parr[4];
    int done[4];
    int quantum = 0;
    int n = sizeof(parr) / sizeof(parr[0]);
    printf("Enter Time Quantum for Round Robin: ");
    scanf("%d", &quantum);
    printf("\n");

    for (int i = 0; i < sizeof(parr) / sizeof(parr[0]); i++) {
        done[i] = 0;
    }

    // Setting up Processes data:
    for (int i = 0; i < sizeof(parr) / sizeof(parr[0]); i++) {
        printf("Enter Burst and Arrival for process P%d :=> ", i);
        int b, a;
        scanf("%d %d", &b, &a);
        initializeProcess(&parr[i], b, a);
    }

    P arr[n];
    for(int i=0;i<n;i++){
        arr[i] = parr[i];
    }

    //finding First Arrived and adding it to Ready Queue:
       for(int i=0;i<n-1;i++){
            for(int j=0;j<n-i-1;j++){
                if(arr[j].arrival>arr[j+1].arrival){
                    P temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
    }

    int total = 0,pcount=0;
    total+=arr[0].arrival;
    addNode(&head,&arr[0]);
    printf("\n\n");

    while(pcount!=n){
        Node* moving = removeNode(&head);
        int Idx;
        for(int i=0;i<n;i++){
            if(moving->p.arrival==arr[i].arrival && moving->p.holdBurst==arr[i].holdBurst){
                Idx = i;
            }
        }

        if(quantum>=moving->p.burst){
            int old = total;
            total+=moving->p.burst;
            moving->p.burst=0;
            done[Idx] = 1;

            //Finding In actual array
            int duplicateIdx;
            for(int i=0;i<n;i++){
            if(parr[i].arrival==arr[Idx].arrival && parr[i].holdBurst==arr[Idx].holdBurst){
                duplicateIdx = i;
            }
            }

            printf("P%d = %d-%d\t\t",duplicateIdx,old,total);


            arr[Idx].tat = total-arr[Idx].arrival;
            arr[Idx].wt = arr[Idx].tat - arr[Idx].holdBurst;

            pcount++;
            for(int i=0;i<n;i++){
                    if(arr[i].arrival<=total && arr[i].arrival>old && done[i]!=1 && i!=Idx){
                        addNode(&head,&arr[i]);
                    }
                }
        }else{
            int old = total;
            total+=quantum;
            moving->p.burst-=quantum;

            int duplicateIdx;
            for(int i=0;i<n;i++){
            if(parr[i].arrival==arr[Idx].arrival && parr[i].holdBurst==arr[Idx].holdBurst){
                duplicateIdx = i;
            }
            }
            printf("P%d = %d-%d\t\t",duplicateIdx,old,total);

            // if(){
                for(int i=0;i<n;i++){
                    if(arr[i].arrival<=total && arr[i].arrival>old && done[i]!=1 && i!=Idx){
                        addNode(&head,&arr[i]);
                    }
                }
            // }

            if(moving->p.burst!=0){
                addNode(&head,&moving->p);
            }else if(moving->p.burst==0){
                pcount++;
                done[Idx] = 1;

                arr[Idx].tat = total-arr[Idx].arrival;
                arr[Idx].wt = arr[Idx].tat - arr[Idx].holdBurst;
            }
            
        }
    }


printf("\n\nANSWER: %d\n\n",total);

int avgTAT=0,avgWT=0;
for(int i=0;i<n;i++){
    printf("%d %d\t\t",arr[i].tat,arr[i].wt);
    avgTAT+=arr[i].tat;
    avgWT+=arr[i].wt;
}

printf("\n\nTAT average:%.3f\t WT average: %.3f",(float)avgTAT/n,(float)avgWT/n);




    return 0;
}


