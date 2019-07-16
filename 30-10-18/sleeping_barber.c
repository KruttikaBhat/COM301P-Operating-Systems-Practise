#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#define N 10
sem_t barber,customer,barberchair,chairs;
int done=0,numChairs=5,arr[]={0,1,2,3,4,5,6,7,8,9};

void *barberFunc()
{

  printf("The barber is sleeping\n");
  sem_wait(&barber);
  printf("\nThe barber is woken up\n");
  while(!done)
  {
     //printf("\nBarber is woken up\n");

     printf("\nBarber is cutting hair\n");
     sleep(1);

     //now other customers can come get a haircut
     sem_post(&customer);
  }
  printf("\nThe barber is sleeping\n");
  pthread_exit(NULL);
}

void *customerFunc(void * arg)
{
  int num = *(int *)arg;
  sleep(1);
  printf("\nCustomer %d enters the shop\n",num+1);
  //occupy a waiting chair
  sem_wait(&chairs);
  numChairs--;
  if(numChairs<0)
     printf("\nNo chairs available. Customer %d leaves the shop\n",num+1);

  else
  {
    printf("\nCustomer %d occupies a chair in waiting room. Number of chairs left %d\n",num+1,numChairs);
    //Occupies barber's chair
    sem_wait(&barberchair);
    //Free a waiting room chair
    sem_post(&chairs);
    numChairs++;
    printf("\nCustomer %d leaves the waiting room and sits in the barber's chair\n",num+1);
    //barber will cut hair
    sem_post(&barber);
    //waits ensures no other customer comes while current one is getting cut
    sem_wait(&customer);
    //free barber chair
    sem_post(&barberchair);
    printf("\nCustomer %d is leaving the barber shop\n",num+1);
  }

  pthread_exit(NULL);

}

int main()
{
  int i;
  pthread_t t[N],B;
  sem_init(&barber,0,0);
  sem_init(&customer,0,0);
  sem_init(&barberchair,0,1);
  sem_init(&chairs,0,7);


  pthread_create(&B,NULL,barberFunc,NULL);
  for(i=0;i<N;i++)
  {
    pthread_create(&t[i],NULL,customerFunc,(void *)&arr[i]);
    //sleep(1);
  }
  for(i=0;i<N;i++)
    pthread_join(t[i],NULL);

  done=1;
  sem_post(&barber);
  pthread_join(B,NULL);


  return 0;
}
