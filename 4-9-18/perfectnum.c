#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void perfectnum(int l,int u)
{
  int i,j;
  for(i=l;i<=u;i++)
  {
    int sum=0;
    for(j=1;j<i;j++)
    {
      if(i%j==0)
        sum+=j;
    }
    if(sum==i)
      printf("%d is a perfect number\n",i);
  }
}

int main()
{
  int pid=vfork();
  int ll,ul;
  if(pid>0)
  {
    wait(NULL);
    perfectnum(ll,ul);
    //perfectnum(ll,ul);
  }
  else
  {
    printf("Enter the lower and upper limit: ");
    scanf("%d%d",&ll,&ul);
    _exit(0);
  }
  return 0;
}
