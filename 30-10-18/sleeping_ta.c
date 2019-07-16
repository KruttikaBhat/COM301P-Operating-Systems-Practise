#include<stdio.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>
#define N 15
#define WC 3

sem_t ta,student,officeChair,waitingChair;
int sleeping=1,done=0,numChairs=3,arr[]={0,1,2,3,4,5,6,7,8,9};

void *taFunc()
{
  printf("\nThe TA is sleeping\n");
  sem_wait(&ta);
  //printf("\nThe TA is woken up\n");
  while(!done)
  {
    //sleep(1);
    //printf("\nTA is helping a student\n");

    sleep(1);
    sem_post(&student);
  }
  printf("\nTA goes to sleep\n");
  pthread_exit(0);
}

void *studentFunc(void *arg)
{
  int num=*(int *)arg;
  sleep(1);
  printf("\nStudent %d comes near the TA's office\n",num+1);
  sem_wait(&waitingChair);
  numChairs--;
  while(numChairs<0)
  {
    printf("\nNo chairs available. Student %d leaves\n",num+1);
    sleep(2);
    printf("\nStudent %d comes again\n",num+1);
  }


  printf("\nStudent %d is waiting. Number of chairs left %d \n",num+1,numChairs);

  //sleep(1);

  sem_wait(&officeChair);
  sem_post(&waitingChair);
  numChairs++;
  printf("\nStudent %d enter TA's office\n",num+1);

  if(sleeping==1)
  {
    printf("\nStudent %d wakes up TA\n",num+1);
    sleeping=0;
    sem_post(&ta);
  }
  sem_wait(&student);
  printf("\nStudent %d sits in the office chair\n",num+1);
  //sleep(1);
  printf("\nTA is helping student %d\n",num+1);
  sem_post(&officeChair);


  pthread_exit(0);
}

int main()
{
  int i;
  sem_init(&ta,0,0);
  sem_init(&student,0,1);
  sem_init(&officeChair,0,1);
  sem_init(&waitingChair,0,3);

  pthread_t TA,t[N];
  pthread_create(&TA,NULL,taFunc,NULL);
  for(i=0;i<N;i++)
  {
    pthread_create(&t[i],NULL,studentFunc,(void *)&arr[i]);
    //sleep(1);
  }
  for(i=0;i<N;i++)
    pthread_join(t[i],NULL);
  done=1;
  sem_post(&ta);
  pthread_join(TA,NULL);
}
