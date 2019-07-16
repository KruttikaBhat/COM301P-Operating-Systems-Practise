#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int size=0;

void *mean(void *arg)
{
  int i,j,flag;
  int *array=(int *)arg;
  int sum = 0;
  for( i = 0; i < size; i++){
    sum += array[i];
  }
  float average =(float) sum / (size);
  printf("\nMean: %f\n",average);
  pthread_exit(0);
}

void *median(void *arg)
{
  int i,j,flag;
  int *array=(int *)arg;
  for(i=1;i<size;i++)
  {
    for(j=i;j>0;j--)
    {
      if(array[j]<array[j-1])
      {
        int temp=array[j];
        array[j]=array[j-1];
        array[j-1]=temp;
      }
    }
  }
  printf("\nMedian: %d\n",array[size/2]);
  pthread_exit(0);
}

void *mode(void *arg)
{
  int i;
  int *array=(int *)arg;
  int num[100]={0};
  for(i=0;i<size;i++)
  {
    num[array[i]]++;
  }
  int max=0,maxnum;
  for(i=0;i<100;i++)
  {
    if(num[i]>max)
    {
      max=num[i];
      maxnum=i;
    }
  }
  printf("\nMode: %d\n",maxnum);
  pthread_exit(0);
}

int main(int argc,char *argv[])
{
  pthread_t thread1,thread2,thread3;
  printf("%s\n",argv[1]);
  int *array = (int*)malloc((argc - 1)*sizeof(int));
  int i = 1;
  for(i = 1; i < argc ; i++){
    array[i-1] = atoi(argv[i]);
    size++;
  }
  if(pthread_create(&thread1,NULL,mean,(void *)array)<0)
  {
    fprintf(stderr,"\nThread not created\n");
    exit(0);
  }
  if(pthread_create(&thread2,NULL,median,(void *)array)<0)
  {
    fprintf(stderr,"\nThread not created\n");
    exit(0);
  }
  if(pthread_create(&thread3,NULL,mode,(void *)array)<0)
  {
    fprintf(stderr,"\nThread not created\n");
    exit(0);
  }
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);

return 0;
}
