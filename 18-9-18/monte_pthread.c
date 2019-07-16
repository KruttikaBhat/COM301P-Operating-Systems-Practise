#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>

void *monte()
{
  int i,val=1000,incircle=0,total=0;
  double x,y,dist;
  srand(time(NULL));
  for(i=0;i<val*val;i++)
  {
    x=(double)(rand()%(val+1))/val;
    y=(double)(rand()%(val+1))/val;
    double xsquare=(double)pow(x,2);
    double ysquare=(double)pow(y,2);
    dist=sqrt(xsquare+ysquare);
    if(dist<=1)
      incircle++;
    printf("X: %f Y: %f Distance: %f\n",x,y,dist);
  }
  total=i;
  printf("incircle: %d total:%d",incircle,total);
  double pi=4.0*incircle/total;
  printf("\n%f",pi);
  pthread_exit(NULL);
}

int main()
{
  pthread_t tid;
  pthread_create(&tid,NULL,monte,NULL);
  pthread_join(tid,NULL);
return 0;
}
