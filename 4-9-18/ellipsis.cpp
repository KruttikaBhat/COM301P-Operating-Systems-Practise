#include<iostream>
#include <cstdarg>
using namespace std;

void sort(int count, ...)
{
  va_list list;
  va_start(list,count);
  int *arr=va_arg(Array,int*);
  for(int i=0;i<count;++i)
  {
    for(j=0;j<count-i-1;j++)
    if(array[j]>array[j+1])
    {
      swap(array[j],array[j+1]);
    }
  }
}
void sort(int n,int array[])
{
  int i,j;
  cout<<"Before"<<endl;
  for(i=0;i<n;i++)
    cout<<array[i]<<" ";
  for(i=0;i<n-1;i++)
  {
    for(j=0;j<n-i-1;j++)
    {
      if(array[j]>array[j+1])
      {
        swap(array[j],array[j+1]);
      }
    }
  }
  cout<<"\nAfter"<<endl;
  for(i=0;i<n;i++)
    cout<<array[i]<<" ";
}

void swap(int &a,int &b)
{
  int temp=a;
  a=b;
  b=temp;
}

int main()
{
  sort(7,2,4,6,3,9,7,8);
  return 0;
}
