#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#define rend 0
#define wend 1

int main()
{

  int fd[2],pid;
  if(pipe(fd)>=0)
    pid=fork();
  else
  {
    fprintf(stderr,"Could not establish pipe\n");
    return 1;
  }
  if(pid>0)
  {
    char mes[20]="Hello";
    close(fd[rend]);
    write(fd[wend],mes,20);
    close(fd[wend]);
  }
  else
  {
    char rec[20];
    close(fd[wend]);
    read(fd[rend],rec,20);
    printf("%s",rec);
  }
  return 0;
}
