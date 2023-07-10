#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
int D_score = 0;
int C_score = 0;
int main(){
    int p1[2], p2[2];
    int r1 = pipe(p1);
    int r2 = pipe(p2);
    int c, d, num1, num2;
    if (r1 == -1 || r2 == -1) {
        printf("Pipe Failed !!\n");
        exit(1);
    }
    int a, b;
    a = fork();
    if (a == -1)
    {
        printf("Fork Failed.\n");
        exit(1);
    }
    else if (a == 0)
    {
        printf("Child Process C.\n");
        close(p1[0]);
        close(p2[1]);
        srand(time(NULL));
        while (C_score < 10){
            num1 = rand() % 100 + 1;
            write(p1[1], &num1, sizeof(int));
        }
        close(p1[1]);
    }
    b = fork();
    if (b == -1){
        printf("Fork Failed.\n");
        exit(1);
    }
    else if (b == 0){
        printf("Child Process D.\n");
        close(p1[1]);
        close(p2[0]);
        sleep(1);
        srand(time(NULL));
        while (D_score < 10){
            num2 = rand() % 100 + 1;
            write(p2[1], &num2, sizeof(int));
        }
        close(p2[1]);
    }
    close(p1[1]);
    close(p2[1]);
    int round_no = 1;
    srand(time(NULL));
    while (C_score < 10 && D_score < 10){
        int choice = rand() % 2;
        printf("Round Number : %d\n", round_no);
        if (choice == 0) printf("Parent Process chose MIN\n");     
        else printf("Parent Process chose MAX\n");     
        read(p1[0], &num1, sizeof(int));
        read(p2[0], &num2, sizeof(int));
        c = num1;
        d = num2;
        printf("Child C chose the number : %d\n", c);
        printf("Child D chose the number : %d\n", d);
        if ((choice == 0 && c < d) || (choice == 1 && c > d)){
            C_score++;
            printf("Child C got the point.\n");
        }
        else if ((choice == 0 && c > d) || (choice == 1 && c < d)){
            D_score++;
            printf("Child D got the point.\n");
        }
        else
        printf("Round Ignored.\n");
        printf("Child C score is %d\n", C_score);
        printf("Child D score is %d\n\n", D_score);
        round_no++;
    }
    if (C_score == 10) printf("Child C wins!\n");   
    else if (D_score == 10) printf("Child D wins!\n");
    close(p1[0]);
    close(p2[0]);
    return 0;
}
