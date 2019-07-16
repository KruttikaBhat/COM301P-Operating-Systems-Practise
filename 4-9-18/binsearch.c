#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void swap(int *a,int *b)
{
  int temp=*a;
  *a=*b;
  *b=temp;
}

void bubsort(int n,int arr[])
{
  int i,j;
  for(i=0;i<n-1;i++)
  {
    for(j=0;j<n-i-1;j++)
    {
      if(arr[j]>arr[j+1])
        swap(&arr[j],&arr[j+1]);
    }
  }

}

int search(int x,int arr[],int n)
{
  int beg=0,end=n-1,mid;
  while(beg<=end)
  {
    mid=(beg+end)/2;
    if(x<arr[mid])
      end=mid-1;
    else if(x>arr[mid])
      end=mid+1;
    else
    {
      printf("\n%d is found\n",x);
      return 0;
    }
  }
  return -1;
}

int main()
{
  int pid=vfork();
  int n,arr[10],i,x,flag=0;
  if(pid>0)
  {
    wait(NULL);
    printf("\nEnter a number to search: ");
    scanf("%d",&x);
    if(search(x,arr,n)==-1)
      printf("\n%d not found\n",x);

  }
  else
  {
    printf("\nEnter the size of the array: ");
    scanf("%d",&n);
    printf("\nEnter the array: ");
    for(i=0;i<n;i++)
      scanf("%d",&arr[i]);
    bubsort(n,arr);
    printf("\nAfter sorting: ");
    for(i=0;i<n;i++)
      printf("%d ",arr[i]);
    _exit(0);
  }
  return 0;
}
