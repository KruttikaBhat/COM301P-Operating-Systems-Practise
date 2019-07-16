#include<iostream>
using namespace std;

struct node{
  int pid,at,bt,finish,tat,wt,rt;
};

class srt{
  int size,totalTime,totalWT;
  struct node array[10];
public:
  void enter();
  void avgWT();
  int find();
};

void srt::enter()
{
  totalWT=0;
  totalTime=0;
  cout<<"Enter the number of processes"<<endl;
	cin>>size;
	for(int i=0;i<size;i++)
	{
		cout<<"Enter the arrival time and burst time"<<endl;
		cin>>array[i].at>>array[i].bt;
		array[i].pid=i;
    array[i].tat=0;
    array[i].wt=0;
    array[i].rt=array[i].bt;
    array[i].finish=0;
    totalTime+=array[i].bt;
	}
	cout<<"Schedule:\npid\tat\tbt"<<endl;
	for(int i=0;i<size;i++)
	{
		cout<<array[i].pid<<"\t"<<array[i].at<<"\t"<<array[i].bt<<endl;
	}
}

void srt::avgWT()
{
  int t,minAT,pre,pos=-1,i;
  minAT=find();
  totalTime+=array[minAT].at;
  for(t=array[minAT].at;t<totalTime;t++)
  {
    int minrt=100;
    pre=pos;
    for(i=0;i<size;i++)
    {
      if(array[i].at<=t && array[i].finish==0 && array[i].rt<=minrt)
      {
        if(array[i].rt==minrt && array[i].at<array[pos].at)
          pos=i;
        else if(array[i].rt==minrt && array[i].at>array[pos].at)
            continue;
        else
        {
          minrt=array[i].rt;
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
  cout<<"Schedule:\npid\tat\tbt\ttat\twt"<<endl;
  for(i=0;i<size;i++)
  {
    totalWT+=array[i].wt;
    array[i].tat=array[i].wt+array[i].bt;
    cout<<array[i].pid<<"\t"<<array[i].at<<"\t"<<array[i].bt<<"\t"<<array[i].tat<<"\t"<<array[i].wt<<endl;
  }
  cout<<"Average waiting time: "<<(float)totalWT/size<<endl;
}

int srt::find()
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
  srt s;
  s.enter();
  s.avgWT();
  return 0;
}
