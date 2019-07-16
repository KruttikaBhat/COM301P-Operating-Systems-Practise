#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;

template <class T>
void sort(int n,T array[])
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

template <class S>
void swap(S &a,S &b)
{
  S temp=a;
  a=b;
  b=temp;
}

int main(int argc, char * argv[])
{
  int i,n,array[20],j;
  float arrayf[20];
  if(strcmp(argv[1],"--")==0)
  {
    n=atoi(argv[2]);
    int base=3;
    for(i=base;i<argc;i++)
      array[i-base]=atoi(argv[i]);
    for(i=base;i<argc;i++)
      arrayf[i-base]=atof(argv[i]);
    for(i=0;i<n;i++)
    {
      if(arrayf[i]-int(arrayf[i])>0)
        break;
    }
    if(i==n)
      sort(n,array);
    else
      sort(n,arrayf);
  }
  else if(strcmp(argv[1],"--")!=0)
  {
    n=argc-1;
    int base=1;
    for(i=base;i<argc;i++)
      array[i-base]=atoi(argv[i]);
    for(i=base;i<argc;i++)
      arrayf[i-base]=atof(argv[i]);
    for(i=0;i<n;i++)
    {
      if(arrayf[i]-int(arrayf[i])>0)
        break;
    }
    if(i==n)
      sort(n,array);
    else
      sort(n,arrayf);
  }
  return 0;
}
