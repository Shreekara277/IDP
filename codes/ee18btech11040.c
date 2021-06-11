#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include<math.h>
#define PI 3.141592653
complex double* fft(complex double* x, int n){
    if(n == 1)
    {
        return x;
        
    }
    complex double* xe = malloc((n/2)*sizeof(complex double));
    complex double* xo = malloc((n/2)*sizeof(complex double));
    
    for(int i=0;i<n/2;i++)
    {
        xe[i] = x[2*i];
        xo[i] = x[2*i+1];
        
    }
    complex double* ye = fft(xe,n/2);
    complex double* yo = fft(xo,n/2);
    complex double* y = malloc((n)*sizeof(complex double));
    for(int i=0;i<n/2;i++)
    {
		complex double w = cos(2*PI*i/n) - I*sin(2*PI*i/n);
		y[i] = ye[i] + w*yo[i];
		y[i + n/2] = ye[i] - w*yo[i];
    }
    free(ye);
    free(yo);
    return y;
    
}
    

complex double* ifft(complex double* y, int n)
{
    if(n==1)
    {
        return y;
        
    }
    complex double* xe = malloc((n/2)*sizeof(complex double));
    complex double* xo = malloc((n/2)*sizeof(complex double));
    int i;
    for(i=0;i<n/2;i++)
    {
        xe[i] = y[2*i];
        xo[i] = y[2*i+1];
        
    }
    complex double* ye = ifft(xe,n/2);
    complex double* yo = ifft(xo,n/2);
    complex double* x1 = malloc((n)*sizeof(complex double));
    for(i=0;i<n/2;i++)
    {
        complex double w = cos(2*PI*i/n) + I*sin(2*PI*i/n);
		x1[i] = ye[i] + w*yo[i];
		x1[i + n/2] = ye[i] - w*yo[i];
    }
    free(ye);
    free(yo);
    return x1;
    
    
    
}

int main() 
{
	int n=8;
	complex double  x[16] = {7,2,13,4,5,2,7,8,1,5,7,4,3,2,8,9};  
	complex double* y = fft(x,n);
	complex double* x1 = ifft(y,n); 

	for(int i=0;i<n;i++)
	{
		printf( "%f %f\n", creal(y[i]), cimag(y[i]));

	}

	for(int i=0;i<n;i++)
	{
		printf( "%f %f\n", creal(x1[i])/n, cimag(x1[i])/n);
	}
    
    
    return 0;
}
