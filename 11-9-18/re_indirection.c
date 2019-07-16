#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<fcntl.h>
#define rend 0
#define wend 1

int main()
{
  int pid,fd[2],nb;
  char buffer[3000];
  int f=open("ls.txt", O_CREAT|O_RDWR,0666);
  if(pipe(fd)==-1)
  {
    fprintf(stderr,"Could not establish pipe\n");
    return 1;
  }
  pid=fork();
  if(pid==0)
  {
    //close(fd[1]);  //close write end of pipe
    int f2=dup2(f,0); //stdin points to the rend of pipe
    while(nb=read(f2,buffer,3000)>0)
    {
      write(1,buffer,strlen(buffer));
    }
  }
  else if(pid>0)
  {
    dup2(f,1);  //stdout points to the wend of pipe
    execlp("ls","ls",NULL); //ps output is dumped in pipe
  }

  return 0;
}
