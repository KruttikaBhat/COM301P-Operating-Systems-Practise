#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>

int n;
float arr[25][25],detvalue;

float caldet(float a[25][25], float k)
{
  float s = 1, det = 0, b[25][25];
  int i, j, q, r, c;
  if (k == 1)
  {
    return (a[0][0]);
  }
  else
    {
     det = 0;
     for (c = 0; c < k; c++)
       {
        q = 0;
        r = 0;
        for (i = 0;i < k; i++)
          {
            for (j = 0 ;j < k; j++)
              {
                b[i][j] = 0;
                if (i != 0 && j != c)
                 {
                   b[q][r] = a[i][j];
                   if (r < (k - 2))
                    r++;
                   else
                    {
                     r = 0;
                     q++;
                     }
                   }
               }
             }
          det = det + s * (a[0][c] * caldet(b, k - 1));
          s = -1 * s;
          }
    }
    return det;
}


void *det()
{
  detvalue=caldet(arr,n);
  if (detvalue == 0)
   printf("\nInverse of Entered Matrix is not possible\n");
  pthread_exit(0);
}

void transpose(float num[25][25], float fac[25][25], float r)
{
  int i, j;
  float b[25][25], inverse[25][25], d;
  for (i = 0;i < r; i++)
  {
    for (j = 0;j < r; j++)
    {
      b[i][j] = fac[j][i];
    }
  }

  for (i = 0;i < r; i++)
  {
    for (j = 0;j < r; j++)
    {
      inverse[i][j] = b[i][j] / detvalue;
    }
  }
  printf("\n\n\nThe inverse of matrix is : \n");
  for (i = 0;i < r; i++)
  {
    for (j = 0;j < r; j++)
    {
      printf("\t%f", inverse[i][j]);
    }
    printf("\n");
  }
}

void *cofac()
{
  float b[25][25], fac[25][25];
  int p, q, r, s, i, j;
  for (q = 0;q < n; q++)
  {
   for (p = 0;p < n; p++)
    {
     r = 0;
     s = 0;
     for (i = 0;i < n; i++)
     {
       for (j = 0;j < n; j++)
        {
          if (i != q && j != p)
          {
            b[r][s] = arr[i][j];
            if (s < (n - 2))
             s++;
            else
             {
               s = 0;
               r++;
               }
            }
        }
      }
      fac[q][p] = pow(-1, q + p) * caldet(b, n - 1);
    }
  }
  transpose(arr, fac, n);
  pthread_exit(0);
}

int main()
{
  pthread_t thread1,thread2;
  int i,j;
  printf("Enter the size of the matrix\n");
  scanf("%d",&n);
  printf("Enter the matrix\n");
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      scanf("%f",&arr[i][j]);
  printf("Entered array is\n");
  for(i=0;i<n;i++)
  {
    for(j=0;j<n;j++)
        printf("%f ",arr[i][j]);
    printf("\n");
  }
  if(pthread_create(&thread1,NULL,det,NULL)<0)
  {
    fprintf(stderr,"\nThread not created\n");
    exit(0);
  }
  if(pthread_create(&thread2,NULL,cofac,NULL)<0)
  {
    fprintf(stderr,"\nThread not created\n");
    exit(0);
  }
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  return 0;
}
