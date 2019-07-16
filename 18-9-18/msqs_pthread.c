#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int size=0;
int array2[20];

void merge(int *array,int l,int m,int r)
{
  int i,j,k;
  int b[50];
   for(j= l, k = m + 1, i = l; j <= m && k <= r; i++) {
      if(array[j] <= array[k])
         b[i] = array[j++];
      else
         b[i] = array[k++];
   }

   while(j<= m)
      b[i++] = array[j++];

   while(k <= r)
      b[i++] = array[k++];

   for(i = l; i <= r; i++)
      array[i] = b[i];
}

void mergesort(int *array,int l,int r)
{
  if(l<r)
  {
    int mid=(l+r)/2;
    mergesort(array,l,mid);
    mergesort(array,mid+1,r);
    merge(array,l,mid,r);

  }
}

void *ms(void *arg)
{
  int i,j,flag;
  int *array=(int *)arg;
  mergesort(array,0,size-1);
  printf("\nMerge sort: ");
  for(i=0;i<size;i++)
    printf("%d ",array[i]);
  pthread_exit(0);
}

struct args{
  int f,l;
};

void quicksort(int number[],int first,int last)
{
   int i, j, pivot, temp;

   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while(number[i]<=number[pivot]&&i<last)
            i++;
         while(number[j]>number[pivot])
            j--;
         if(i<j){
            temp=number[i];
            number[i]=number[j];
            number[j]=temp;
         }
      }

      temp=number[pivot];
      number[pivot]=number[j];
      number[j]=temp;
      quicksort(number,first,j-1);
      quicksort(number,j+1,last);

   }
}


void *qs(void *arg)
{
  int i,j,flag,first,last,temp,pivot;
  pthread_t thread1,thread2;
  struct args *s=arg;
  first=s->f;
  last=s->l;
  if(first<last){
     pivot=first;
     i=first;
     j=last;

     while(i<j){
        while(array2[i]<=array2[pivot]&&i<last)
           i++;
        while(array2[j]>array2[pivot])
           j--;
        if(i<j){
           temp=array2[i];
           array2[i]=array2[j];
           array2[j]=temp;
        }
     }

     temp=array2[pivot];
     array2[pivot]=array2[j];
     array2[j]=temp;
     struct args *t1=(struct *)malloc(sizeof(args));
     t1->f=first;
     t1->l=j-1;
     t2->f=j+1;
     t2->l=last;
     if(pthread_create(&thread1,NULL,qs,t1)<0)
     {
       fprintf(stderr,"\nThread not created\n");
       exit(0);
     }
     if(pthread_create(&thread2,NULL,qs,t2)<0)
     {
       fprintf(stderr,"\nThread not created\n");
       exit(0);
     }

   }
  pthread_exit(0);
}

int main(int argc,char *argv[])
{
  pthread_t thread1,thread2;
  printf("%s\n",argv[1]);
  int *array1 = (int*)malloc((argc - 1)*sizeof(int));
  *array2 = (int*)malloc((argc - 1)*sizeof(int));
  int i = 1;
  for(i = 1; i < argc ; i++){
    array1[i-1] = atoi(argv[i]);
    array2[i-1]=array1[i-1];
    size++;
  }
  struct args s;
  s.f=0;
  s.l=size-1;
  /*if(pthread_create(&thread1,NULL,ms,(void *)array)<0)
  {
    fprintf(stderr,"\nThread not created\n");
    exit(0);
  }*/
  if(pthread_create(&thread2,NULL,qs,(void *)s)<0)
  {
    fprintf(stderr,"\nThread not created\n");
    exit(0);
  }
  //pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  printf("\nQuick sort: ");
  for(i=0;i<size;i++)
    printf("%d ",array2[i]);
return 0;
}
