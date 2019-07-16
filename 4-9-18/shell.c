#include <stdio.h>
#include <stdlib.h>
#include <string.h>     // strlen, strncpy
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
  int pid,count=0,i;
  char arg[50],history[50][50],empty[50]={0};
  while(1)
  {
    printf("\n\nEnter the command: ");
    scanf("%s",arg);
    strcpy(history[count++],arg);
    pid=fork();
    if(pid>0)
    {
      wait(NULL);
    }
    else if(pid==0)
    {
      if(arg[0]=='!')
      {
        strcpy(history[count-1],empty);
        count--;
        if(arg[1]=='!')
        {
          for(i=0;i<count;i++)
            printf("\n%s",history[i]);
        }
        else if(arg[1]>48)
        {
          for(i=count-(arg[1]-48);i<count;i++)
            printf("\n%s",history[i]);
        }
      }
      else
        execlp(arg,arg,NULL);
    }
  }
  return 0;
}
