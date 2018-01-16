#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 10

void prod(float *a,float *b,float *tmp)  {
  int i,j,k;
  for (i=0; i<SIZE; i++)
    for (j=0; j<SIZE; j++)
      tmp[i*SIZE+j]=0;
      for (i=0; i<SIZE; i++)
	for (k=0; k<SIZE; k++)
	  for (j=0; j<SIZE; j++)
	tmp[i*SIZE+j] += a[i*SIZE+k]*b[k*SIZE+j];			    
}
void sum(float *a,float *b,float *tmp)  {
  int i,j;
  for (i=0; i<SIZE; i++)
    for (j=0; j<SIZE; j++)
	tmp[i*SIZE+j] = a[i*SIZE+j]+b[i*SIZE+j];;			    
}
void prodpoly(float *a,float *b,float *c)  {
  int k;
  float *tmp=(float*)malloc(sizeof(float)*SIZE*SIZE);
  for (k=0; k<SIZE; k++)  {  
    prod(&a[k*SIZE*SIZE],c,tmp);
    sum(tmp,b,c);
  }
  free(tmp);
}
 int main() {
   int i,j,k;
   float *a,*b,*c;
  float s=0;
  a=(float *)malloc(sizeof(float)*SIZE*SIZE*SIZE);
  b=(float*)malloc(sizeof(float)*SIZE*SIZE);
  c=(float*)malloc(sizeof(float)*SIZE*SIZE);
  /* Initialization */
  for (i=0; i<SIZE; i++)    
    for (j=0; j<SIZE; j++)    
      c[i*SIZE+j]=b[i*SIZE+j]=i+1./(j+1);
  for (k=0; k<SIZE; k++)    
    for (i=0; i<SIZE; i++)
      for (j=0; j<SIZE; j++)    
	a[k*SIZE*SIZE+i*SIZE+j]=i+j+k;
  
  prodpoly(a,b,c);
  for (i=0; i<SIZE; i++)    
    for (j=0; j<SIZE; j++)    
      s+=c[i*SIZE+j];
  fprintf(stderr,"\n%f",s);
  free(a);
  free(b);
  free(c);
  return 0;
}
