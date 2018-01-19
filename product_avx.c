#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "immintrin.h" 

#define SIZE 320
#define BLOC_SIZE 64

void affiche(float* a){
  for(int i=0;i<SIZE;++i){
    for(int j=0;j<SIZE;++j){
      printf("%f ",a[i*SIZE+j]);
    }
    printf("\n");
  }
}

void prod(float *a,float *b,float *tmp)  {
  int i,j,k,p;
  /* affiche(a); */
  /* printf("\n"); */
  /* affiche(b); */
  for (i=0; i<SIZE; i++)
    for (j=0; j<SIZE; j++)
      tmp[i*SIZE+j]=0;
  
  for (i=0; i<SIZE; i++)
    {
      for (k=0; k<SIZE; k++)
	{
	  __m256 aik = _mm256_set1_ps(a[i*SIZE+k]);
	  for (j=0; j<SIZE; j+=8)
	    {
	      __m256 bk = _mm256_set_ps(b[k*SIZE+j+7],b[k*SIZE+j+6],b[k*SIZE+j+5],
					b[k*SIZE+j+4],b[k*SIZE+j+3],b[k*SIZE+j+2],
					b[k*SIZE+j+1],b[k*SIZE+j]); 
	      
	      /* __m256 tmpk = _mm256_set_ps(tmp[i*SIZE+j+7],tmp[i*SIZE+j+6],tmp[i*SIZE+j+5], */
	      /* 				tmp[i*SIZE+j+4],tmp[i*SIZE+j+3],tmp[i*SIZE+j+2], */
	      /* 				tmp[i*SIZE+j+1],tmp[i*SIZE+j]);  */
	      
	      /* __m256 res = _mm256_fmadd_ps(aik,bk,tmpk); */
	      __m256 res = _mm256_mul_ps(aik,bk);
	      float store[8];
	      _mm256_store_ps(store,res);
	      for(p=0;p<8;p++){
		tmp[i*SIZE+p] += store[p];
		//printf("%f \n",store[p]);
	      }
	      //tmp[i*SIZE+j] += a[i*SIZE+k]*b[k*SIZE+j];			    
	    }
	}
    }
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
  fprintf(stdout,"\n%f",s);
  free(a);
  free(b);
  free(c);
  return 0;
}
