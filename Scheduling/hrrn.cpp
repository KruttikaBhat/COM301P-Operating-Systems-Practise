#include<iostream>
using namespace std;

struct node{
  int pid,at,bt,tat,wt,finish,ct;
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
		cout<<"Enter the arrival time and burst time"<<endl;
		cin>>array[i].at>>array[i].bt;
		array[i].pid=i;
    array[i].tat=0;
    array[i].wt=0;
    array[i].finish=0;
    array[i].ct=0;
    totalTime+=array[i].bt;
	}
	cout<<"Schedule:\npid\tat\tbt"<<endl;
	for(int i=0;i<size;i++)
	{
		cout<<array[i].pid<<"\t"<<array[i].at<<"\t"<<array[i].bt<<endl;
	}
}

void priority::avgWT()
{
  int t,minAT,pos,i,pre,temp;
  minAT=find();
  totalTime+=array[minAT].at;
  for(t=array[minAT].at;t<totalTime;)
  {
    float maxrr=-1;
    for(i=0;i<size;i++)
    {
      array[i].wt=t-array[i].at;
      float rr=1+(array[i].wt/array[i].bt);
      if(array[i].at<=t && array[i].finish==0 && rr>maxrr)
      {
        maxrr=rr;
        pos=i;
      }
    }
    if(pre!=pos)
    {
      cout<<t<<"|==P"<<pos+1<<"==|";
      array[pos].finish=1;
      t+=array[pos].bt;
      array[pos].ct=t;
      pre=pos;
      temp=0;
    }
    else if(temp!=-1)
    {
      cout<<t<<"|==idle==|";
      temp=-1;
      t++;
    }
    else
      t++;
  }
  cout<<totalTime<<endl;
  cout<<"Schedule:\npid\tat\tbt\tct\ttat\twt"<<endl;
  for(i=0;i<size;i++)
  {
    totalWT+=array[i].wt;
    array[i].tat=array[i].wt+array[i].bt;
    cout<<array[i].pid<<"\t"<<array[i].at<<"\t"<<array[i].bt<<"\t"<<array[i].ct<<"\t"<<array[i].tat<<"\t"<<array[i].wt<<endl;
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
