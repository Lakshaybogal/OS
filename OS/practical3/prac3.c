#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
int main()
{
	char ch, buff[100], filename[15], pattern[15];
	char buffer[1024];
	int choice, fd, n, n1, size;
	bool found = false;
	while(1)
	{

		printf("\n1.Create file");
		printf("\n2.Read file");
		printf("\n3.Write into file");
		printf("\n4.Read file in reverse order.");
		printf("\n5.Search a pattern in a file");
		printf("\n6.Delete a file");
		printf("\n7.File status using stat");
		printf("\n8.File status using fstat.");
		printf("\n0.Exit");
		printf("\nEnter your Choice -: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("Enter the file name you want to create : ");
			scanf("%s", filename);
			fd = open(filename, O_CREAT | O_WRONLY, 0777);
			if (fd != -1)
			{
				printf("\nFile created!!!");
				printf("\nEnter contents in the file : ");
				scanf("%s", buff);
				n = write(fd, buff, strlen(buff));
				printf("\nSize of the file : %d", n);
				close(fd);
			}
			else
				printf("\nFile not created.");
			printf("\n");
			break;

		case 2:
			printf("Enter the filename which you want to read : ");
			scanf("%s", filename);
			fd = open(filename, O_RDONLY, 0777);
			if (fd != -1)
			{
				printf("\nFile opened!!!");
				printf("\nContents of the file are :\n");
				n = lseek(fd, 0, 2);
				lseek(fd, 0, 0);
				for (int i = 0; i < n; i++)
				{
					read(fd, &ch, 1);
					printf("%c", ch);
				}
				close(fd);
			}
			else
				printf("\nFile not opened.");
			printf("\n");
			break;

		case 3:
			printf("Enter the filename in which you want to write : ");
			scanf("%s", filename);
			printf("\nDo you want to overwrite the file ?(1-Yes/0-No)");
			scanf("%d", &n1);
			if (n1 == 0)
			{
				fd = open(filename, O_WRONLY | O_APPEND, 0777);
				if (fd != -1)
				{
					printf("\nFile opened!!!");
					printf("\nContents to write into the file :\n");
					scanf("%s", buff);
					write(fd, buff, strlen(buff));
					n = lseek(fd, 0, 2);
					printf("\nSize of the file : %d", n);
					close(fd);
				}
				else
					printf("\nFile not opened.");
			}
			else if (n1 == 1)
			{
				fd = open(filename, O_WRONLY, 0777);
				if (fd != -1)
				{
					printf("\nFile opened!!!");
					printf("\nContents to write into the file :\n");
					scanf("%s", buff);
					n = write(fd, buff, strlen(buff));
					printf("\nSize of the file : %d", n);
					close(fd);
				}
				else
					printf("File not opened.");
			}
			printf("\n");
			break;

		case 4:
			printf("Enter the filename : ");
			scanf("%s", filename);
			fd = open(filename, O_RDONLY, 0777);
			if (fd != -1)
			{
				printf("\nFile opened!!!");
				printf("\nContents of file in reverse order :\n");
				n = lseek(fd, 0, 2);
				lseek(fd, -1, 2);
				while (n-- > 0)
				{
					read(fd, &ch, 1);
					printf("%c", ch);
					lseek(fd, -2, 1);
				}
				printf("\n");
				close(fd);
			}
			else
				printf("File not opened.");
			printf("\n");
			break;

		case 5:
			printf("Enter the filename : ");
			scanf("%s", filename);
			fd = open(filename, O_RDONLY, 0777);
			if (fd != -1)
			{
				printf("\nFile opened!!!");
				printf("\nPattern which you want to search : ");
				scanf("%s", pattern);
				size = read(fd, &ch, 1);
				while (read(fd, buffer, sizeof(buffer)) > 0)
				{
					if (strstr(buffer, pattern) != NULL)
					{
						found = true;
						break;
					}
				}
				if (found)
					printf("String %s found\n", pattern);
				else
					printf("String %s not found\n", pattern);
				close(fd);
			}
			else
				printf("File not opened.");
			printf("\n");
			break;

		case 6:
			printf("Enter the filename : ");
			scanf("%s", filename);

			n = unlink(filename);
			if (!n)
				printf("\nFile is deleted.");
			else
				printf("\nFile not deleted");
			printf("\n");
			break;

		case 7:
			// stat call
			struct stat sfile1;
			stat("a", &sfile1);
			printf("st_mode of file a : %o", sfile1.st_mode);
			printf("\n");
			break;
		case 8:
			printf("Enter the filename : ");
			scanf("%s", filename);
			fd = open(filename, O_RDONLY, 0777);
			// fstat call
			struct stat sfile2;
			fstat(fd, &sfile2);
			printf("st_mode: %o", sfile2.st_mode);
			printf("\n");
			break;
		case 0:
		
			exit(0);
			break;
		}
	}
	return 0;
}
