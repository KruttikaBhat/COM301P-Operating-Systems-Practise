#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void collatz(int n)
{
  while(n!=1)
  {
    printf("%d ",n);
    if(n%2==0)
      n=n/2;
    else
      n=3*n+1;
  }
  printf("%d",n);
}

int main()
{
  int pid=vfork();
  int x;
  if(pid>0)
  {
    wait(NULL);
    collatz(x);
    //perfectnum(ll,ul);
  }
  else
  {
    printf("Enter the number: ");
    scanf("%d",&x);
    _exit(0);
  }
  return 0;
}
