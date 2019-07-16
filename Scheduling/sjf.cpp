#include<iostream>
using namespace std;

struct node{
  int pid,at,bt,ct,tat,wt,finish;
};

class sjf{
  int size,totalWT,totalTime;
  struct node array[10];
public:
  void enter();
  void avgWT();
  int find();
};

void sjf::enter()
{
  totalWT=0;
  cout<<"Enter the number of processes"<<endl;
	cin>>size;
	for(int i=0;i<size;i++)
	{
		cout<<"Enter the arrival time and burst time"<<endl;
		cin>>array[i].at>>array[i].bt;
		array[i].pid=i;
    array[i].tat=0;
    array[i].wt=0;
    array[i].ct=0;
    array[i].finish=0;
    totalTime+=array[i].bt;
	}
	cout<<"Schedule:\npid\tat\tbt"<<endl;
	for(int i=0;i<size;i++)
	{
		cout<<array[i].pid<<"\t"<<array[i].at<<"\t"<<array[i].bt<<endl;
	}
}

int sjf::find()
{
  int min=100,minpos;
  for(int i=0;i<size;i++)
  {
    if(array[i].at<min)
    {
      min=array[i].at;
      minpos=i;
    }
  }
  return minpos;
}

void sjf::avgWT()
{
  int t,minAT,pos=0,i,pre=-1,j;
  minAT=find();
  t=array[minAT].at;
  for(j=0;j<size;j++)
  {
    int minbt=999;
    for(i=0;i<size;i++)
    {
      if(array[i].at<=t && array[i].finish==0 && array[i].bt<=minbt )
      {
        if(array[i].bt==minbt && array[i].at<=array[pos].at)
        {
          pos=i;
        }
        else if(array[i].bt<minbt)
        {
          minbt=array[i].bt;
          pos=i;
        }
      }
    }
    if(pos==pre)
    {
      int minat=999;
      for(i=0;i<size;i++)
      {
        if(array[i].finish==0 && array[i].at<=minat )
        {
          minat=array[i].at;
          pos=i;
        }
      }
      cout<<t<<"|==idle==|";
      t=array[pos].at;
    }
    cout<<t<<"|==P"<<pos+1<<"==|";
    array[pos].finish=1;
    array[pos].wt=t-array[pos].at;
    if(array[pos].at>t)
      t+=array[pos].at-t+array[pos].bt;
    else
      t+=array[pos].bt;
    array[pos].ct=t;
    array[pos].tat=array[pos].wt+array[pos].bt;
    pre=pos;
  }
  cout<<t<<endl;
  cout<<"Schedule:\npid\tat\tbt\tct\ttat\twt"<<endl;
  for(i=0;i<size;i++)
  {
    totalWT+=array[i].wt;
    cout<<array[i].pid<<"\t"<<array[i].at<<"\t"<<array[i].bt<<"\t"<<array[i].ct<<"\t"<<array[i].tat<<"\t"<<array[i].wt<<endl;
  }
  cout<<"Average waiting time: "<<(float)totalWT/size<<endl;
}


int main()
{
  sjf p;
  p.enter();
  p.avgWT();
  return 0;
}
