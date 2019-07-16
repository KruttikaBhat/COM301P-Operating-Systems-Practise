#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#define rend 0
#define wend 1

int main()
{
  int fd1[2],fd2[2];
  if(pipe(fd1)==-1)
  {
    fprintf(stderr,"Could not establish pipe\n");
    return 1;
  }
  if(pipe(fd2)==-1)
  {
    fprintf(stderr,"Could not establish pipe\n");
    return 1;
  }
  int pid=fork();
  if(pid>0)
  {
    char mes[20]="Message 1",mes2[20];
    close(fd1[rend]);
    close(fd2[wend]);
    write(fd1[wend],mes,20);
    wait(NULL);
    read(fd2[rend],mes2,20);
    printf("\nParent: %s",mes2);
  }
  else
  {
    char mes[20],mes2[20]="Message 2";
    close(fd1[wend]);
    close(fd2[rend]);
    read(fd1[rend],mes,20);
    printf("\nChild: %s",mes);
    write(fd2[wend],mes2,20);

  }
  return 0;
}
