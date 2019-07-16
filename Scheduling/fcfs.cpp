#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <sstream>

using namespace std;

struct node{
  int pid,at,bt,ct,tat,wt,finish;
};

class fcfs{
  int size,totalWT,totalTime;
  struct node array[10];
public:
  void enter();
  void avgWT();
  int find();
};

void fcfs::enter()
{
  totalWT=0;
  cout<<"Enter the number of processes"<<endl;
	cin>>size;
  char filename[100];
  for(int i=0; i<size; i++)
	{
	    cout << "Enter file name  ";
	    cin >> filename;
		struct stat t_stat;
		stat(filename, &t_stat);
    	struct tm * timeinfo = localtime(&t_stat.st_ctime); // or gmtime() depending on what you want

    	string s1 = asctime(timeinfo);
		cout << "Time info of file is   " << s1 << endl;

		string s2 = s1.substr(11, 2);
		stringstream g1(s2);
		int hr =0;
    	g1 >> hr;

 	    string s3= s1.substr(14,2);
	    stringstream g2(s3);
	    int min =0;
	    g2 >> min;

	    string s4= s1.substr(17,2);
    	stringstream g3(s4);
    	int sec =0;
    	g3 >> sec;

    	int seconds = (hr*60*60) + (min*60) + (sec);
    	array[i].at = seconds;
    	cout << "Time in seconds is  " << seconds << endl;

    	FILE* fp = fopen(filename, "r");
		if (fp == NULL)
	    {
    	    cout<<"File Not Found!\n";
    	    return;
    	}

    	fseek(fp, 0L, SEEK_END);
    	long int res = ftell(fp);

		fclose(fp);

		array[i].bt =res;
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
/*
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
	}*/
}

int fcfs::find()
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

void fcfs::avgWT()
{
  int t,minAT,pos,i;
  minAT=find();
  totalTime+=array[minAT].at;
  for(t=array[minAT].at;t<totalTime;)
  {
    int minat=999;
    for(i=0;i<size;i++)
    {
      if(array[i].at<=t && array[i].finish==0 && array[i].at<minat)
      {
        minat=array[i].at;
        pos=i;
      }
    }
    cout<<t<<"|==P"<<pos+1<<"==|";
    array[pos].finish=1;
    array[pos].wt=t-array[pos].at;
    t+=array[pos].bt;
    array[pos].ct=t;
    array[pos].tat=array[pos].wt+array[pos].bt;
  }
  cout<<totalTime<<endl;
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
  fcfs p;
  p.enter();
  p.avgWT();
  return 0;
}
