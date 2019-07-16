#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>
#define rend 0
#define wend 1

int main()
{
  int pid,fd[2],nb;
  char buffer[3000];
  if(pipe(fd)==-1)
  {
    fprintf(stderr,"Could not establish pipe\n");
    return 1;
  }
  pid=fork();
  if(pid==0)
  {
    close(fd[1]);  //close write end of pipe
    dup2(fd[0],0); //stdin points to the rend of pipe
    FILE *fd=fopen("stdout.txt","w");
    nb=read(0,buffer,3000);
    buffer[nb]='\0';
    fprintf(fd,"%s",buffer);
  }
  else if(pid>0)
  {
    dup2(fd[1],1);  //stdout points to the wend of pipe
    execlp("ls","ls",NULL); //ps output is dumped in pipe
  }

  return 0;
}
