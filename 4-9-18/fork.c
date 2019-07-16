#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
  //fork basic example
  /*printf("Hello \n");
  fork();
  printf("World \n");
  fork();
  printf("OS course \n");
  fork();
  printf("IIITDM\n");*/
  //checking return value of fork
  /*if(fork()==0)
    printf("child");
  else
    printf("parent");*/
  //changing local variable with fork, parent has x=0\nchild has x=2 is printed
  /*int x=1;
  if(fork()==0)
      printf("Child has x=%d\n",++x);
  else
      printf("Parent has x=%d\n",--x);*/
  //IIIT prints 6 times
  /*
  int pid=fork();
  if(pid!=0)
    fork();
  fork();
  printf("IIIT\n");*/
  //Hi 16 times
/*
  fork();
  fork();
  fork();
  fork();
  printf("Hi\n");*/
  //main parent and Child
  /*int pid=fork();
  if(pid==0)
  {
    fork();
    printf("Child\n");
  }
  else if(pid>0)
    printf("Parent\n");
  printf("Main parent\n");*/
  /*int pid=fork();
  if(pid==0)
  {
    printf("child pid: %d\n",getpid());
    printf("child ppid: %d\n",getppid());
  }
  else if(pid>0)
  {
    printf("pid>0 pid: %d\n",getpid());
    printf("pid>0 ppid: %d\n",getppid());
  }*/
  //tutorial 4
  /*if(fork()&&fork())
    fork();
  if(fork()||fork())
    fork();
  printf("*\n");  */
  //tutorial 5-> 8 stars
  /*for(int i=1;i<=3;i++)
    fork();
  printf("*\n");*/
  //tutorial 6: with \n->14 stars;7: without \n->24 stars
  for(int i=1;i<=3;i++)
  {
    fork();
    printf("*");
  }
  //tutorial 8->3 stars
  /*for(int i=0;i<2;i++)
  {
    if(fork()==0)
      printf("%d\n",i);
  }
  //textbook pg. 106
  /*int pid=fork();
  if(pid<0)
  {
    fprintf(stderr, "Fork failed");
    exit(-1);
  }
  else if(pid==0)
    execlp("/bin/ls","ls","-al",NULL);
  else if(pid>0)
  {
    wait(NULL);
    printf("Child complete");
    exit(0);
  }*/
  return 0;
}
