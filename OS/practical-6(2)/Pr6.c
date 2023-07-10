#include<stdio.h>
#include<unistd.h>
#include<string.h>
main()
{
 int p1[2],p2[2],p3[2],p4[2];
 int i,j=0,k=0,l=0;
 char r[10],s[10],t[10],u[10];
 printf("\t PROCESS 1.ENTER THE STRING");
 scanf("%s",r);
 pipe(p1);
 pipe(p2);
 write(p1[1],r,sizeof(r));
 write(p2[1],r,sizeof(r));
 int a=fork();
 if(a==0)
 {
  printf("\n\t PROCESS 2:it splits the given string\n");
  read(p1[0],r,sizeof(r));
  int n=strlen(r);
  for(i=0;i<n/2;i++)
  {
    s[i]=r[i];
  }
  for(i=n/2;i<=n;i++)
  {
   t[j++]=r[i];
  }
  pipe(p3);
  pipe(p4);
  write(p3[1],s,sizeof(s));
  write(p4[1],t,sizeof(t));
  int b=fork();
  if(b==0)
  {
   printf("p4 %d\t",getpid());
   printf("p2 %d\n",getppid());
   read(p3[0],s,sizeof(s));
   printf("\t PROCESS 4:sub string \t %s \t",s);
   printf("no of char=%d \n",strlen(s));
  }
  else
  {
    int c=fork();
    if(c==0)
  {
   printf("p5 %d\t",getpid());
   printf("p2 %d\n",getppid());
   read(p4[0],t,sizeof(t));
   printf("\t PROCESS 5:sub string \t %s \t",t);
   printf("no of char=%d \n",strlen(t));
  }
  else
  {
    wait();
    printf("p2 %d\t",getpid());
    printf("p1 %d\n",getppid());
  }   }}
else
{
  wait();
  int d=fork();
  if(d==0)
   {
     printf("p3 %d\t",getpid());
     printf("p1 %d\n",getppid());
     read(p2[0],r,sizeof(r));
     for(i=strlen(r)-1;i>=0;i--)
     {
       u[l++]=r[i];
     }
     for(i=0;i<strlen(r);i++)
     {
       if(u[i]==r[i])
       k++;
       else
       continue;
    }
     if(k==strlen(r))
     printf("\t PROCESS 3: the given string is palindrome\n");
     else
     printf("\t PROCESS 3: the given string is not palindrome\n");
    }
    else
    {
      printf("p1 %d\t",getpid());
      printf("kernal %d\t\n",getppid());
    } 
 }} 

