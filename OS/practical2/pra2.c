#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <dirent.h>

void main(int argc, char *argv)
{
    int f;
    int ch;
    char cwd[1024], fileName[200];
    char dirName[10];
    DIR *p;
    struct dirent *d;

    while (1)
    {
        printf("1. Create directory\n");
        printf("2. Remove directory\n");
        printf("3. Change directory\n");
        printf("4. Search directory.\n");
        printf("0. EXit .\n");
        printf("Enter your choice.\n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("Enter name of the directory.\n");
            scanf("%s", fileName);
            f = mkdir(fileName, 0777);
            if (f == -1)
            {
                printf("\n Cannot create directory.\n");
                exit(-1);
            }
            else
            {
                printf("\n Directory with name %s is created\n", fileName);
            }
            break;
        case 2:
            printf("Enter name of the directory.\n");
            scanf("%s", fileName);
            f = rmdir(fileName);
            if (f == -1)
            {
                printf("\n Cannot remove directory.\n");
                exit(-1);
            }
            else
            {
                printf("\n Directory %s deleted\n", fileName);
            }
            break;
        case 3:
            printf("Enter name of the directory.\n");
            scanf("%s", cwd);
            char buffer[100];
            char *path = malloc(100 * sizeof(char));
            strcpy(path, cwd);
            if (chdir(path) == -1)
            {
                fprintf("Error : could not change directory %s\n", buffer);
            }
            else
            {
                getcwd(buffer, 100);
                printf("CWD is %s\n", buffer);
                printf("Directory changed to %s\n", buffer);
            }
            free(path);
            break;
        case 4:
            if (getcwd(cwd, sizeof(cwd)) != NULL)
            {
                fprintf(stdout, "Current working directory is %s\n", cwd);
            }
            else
            {
                perror("getcwd() failed\n");
            }
            p = opendir(cwd);
            if (p != NULL)
            {
                while (d = readdir(p))
                {
                    printf("\n %s\t", d->d_name);
                }
            }
            else
            {
                perror("Can't find directory.\n");
                exit(-1);
            }
        case 0:
            {
            exit(1);
            }
        }
    }
}
