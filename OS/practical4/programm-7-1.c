#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
int main()
{
int i, value;
int status;
pid_t f;
value = 0;
i = 0;
status = 1;
f = vfork();
if (f < 0)
{
fprintf(stderr, "Error : %s - fork() < 0 (%d)\n", strerror(errno), f);
}
else if (f > 0)
{
printf("\n=====Begin Parent=====\n\n");
printf(" fork() = %d\n", f);
printf(" getpid() = %d\n", getpid());
while (i < 10)
{
printf(" Parent-value = %d\n", value);
++value;
++i;
}
}
else
{
printf("\n =====Begin Child=====\n\n");
printf(" fork() = %d\n", f);
printf(" getpid() = %d\n", getpid());
while (i < 10)
{
printf(" Child - value = %d\n", value);
++value;
++i;
}
_exit(status);
}
printf(" status = %d\n", status);
printf(" value = %d\n\n", value);
printf("=====End=====\n\n");
return 0;
}
