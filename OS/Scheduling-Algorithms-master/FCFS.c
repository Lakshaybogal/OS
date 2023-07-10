#include<stdio.h>
#include<stdlib.h>

typedef struct Process{
    int burst;
    int arrival;
    int tat;
    int wt;
}P;

void initialize(P* p,int b,int a){
    p->burst = b;
    p->arrival = a;
    p->tat = 0;
    p->wt = 0;
}

int main(){
    P parr[3];
    int done[3];

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
   P pdash = parr[0];
   //finding first arrived process

   for(int i=1;i<n;i++){
        if(pdash.arrival>parr[i].arrival){
            pdash = parr[i];
        }
   }

   //processing on first arrived process:
   if(pdash.arrival!=0){
    total+=pdash.arrival;
   } 
   
   //finding smallest
   printf("\n\nGantt Chart:\n");
   int pcount=0;
   while(pcount!=n){
    initialize(&pdash,0,999);
    int idx = -1;
        for(int i=0;i<n;i++){
            if(pdash.arrival>parr[i].arrival && done[i]!=1){
                pdash = parr[i];
                idx = i;
            }
        }
        //got arrived process
        if(idx!=-1){
            int old = total;
            total+=pdash.burst;

            parr[idx].tat = total-parr[idx].arrival;
            parr[idx].wt = parr[idx].tat-parr[idx].burst;
            
            done[idx]=1;
            printf("P%d-> %d-%d\t\t",idx,old,total);
        }
        pcount++;

   }

    printf("\n\n");
    int totTAT=0,totWT=0;
    for(int i=0;i<n;i++){
        printf("P%d => TAT:%d and WT:%d \t",i,parr[i].tat,parr[i].wt);
        totTAT+=parr[i].tat; totWT+=parr[i].wt;
    }

    printf("\nAverage TAT: %.3f\n",(float)totTAT/n);
    printf("Average WT: %.3f",(float)totWT/n);

}
