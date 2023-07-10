#include<stdio.h>
#include<stdlib.h>

typedef struct Process{
    int burst;
    int holdBurst;
    int arrival;
    int tat;
    int wt;
}P;

void initialize(P* p,int b,int a){
    p->burst = b;
    p->arrival = a;
    p->holdBurst = b;
    p->tat = 0;
    p->wt = 0;
}

int main(){
    P parr[5];
    int done[5];

    for(int i=0;i<sizeof(parr)/sizeof(parr[0]);i++){
        done[i] = 0;
    }

    //setting Up Processes data :
    for(int i=0;i<sizeof(parr)/sizeof(parr[0]);i++){
        printf("Enter Burst and Arrival for process P%d :=> ",i);
        int b,a;
        scanf("%d %d",&b,&a);
        initialize(&parr[i],b,a);
    }

   int total=0;
   int n = sizeof(parr)/sizeof(parr[0]);
   P arr[n];
   
   for(int i=0;i<n;i++){
    arr[i] = parr[i];
   }

   for(int i=0;i<n-1;i++){
    for(int j=0;j<n-i-1;j++){
        if(arr[j].arrival>arr[j+1].arrival){
            P temp = arr[j];
            arr[j] = arr[j+1];
            arr[j+1] = temp;
        }
    }
   }

    printf("\n");

    //Actual Logic:
    int lastArrival = 0;
    // int pcount=0;
    P* moving = &arr[0];
    int movingIDX=0;

    int toReach = arr[n-1].arrival;
    if(arr[0].arrival!=0){
        lastArrival+=arr[0].arrival;
        total+=arr[0].arrival;
    }

    while(lastArrival != toReach){

        if(lastArrival==0){
            moving->burst--;
            lastArrival++;
            total++;
        }else{
            for(int i=0;i<n;i++){
                if(done[i]!=1)
                if(lastArrival>=arr[i].arrival && moving->burst>arr[i].burst){
                    moving = &arr[i];
                    movingIDX = i;
                }
            }
            if(moving->burst!=0){
                moving->burst--;
                lastArrival++; total++;

                if(arr[movingIDX].burst==0){
                    done[movingIDX] = 1;
                    arr[movingIDX].tat = total-arr[movingIDX].arrival;
                    arr[movingIDX].wt = arr[movingIDX].tat-arr[movingIDX].holdBurst;
                    
                    //set new moving
                    P p;
                    initialize(&p,999,0);
                    moving = &p;
                    movingIDX=-1;
                    for(int i=0;i<n;i++){
                        if(done[i]!=1 && lastArrival>=arr[i].arrival){
                            if(moving->burst>arr[i].burst){
                                moving = &arr[i];
                                movingIDX = i;
                            }
                        }
                    }
                }
            }

        }


    }

    //Remaining bursts:
    int allDone = 1;
    while(allDone){
        //Setting up allDone:
        int finding=0;
        for(int i=0;i<n;i++){
            if(done[i]==1){
                finding++;
            }
        }
        if(finding==n){
            allDone=0;
            break;
        }

        P p;
        initialize(&p,999,0);
        moving = &p;
        movingIDX=-1;
        for(int i=0;i<n;i++){
            if(done[i]!=1 && lastArrival>=arr[i].arrival){
                if(moving->burst>arr[i].burst){
                    moving = &arr[i];
                    movingIDX = i;
                }
            }
        }

        total+=moving->burst;
        moving->burst=0;
        done[movingIDX]=1;
        arr[movingIDX].tat = total-arr[movingIDX].arrival;
        arr[movingIDX].wt = arr[movingIDX].tat-arr[movingIDX].holdBurst; 
       
    }


    printf("\n\n%d\n\n",total);
   float avgTAT=0,avgWT=0;
    for(int i=0;i<n;i++){
        avgTAT+=(float)arr[i].tat;
        printf("TAT: %d\t",arr[i].tat);
        avgWT+=(float)arr[i].wt;
        printf("WT: %d\n",arr[i].wt);

    }

    printf("\nAverage TAT: %.3f  and  Average WT: %.3f",avgTAT/n,avgWT/n);

  return 0;
}


