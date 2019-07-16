#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>
#define rend 0
#define wend 1

int main()
{
  int pid,fd[2];
  if(pipe(fd)==-1)
  {
    fprintf(stderr,"Could not establish pipe\n");
    return 1;
  }
  pid=fork();
  if(pid==0)
  {
    close(fd[1]);  //close write end of pipe
    dup2(fd[0],0);  //point the stdin to the read end of pipe
    execlp("tr","tr","a-z","A-Z",NULL);  //the stdin->rend of pipe is taken as input for this command
  }
  else if(pid>0)
  {
    dup2(fd[1],1); //point the stdout to the write end of pipe
    execlp("ps","ps",NULL); //dumped in stdout-> wend pipe

  }

  return 0;
}
