#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;


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

int main(int argc, char * argv[])
{
  int i,n,array[20],j;
  n=atoi(argv[1]);
  int base=2;
  for(i=base;i<argc;i++)
    array[i-base]=atoi(argv[i]);
  sort(n,array);
  return 0;
}
