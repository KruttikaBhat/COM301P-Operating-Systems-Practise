#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
  int pid=fork();
  if(pid>0)
  {
      //execl("/bin/ls","ls",NULL);
      //execlp("ls","ls",NULL);
      //char *args[]={"/bin/ls","-1",NULL};
      //execv(args[0],args);
      char *args[]={"ls","-1",NULL};
      execvp(args[0],args);
  }
  else
    wait(NULL);
  return 0;
}
