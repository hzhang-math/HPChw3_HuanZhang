/******************************************************************************
* FILE: omp_bug6.c
* DESCRIPTION:
*   This program compiles and runs fine, but produces the wrong result.
*   Compare to omp_orphan.c.
* AUTHOR: Blaise Barney  6/05
* LAST REVISED: 06/30/05
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define VECLEN 100

float a[VECLEN], b[VECLEN];

float dotprod ()
{
int i,tid;
float sum=0.0;
#pragma omp parallel shared(sum) 
{
tid = omp_get_thread_num();
#pragma omp for reduction(+:sum)
  for (i=0; i < VECLEN; i++)
    {
    sum = sum + (a[i]*b[i]);
    printf("  tid= %d i=%d\n",tid,i);
    }
}
return sum;
}

int main (int argc, char *argv[]) {
int i;
float sum;

for (i=0; i < VECLEN; i++)
  a[i] = b[i] = 1.0 * i;
sum = 0.0;

//#pragma omp parallel shared(sum)
//It declares the sum in wrong scope. It declares sum outside of the function as shared, but inside the function a variable with same name is defined again. As a function parameter, it has automatic storage duration, so it is by default a private variable. Therefore I re-private it inside the function and it is working well.
sum=dotprod();

printf("Sum = %f\n",sum);

}

