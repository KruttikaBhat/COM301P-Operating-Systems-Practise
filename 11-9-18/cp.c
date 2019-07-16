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
  int pid,fd[2],i,j;
  if(pipe(fd)==-1)
  {
    fprintf(stderr,"Could not establish pipe\n");
    return 1;
  }
  pid=fork();
  if(pid==0)
  {
    char buffer[100];
    close(fd[1]);
    dup2(fd[0],0);
    FILE *dest=fopen("out.txt","w");
    while(fgets(buffer,sizeof(buffer),stdin))
    {
      printf("%s",buffer);
      fprintf(dest,"%s",buffer);
    }
    fclose(dest);
  }
  else if(pid>0)
  {
    int readcounter;
    char input[100];
    close(fd[0]);
    FILE *fileopen=fopen("input.txt","r");
    while(readcounter=read(fileopen,input,sizeof(input))>0)
    {
      printf("%s",input);
      write(fd[1],input,strlen(input));
    }
    fclose(fileopen);
  }
  /*if(pid==0)
  {
    char buffer[50];
    close(fd[wend]);
    dup2(fd[0],0);
    while(fgets(buffer,sizeof(buffer),stdin))
      fwrite(buffer,sizeof(buffer),1,d);

  }
  else if(pid>0)
  {
    char input[50],source[20],dest[20],rdline[50];
    close(fd[rend]);
    printf("Enter the source file and destination file separated by a space: ");
    fgets(input,sizeof(input),stdin);
    printf("%s",input);
    for(i=0;input[i]!='\0';i++)
    {
      if(input[i]==' ')
      {
        i++;
        for(j=i;input[j]!='\0';j++)
        {
          dest[j-i]=input[j];
        }
        dest[j]='\0';
        break;
      }
      source[i]=input[i];
    }
    source[i]='\0';
    s=fopen(source,"r");
    d=fopen(dest,"w");
    //write(fd[wend],input,50);
    while(fread(rdline,sizeof(rdline),1,s)==1)
    {
      write(fd[1],rdline,strlen(rdline));
    }
  }
*/
  return 0;
}
