#include<iostream>
using namespace std;

struct node{
  int pid,at,bt,ct,tat,wt,finish,p;
};

class schedule{
	p array[10],Result[10];
	//int size, priority[10];
	int size,totalWT,totalTime;
	public:
		void enter();
		void display();
		int scan(int t);
		void fcfs();
		void sjf();
		void srt();
		void priorityNPE();
		void sort(int key);
		int findMinAT();
		/*static bool comparison(p A, p B)
		{
			return (A.bt<B.bt);
		}*/
};

void schedule::enter()
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
    totalTime+=array[i].bt;
	}
	cout<<"Schedule:\npid\tat\tbt\tpriority"<<endl;
	for(int i=0;i<size;i++)
	{
		cout<<array[i].pid<<"\t"<<array[i].at<<"\t"<<array[i].bt<<"\t"<<array[i].p<<endl;
	}
}

void schedule::display()
{
	cout<<"pid\tat\tbt\tct\ttat\twt"<<endl;
	for(int i=0;i<size;i++)
	{
		cout<<i<<"\t"<<array[i].at<<"\t"<<array[i].bt<<"\t"<<array[i].ct<<"\t"<<array[i].tat<<"\t"<<array[i].wt<<endl;
	}
}

void schedule::fcfs()
{
	int n=size,t=0,index;
	float avgWait=0.0;
	while(n!=0)
	{
		index=scan(t);
	}
	/*
	for(i=0;i<size;i++)  //calculate ct,tat,wt
	{
		findMinAT();
		if(i==0 || fcfsResult[i-1].ct<fcfsResult[i].at)
			fcfsResult[i].ct=fcfsResult[i].at+fcfsResult[i].bt;
		else
			fcfsResult[i].ct=fcfsResult[i].bt+fcfsResult[i-1].ct;

		fcfsResult[i].tat=fcfsResult[i].ct-fcfsResult[i].at;
		fcfsResult[i].wt=fcfsResult[i].tat-fcfsResult[i].bt;
		avgWait=avgWait+fcfsResult[i].wt;
	}
	avgWait=avgWait/size;
	cout<<"pid\tat\tbt\tct\ttat\twt"<<endl;
	for(int i=0;i<size;i++)
	{
		cout<<fcfsResult[i].pid<<"\t"<<fcfsResult[i].at<<"\t"<<fcfsResult[i].bt<<"\t"<<fcfsResult[i].ct<<"\t"<<fcfsResult[i].tat<<"\t"<<fcfsResult[i].wt<<endl;
	}
	cout<<"Average Wait time for FCFS is "<<avgWait<<endl;*/
}

int schedule::scan(int t)
{
	for(i=0;i<size;i++)
	{
		if(array[i].at==t && //not already completed && min burst )
			return i;
	}
	return -1;
}
/*
void schedule::sjf()
{
	int min=findMinAT(),i,j=1;
	cout<<"Min AT: "<<min<<endl;
	sjfResult[0]=array[min];
	//cout<<sjfResult[index].at<<" "<<sjfResult[index].bt<<endl;
	//sjfResult[index].ct=sjfResult[index].at+sjfResult[index].bt;
	for(i=0;i<size;i++)
	{
		if(i!=min)
			sjfResult[j++]=array[i];
	}
	sort(2);
	float avgWait=0.0;
	for(i=0;i<size;i++)
	{
	  if(i==0 || sjfResult[i-1].ct<sjfResult[i].at)
			sjfResult[i].ct=sjfResult[i].at+sjfResult[i].bt;
		else
			sjfResult[i].ct=sjfResult[i].bt+sjfResult[i-1].ct;
		sjfResult[i].tat=sjfResult[i].ct-sjfResult[i].at;
		sjfResult[i].wt=sjfResult[i].tat-sjfResult[i].bt;
		avgWait=avgWait+sjfResult[i].wt;
	}
	avgWait=avgWait/size;
	cout<<"pid\tat\tbt\tct\ttat\twt"<<endl;
	for(i=0;i<size;i++)
	{
		cout<<sjfResult[i].pid<<"\t"<<sjfResult[i].at<<"\t"<<sjfResult[i].bt<<"\t"<<sjfResult[i].ct<<"\t"<<sjfResult[i].tat<<"\t"<<sjfResult[i].wt<<endl;
	}
	cout<<"Average Wait time for SJF is "<<avgWait<<endl;
}

void schedule::srt()
{

}

void schedule::priorityNPE()
{
	int i;
	cout<<"Enter the priority for the processes"<<endl;
	for(i=0;i<size;i++)
		cin>>priority[i];
	for(i=0;i<size;i++)
	{
		priResult[i]=sjfResult[i];
	}
	sort(3);
	float avgWait=0.0;
	for(i=0;i<size;i++)
	{
	  if(i==0 || priResult[i-1].ct<priResult[i].at)
			priResult[i].ct=priResult[i].at+priResult[i].bt;
		else
			priResult[i].ct=priResult[i].bt+priResult[i-1].ct;
		priResult[i].tat=priResult[i].ct-priResult[i].at;
		priResult[i].wt=priResult[i].tat-priResult[i].bt;
		avgWait=avgWait+priResult[i].wt;
	}
		avgWait=avgWait/size;
		cout<<"pid\tat\tbt\tpriority\tct\ttat\twt"<<endl;
		for(i=0;i<size;i++)
		{
			cout<<priResult[i].pid<<"\t"<<priResult[i].at<<"\t"<<priResult[i].bt<<"\t"<<priority[priResult[i].pid]<<"\t"<<priResult[i].ct<<"\t"<<priResult[i].tat<<"\t"<<priResult[i].wt<<endl;
		}
		cout<<"Average Wait time for SJF is "<<avgWait<<endl;

}

int schedule::findMinAT()
{
	int min=999,minpos=0,i;
	for(i=0;i<size;i++)
		if(array[i].at<min)
		{
			min=array[i].at;
			minpos=i;
		}
	return minpos;
}

void schedule::sort(int key)
{
	p temp;
	int i,j;
	if(key==1)
	{
		for(i=1;i<size;i++)
		{
			for(j=i;j>0;j--)
			{
				if(fcfsResult[j].at<fcfsResult[j-1].at)
				{
					temp=fcfsResult[j];
					fcfsResult[j]=fcfsResult[j-1];
					fcfsResult[j-1]=temp;
				}
			}
		}
	}
	else if(key==2)
	{
		for(i=2;i<size;i++)
		{
			for(j=i;j>1;j--)
			{
				if(sjfResult[j].bt<sjfResult[j-1].bt)
				{
					temp=sjfResult[j];
					sjfResult[j]=sjfResult[j-1];
					sjfResult[j-1]=temp;
				}
			}
		}
	}
	else if(key==3)
	{
		for(i=2;i<size;i++)
		{
			for(j=i;j>1;j--)
			{
				if(priority[j]<priority[j-1])
				{
					temp=priResult[j];
					priResult[j]=priResult[j-1];
					priResult[j-1]=temp;
				}
			}
		}
	}
}
*/
int main()
{
	schedule x;
	x.enter();
	cout<<"FCFS:"<<endl;
	x.fcfs();
	cout<<"SJF"<<endl;
	x.sjf();

return 0;
}
