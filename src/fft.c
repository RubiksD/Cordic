#include <stdio.h>
#include <math.h>
#include "../include/fft.h"

int bit_rev(int num){
	int rev=0;
	int count = 6;
	while(count){
		rev = (rev<<1)|(num&1);
		num = num>>1;
		count--;
	}
	return rev;
}

void fft_64pt(int *input, double *X_out, double *Y_out)
{
	int i,j,k;
	double X_in[64],Y_in[64];
	double X_temp[3],Y_temp[3];
	for(i=0;i<64;i++){
		X_in[i]=(double)input[i];
		Y_in[i]=0;
	}

	for(i=64/2;i>=1;i=i/2){
		for(j=0;j<64/(i*2);j++){
			for(k=0;k<i;k++){
				X_temp[0] = X_in[k+(j*i*2)]+X_in[k+i+(j*i*2)];
				Y_temp[0] = Y_in[k+(j*i*2)]+Y_in[k+i+(j*i*2)];

				X_temp[1] = X_in[k+(j*i*2)]-X_in[k+i+(j*i*2)];
				Y_temp[1] = Y_in[k+(j*i*2)]-Y_in[k+i+(j*i*2)];

				X_temp[2] = (X_temp[1]*cos(((k*pi)*2)/64)) + (Y_temp[1]*sin(((k*pi)*2)/64));
				Y_temp[2] = (-(X_temp[1]*sin(((k*pi)*2)/64))) + (Y_temp[1]*cos(((k*pi)*2)/64));
				X_temp[2] = (X_temp[1]*cos((k*pi)/i)) + (Y_temp[1]*sin((k*pi)/i));
				Y_temp[2] = (-(X_temp[1]*sin((k*pi)/i))) + (Y_temp[1]*cos((k*pi)/i));
				
				X_in[k+(j*i*2)] = X_temp[0];
				Y_in[k+(j*i*2)] = Y_temp[0];
				X_in[k+i+(j*i*2)] = X_temp[2];
				Y_in[k+i+(j*i*2)] = Y_temp[2];
			}
		}
		printf("---------\n");
	}
	for(i=0;i<64;i++){
	j = bit_rev(i);
	X_out[i] = X_in[j];
	Y_out[i] = Y_in[j];
	}
}
