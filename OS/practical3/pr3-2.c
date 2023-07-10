#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include <string.h>
# include <stdlib.h>

int main(){
	int fd1,fd2,n,choice;
	char buff[100],file1[15],file2[15];
	printf("File 1 - Source file\nFile 2 - Destination file");
	printf("\nEnter the name of file 1 : ");
	scanf("%s",file1);
	printf("Enter the name of file 2 : ");
	scanf("%s",file2);
	
	fd1 = open(file1,O_RDONLY,0777);
	printf("Do you want to overwrite the contents ?(Yes-1/No-0)");
	scanf("%d",&choice);
	if(choice) fd2 = open(file2,O_WRONLY,0777);
	else fd2 = open(file2,O_APPEND,0777);

	if(fd1!=-1 && fd2!=-1){
		n = lseek(fd1,0,2);
		lseek(fd1,0,0);
		read(fd1,buff,n);
		write(fd2,buff,n);
	}
	else printf("\nProblem detected while opening!!");
	return 0;
}
