#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
int main()
{
int j, n, a, i, e, o, u;
char str[50];
a = e = i = o = u = 0;
pid_t pid;
if ((pid = vfork()) < 0)
{
perror(" FORK ERROR");
exit(1);
}
if (pid == 0)
{
printf("Counting Number of Vowels using VFORK\n");
printf("--------------------------------\n");
printf("Enter the String : \n");
gets(str);
_exit(1);
}
else
{
n = strlen(str);
for (j = 0; j < n; j++)
{
if (str[j] == 'a' || str[j] == 'A')
a++;
else if (str[j] == 'e' || str[j] == 'E')
e++;
else if (str[j] == 'i' || str[j] == 'I')
i++;
else if (str[j] == 'o' || str[j] == 'O')
o++;
else if (str[j] == 'u' || str[j] == 'U')
u++;
}
printf("Vowels Counting\n");
printf("--------------\n");
printf("Number of A: %d\n", a);
printf("Number of E: %d\n", e);
printf("Number of I: %d\n", i);
printf("Number of O: %d\n", o);
printf("Number of U: %d\n", u);
printf("Total vowels: % d", a + e + i + o + u);
exit(1);
}
}
