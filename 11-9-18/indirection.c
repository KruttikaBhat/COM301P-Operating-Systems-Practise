#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define rend 0
#define wend 1

int main()
{
  int pid,fd[2],nb;

  if(pipe(fd)==-1)
  {
    fprintf(stderr,"Could not establish pipe\n");
    return 1;
  }
  pid=fork();
  if(pid==0)
  {
    char buffer[1000];
    close(fd[1]);
    dup2(fd[0],0);
    while(fgets(buffer,sizeof(buffer),stdin))
      printf("%s",buffer);
  }
  else if(pid>0)
  {
    char input[20];
    //close(fd[0]);
    FILE *fileopen=fopen("input.txt","r");
    while(fread(input,sizeof(input),1,fileopen))
    {
      write(fd[1],input,strlen(input));
    }

  }

  return 0;
}
