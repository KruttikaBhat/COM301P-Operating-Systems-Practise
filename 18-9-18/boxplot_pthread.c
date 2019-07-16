#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int size=0;
float firstq,secondq,thirdq;

void *sq(void *arg)
{
  int *array=(int *)arg;
  if(size%2==0)
    secondq=(float)(array[size/2]+array[(size/2)-1])/2;
  else
    secondq=array[size/2];
  pthread_exit(0);
}

void *midq(void *arg)
{
  int *array=(int *)arg;
  int n=size/2,beg,end;
  if(size%2==0 && (size/2)%2==0)
  {
    end=n-1;
    beg=n;
    firstq=(float)(array[(end/2)+1]+array[end/2])/2;
    thirdq=(float)(array[(beg+size)/2]+array[((beg+size)/2)-1])/2;
    //printf("\n1: beg:%d end:%d firstq:%f thirdq:%f\n",beg,end,firstq,thirdq);
  }
  else if(size%2!=0 && (size/2)%2==0)
  {
    end=n-1;
    beg=n+1;
    firstq=(float)(array[(end/2)+1]+array[end/2])/2;
    thirdq=(float)(array[(beg+size)/2]+array[((beg+size)/2)-1])/2;
    //printf("\n2: beg:%d end:%d firstq:%f secondq:%f\n",beg,end,firstq,secondq);
  }
  else if(size%2==0 && (size/2)%2!=0)
  {
    end=n-1;
    beg=n;
    firstq=array[end/2];
    thirdq=array[(beg+size)/2];
    //printf("\n3: beg:%d end:%d firstq:%f secondq:%f\n",beg,end,firstq,secondq);
  }
  else if(size%2!=0 && (size/2)%2!=0)
  {
    end=n-1;
    beg=n+1;
    firstq=array[end/2];
    thirdq=array[(beg+size)/2];
    //printf("\n4: beg:%d end:%d firstq:%f secondq:%f\n",beg,end,firstq,secondq);
  }
  //printf("\nInside function: %f %f\n",firstq,thirdq);
  pthread_exit(0);
}

void *sort(void *arg)
{
  int *array=(int *)arg;
  int i,j;
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
  for(i=0;i<size;i++)
    printf("%d ",array[i]);
  pthread_t thread1,thread2;
  if(pthread_create(&thread1,NULL,sq,(void *)array)<0)
  {
    fprintf(stderr,"\nThread not created\n");
    exit(0);
  }
  if(pthread_create(&thread2,NULL,midq,(void *)array)<0)
  {
    fprintf(stderr,"\nThread not created\n");
    exit(0);
  }
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  //printf("Inside function1: %f %f\n",firstq,thirdq);
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

  if(pthread_create(&thread1,NULL,sort,(void *)array)<0)
  {
    fprintf(stderr,"\nThread not created\n");
    exit(0);
  }

  pthread_join(thread1, NULL);
  printf("\n\nMin: %d\nFirstQ: %f\nSecondQ: %f\nThirdQ: %f\nMax: %d\n",array[0],firstq,secondq,thirdq,array[size-1]);

return 0;
}
