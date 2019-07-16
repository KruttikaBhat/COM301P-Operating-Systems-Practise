#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>
#include<sys/wait.h>
#include<string.h>
#define rend 0
#define wend 1

int main()
{
  int pid,fd1[2],fd2[2],i;
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
  pid=fork();
  if(pid==0)
  {
    char buffer[50],output[50];
    close(fd1[wend]);
    close(fd2[rend]);
    read(fd1[rend],buffer,50);
    //printf("%s %zu\n",buffer,strlen(buffer));
    for(i=0;buffer[i]!='\0';i++)
    {
      if(isupper(buffer[i]))
        output[i]=tolower(buffer[i]);
      else if(islower(buffer[i]))
        output[i]=toupper(buffer[i]);
      else
        output[i]=buffer[i];
    }
    output[i]='\0';
    write(fd2[wend],output,50);
  }
  else if(pid>0)
  {
    char input[50],output[50];
    close(fd1[rend]);
    close(fd2[wend]);
    printf("Enter a string: ");
    fgets(input,sizeof(input),stdin);
    write(fd1[wend],input,50);
    wait(NULL);
    read(fd2[rend],output,50);
    printf("After: %s",output);
  }

  return 0;
}
