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
void merge(int beg,int end);
int part=0;

int main(int argc,char **argv){
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

   int mid=(p->beg+p->end)/2;

   i1.beg=p->beg;
   i1.end=mid;

   i2.beg=mid+1;
   i2.end=p->end;

   if(p->beg>=p->end)
     pthread_exit(0);
   else
   {
       pthread_t tid1,tid2;
       pthread_attr_t attr;
       pthread_attr_init(&attr);
       
       int ret;
       ret=pthread_create(&tid1,&attr,runner,&i1);
   
       if (ret) 
         {
            printf("%d %s - unable to create thread - ret - %d\n", __LINE__, __FUNCTION__, ret);
            exit(1);
         }
   
       pthread_create(&tid2,&attr,runner,&i2);

       pthread_join(tid1,NULL);
       pthread_join(tid2,NULL);

       merge(p->beg,p->end);
   }

}

void merge(int beg,int end)
{
  int mid=(beg+end)/2;
	
  int i=beg,j=mid +1,k=0;
  int b[100];

  while((i<=mid )&& (j<=end))
     {
	if(a[i]<a[j])
	  {
	     b[k]=a[i];
	     i++;
          }
	else
          {
	     b[k]=a[j];
	     j++;
	  }
	k++;
     }

  while(i<=mid)
     {
	b[k]=a[i];
	k++;
	i++;
     }
  while(j<=end)
     {
	b[k]=a[j];
	k++;
	j++;
     }

  for(i=beg;i<=end;i++)
     a[i]=b[i-beg];

}
