#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    int pid = fork();
    if (pid > 0)
        sleep(2);
    else
        exit(0);

    return 0;
}
