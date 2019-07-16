#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *prime(void *var)
{
  int i,j,flag;
  int *x=(int *)var;
  for(i=2;i<=*x;i++)
  {
    flag=0;
    for(j=1;j<i/2;j++)
    {
      if(i%j==0 && j!=1)
      {
        flag=1;
        break;
      }
    }
    if(flag==0)
      printf("%d ",i);
  }
  pthread_exit(0);
}

int main(int argc,char *argv[])
{
  pthread_t tid;
  printf("%s\n",argv[1]);
  int i=atoi(argv[1]);
  pthread_create(&tid,NULL,prime,(void *)&i);
  pthread_join(tid,NULL);
return 0;
}
