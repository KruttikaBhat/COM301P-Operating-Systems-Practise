#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int a[100];
int n;

struct index_range
{
  int beg;
  int end;
};

void *runner(void *param);
int partition(int beg,int end);

int main(int argc,char **argv)
{
  if(argc==1)
   {
      printf("Insufficient arguments!!");
      return -1;
   }

   struct index_range *i=(struct index_range*)malloc(sizeof(struct index_range));
   n=argc-1;

   for(int p=0;p<n;p++)
   a[p]=atoi(argv[p+1]);

    i->beg=0;
    i->end=n-1;

    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid,&attr,runner,i);

    pthread_join(tid,NULL);

    printf( "Sorted array: \n");
    for (int i = 0; i < n; i++)
      printf("%d \t",a[i] );

  return 0;
}
void *runner(void *param)
{

   struct index_range *p=param;
   struct index_range i1;
   struct index_range i2;

   if(p->beg < p->end)
   {
        int j=partition(p->beg,p->end);
        i1.beg=p->beg;
        i1.end=j-1;

        i2.beg=j+1;
        i2.end=p->end;
   
        pthread_t tid1,tid2;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
    
        pthread_create(&tid1,&attr,runner,&i1);
        pthread_create(&tid2,&attr,runner,&i2);
        
        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);

    }

 pthread_exit(0);

}

int partition(int beg,int end)
{

  int pivot=a[beg];

  int i=beg, j=end ,temp;

  while(i<=j)
   {
      while((a[i]<=pivot) && (i<=end))
        i++;

      while( (a[j]>pivot) && (j>=beg))
        j--;

      //swap a[i] and a[j]

      if(i<j)
        {
           temp=a[i];
           a[i]=a[j];
           a[j]=temp;
        }

    }

  //swap pivot and a[j];
  temp=a[beg];
  a[beg]=a[j];
  a[j]=temp;

 return (j);

}
