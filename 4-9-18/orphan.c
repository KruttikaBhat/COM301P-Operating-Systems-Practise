#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int pid = fork();
    if (pid > 0)
        printf("Parent process");
    else if (pid == 0)
    {
        sleep(5);
        printf("Child process");
    }
  return 0;
}
