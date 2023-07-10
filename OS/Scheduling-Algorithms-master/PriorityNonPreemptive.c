#include<stdio.h>
#include<stdlib.h>

typedef struct Process{
    int burst;
    int arrival;
    int priority;
    int tat;
    int wt;
}P;

void initialize(P* p,int b,int a,int pb){
    p->burst = b;
    p->arrival = a;
    p->priority = pb;
    p->tat = 0;
    p->wt = 0;
}

int main(){
    P parr[7];
    int done[7];

    for(int i=0;i<sizeof(parr)/sizeof(parr[0]);i++){
        done[i] = 0;
    }

    //setting Up Processes data :
    for(int i=0;i<sizeof(parr)/sizeof(parr[0]);i++){
        printf("Enter Burst , Arrival and Priority for process P%d :=> ",i);
        int b,a,pb;
        scanf("%d %d %d",&b,&a,&pb);
        initialize(&parr[i],b,a,pb);
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
    int x;
        total = arr[0].arrival+arr[0].burst;
        for(int i=0;i<n;i++){
            if(parr[i].arrival == arr[0].arrival && parr[i].priority == arr[0].priority){
                parr[0].tat = total-parr[0].arrival; 
                parr[0].wt = parr[0].tat-parr[0].burst;
                x =i;
            }
        }

    //Actual Logic:
    printf("Gantt Chart: \n");
    printf("P%d: 0-%d\t\t",x,total); 
    int pcount=0;
    while(pcount!=n-1){
        int hold=999;
        int idx;
        int prevProcess;

        for(int i=1;i<n;i++){
            if(done[i]!=1 && arr[i].arrival<=total){
                if(hold>arr[i].priority){
                    hold = arr[i].priority;
                    idx = i; prevProcess = i;
                }
            }
        }

        //Found Process 
        if(hold!=999){
            int dash = total;
            total+=arr[idx].burst;
            done[idx] = 1;
            pcount++;

            for(int i=0;i<n;i++){
                if(parr[i].arrival == arr[idx].arrival && parr[i].priority == arr[idx].priority){
                    parr[i].tat = total-parr[i].arrival; 
                    parr[i].wt = parr[i].tat-parr[i].burst;
                }
            }
            printf("P%d: %d-%d\t",idx,dash,total); 
            }else if(hold==999){
            //For Excess Time gap in Between
            int least=9999;
            for(int i=1;i<n;i++){
                if(i!=prevProcess && done[i]!=1 && arr[i].arrival<least){
                    least = arr[i].arrival;
                }
            }

            printf("%d\n",least);
            least = least-total;
            total += least;
        }

    }

    printf("\n\n%d\n",total);
    float avgTAT=0,avgWT=0;
    for(int i=0;i<n;i++){
        printf("for Process (%d) => TAT: %d\t, WT: %d\n",i,parr[i].tat,parr[i].wt);
        avgTAT+=parr[i].tat;
        avgWT+=parr[i].wt;
    }

    printf("\nAverage TAT: %.3f  and  Average WT: %.3f",avgTAT/n,avgWT/n);
  return 0;
}