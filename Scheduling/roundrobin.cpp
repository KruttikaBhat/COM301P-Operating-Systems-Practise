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
  int check(int);
  int find();

};
struct node q[30];
int qsize=1, front=0, end=qsize;

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
  int tq,t=0,sub=0,i,j,k,now,minAT,pcom=0;
  minAT=find();
  q[0]=array[minAT];
  cout<<"Enter the time quantum"<<endl;
  cin>>tq;
  totalTime+=array[minAT].at;
    for(qsize=1,t=array[minAT].at;t<totalTime;)
    {
      if(qsize!=0 || pcom!=size)
      {
        sub=tq;
        if(qsize!=0)
        {
          now=q[front].pid;
          cout<<t<<"|==P"<<now+1<<"==|";
          if(q[front].rt<tq)
            sub=q[front].rt;
          array[now].rt-=sub;
          q[front].rt-=sub;
          t+=sub;
          for(i=front+1;i<end;i++)
          {
            q[i].wt+=sub;
            array[q[i].pid].wt+=sub;
          }

          for(i=0;i<size;i++)
          {
            if(array[i].finish==0 && array[i].at<=t && check(i)==0)
            {
              if(array[i].at<t)
              {
                array[i].wt=t-array[i].at;
              }
              if(array[i].at<q[end-1].at)
              {
                for(j=front;j<end;j++)
                {
                  if(q[j].at>array[i].at)
                    break;
                }
                for(k=end;k>j;k--)
                {
                  q[k]=q[k-1];
                }
                q[j]=array[i];
                end++;
              }
              else
                q[end++]=array[i];
              qsize++;

            }
          }

          if(array[now].rt!=0)
          {
            q[end++]=q[front];
            front++;
          }
          else if(array[now].rt==0)
          {
            array[now].finish=1;
            pcom++;
            front++;
            qsize--;
          }
        }
        else if(qsize==0)
        {
          t++;
          totalTime++;
        }

      }
      else
        break;
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

int srt::check(int k)
{
  for(int i=front;i<end;i++)
  {
    if(q[i].pid==k)
      return 1;
  }
  return 0;
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
