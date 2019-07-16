#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#define N 3
#define C 5
#define A 500

sem_t counter[N],account[A];
pthread_t cus[C];
float bankBal;

struct account{
  float bal;
  int accnum;
};


struct cust{
  int type;
  float money;
  int accno;
  int token;
  int tid;
  int num;
};

struct account acc[A];
struct cust customer[C];


void *customFunc(void * arg)
{
  struct cust *X;
  X=(struct cust *)arg;
  
  int token=rand()%15;
  int counterNum=token%N;
  
  if(sem_wait(&counter[counterNum])==0)
    printf("\nCustomer %d is waiting at counter %d\n",X->num,counterNum);
    
  sem_wait(&account[X->accno]);
  if(X->type==1)
  {
    int trans=rand()%500;
    acc[X->accno].bal+=X->money;
    bankBal+=X->money;
    X->token=token;
    X->tid=trans;
    printf("\nCustomer %d finished transaction\n",X->num);
  }  
  else if(X->type==2)
  {
    if(acc[X->accno].bal<800 || acc[X->accno].bal-X->money<800)
      printf("\nCustomer %d cannot withdraw. Balance will drop below minimum requirement\n",X->num);
    else
    {
      int trans=rand()%500;
      acc[X->accno].bal-=X->money;
      bankBal-=X->money; 
      X->token=token;
      X->tid=trans;
      printf("\nCustomer %d finished transaction\n",X->num);
    }  
  }
  
  sem_post(&account[X->accno]);
  printf("\nCustomer %d is leaving the bank\n",X->num);
  sem_post(&counter[counterNum]);
  
  pthread_exit(NULL);
  
}



int main()
{
  int i;
  srand(time(NULL)); 
  for(i=0;i<N;i++)
  {
    sem_init(&counter[i],0,1);
  }
  
  for(i=0;i<A;i++)
    sem_init(&account[i],0,1);
  
  for(i=0;i<A;i++)
  {
    acc[i].accnum=i;
    acc[i].bal=0;
  }
  
  for(i=0;i<C;i++)
  {
    printf("\nEnter details for customer %d\n",i+1);
    printf("\nEnter the accnum, type of transaction (1 for credit 2 for debit), amount\n");
    scanf("%d %d %f",&customer[i].accno,&customer[i].type,&customer[i].money);
    acc[customer[i].accno].bal=1000.0;
    bankBal+=1000;
    customer[i].num=i+1;
  }
  printf("\nBank balance: %f\n",bankBal);
  
  for(i=0;i<C;i++)
    pthread_create(&cus[i],NULL,customFunc,(void *)&customer[i]);

  for(i=0;i<C;i++)
    pthread_join(cus[i],NULL);
    
    
    
  printf("\nAfter all transactions are completed. Transaction details:\n");
  printf("\nAccNo\tBalance\n");
  for(i=0;i<A;i++)
    if(acc[i].bal!=0)
      printf("%d\t%f\n",acc[i].accnum,acc[i].bal);
  printf("\nCustomer details\n");
  printf("\nSno\tTOT\tAccNo\tToken\tTid\tAmount\n");
  for(i=0;i<C;i++)
    printf("%d\t%d\t%d\t%d\t%d\t%f\n",customer[i].num,customer[i].type,customer[i].accno,customer[i].token,customer[i].tid,customer[i].money);
    
  printf("\nBank balance: %f\n",bankBal); 
  
  
  return(0);

}
