#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<sys/wait.h>
#define rend 0
#define wend 1

int main()
{
  int pid,fd[2],nb,max=100,i;
  char buffer[50],input[50];
  if(pipe(fd)==-1)
  {
    fprintf(stderr,"Could not establish pipe\n");
    return 1;
  }
  pid=fork();
  if(pid==0)
  {
    close(fd[0]);
    printf("Enter the message: ");
    scanf("%s",input);
    write(fd[1],input,strlen(input));
  }
  else if(pid>0)
  {
    //wait(NULL);
    close(fd[1]);
    read(fd[0],buffer,50);
    for(i=0;i<strlen(buffer);i++)
      buffer[i]=toupper(buffer[i]);
    printf("After conversion: %s",buffer);
  }
  return 0;
}
