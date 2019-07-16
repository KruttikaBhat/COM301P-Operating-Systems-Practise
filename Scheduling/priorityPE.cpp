#include<iostream>
using namespace std;

struct node{
  int pid,at,bt,tat,wt,finish,p,rt;
};

class priority{
  int size,totalWT,totalTime;
  struct node array[10];
public:
  void enter();
  void avgWT();
  int find();

};

void priority::enter()
{
  totalWT=0;
  cout<<"Enter the number of processes"<<endl;
	cin>>size;
	for(int i=0;i<size;i++)
	{
		cout<<"Enter the arrival time, burst time and priority"<<endl;
		cin>>array[i].at>>array[i].bt>>array[i].p;
		array[i].pid=i;
    array[i].tat=0;
    array[i].wt=0;
    array[i].finish=0;
    array[i].rt=array[i].bt;
    totalTime+=array[i].bt;
	}
	cout<<"Schedule:\npid\tat\tbt\tpriority"<<endl;
	for(int i=0;i<size;i++)
	{
		cout<<array[i].pid<<"\t"<<array[i].at<<"\t"<<array[i].bt<<"\t"<<array[i].p<<endl;
	}
}

void priority::avgWT()
{
  int t,minAT,pos=-1,i,pre;
  minAT=find();
  totalTime+=array[minAT].at;
  for(t=array[minAT].at;t<totalTime;t++)
  {
    int maxp=-1;
    pre=pos;
    for(i=0;i<size;i++)
    {
      if(array[i].at<=t && array[i].finish==0 && array[i].p>=maxp)
      {
        if(array[i].p==maxp && array[i].at<array[pos].at)
          pos=i;
        else if(array[i].p==maxp && array[i].at>array[pos].at)
          continue;
        else
        {
          maxp=array[i].p;
          pos=i;
        }
      }
    }
    array[pos].rt-=1;
    if(array[pos].rt==0)
      array[pos].finish=1;
    if(pos!=pre)
      cout<<t<<"|==P"<<pos+1<<"==|";
    for(i=0;i<size;i++)
    {
      if(array[i].finish==0 && array[i].at<=t && i!=pos)
        array[i].wt++;
    }
  }
  cout<<totalTime<<endl;
  cout<<"Schedule:\npid\tat\tbt\tpriority\ttat\twt"<<endl;
  for(i=0;i<size;i++)
  {
    totalWT+=array[i].wt;
    array[i].tat=array[i].wt+array[i].bt;
    cout<<array[i].pid<<"\t"<<array[i].at<<"\t"<<array[i].bt<<"\t"<<array[i].p<<"\t"<<array[i].tat<<"\t"<<array[i].wt<<endl;
  }
  cout<<"Average waiting time: "<<(float)totalWT/size<<endl;
}

int priority::find()
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

int main()
{
  priority p;
  p.enter();
  p.avgWT();
  return 0;
}
