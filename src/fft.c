#include <stdio.h>
#include <math.h>
#include "../include/fft.h"

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
/*
				printf("%d, %d, %d, %d, %d, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf\n",
				i,j,k,k+(j*i*2),k+i+(j*i*2),X_temp[0],X_temp[1],Y_temp[0],Y_temp[1]
				,X_in[k+(j*i*2)],X_in[k+i+(j*i*2)],Y_in[k+(j*i*2)],Y_in[k+i+(j*i*2)]
				);
				printf("%lf, %lf, %lf, %lf\n",X_in[k+(j*i*2)],X_in[k+i+(j*i*2)],Y_in[k+(j*i*2)],Y_in[k+i+(j*i*2)]);
*/

				printf("%d, %d, %d, %d, %d, %f, %f, %f, %f\n",
				i,j,k,k+(j*i*2),k+i+(j*i*2),X_temp[0],X_temp[2],Y_temp[0],Y_temp[2]
				);

//				printf("%lf, %lf\n",cos(((k*pi)*2)/64),sin(((k*pi)*2)/64));
				X_in[k+(j*i*2)] = X_temp[0];
				Y_in[k+(j*i*2)] = Y_temp[0];
				X_in[k+i+(j*i*2)] = X_temp[2];
				Y_in[k+i+(j*i*2)] = Y_temp[2];
			}
		}
		printf("---------\n");
	}

	for(i=4;i<=64;i=i*2){
		for(j=0;j<(64/i);j++){
			for(k=0;k<(i);k=k+2){
					X_out[k+(i*j)] = X_in[(k/2)+(i*j)];
					Y_out[k+(i*j)] = Y_in[(k/2)+(i*j)];
					X_out[(k+1)+(i*j)] = X_in[((k+i)/2)+(i*j)];
					Y_out[(k+1)+(i*j)] = Y_in[((k+i)/2)+(i*j)];
//					printf("%d, %d, %d, %d, %d, %d, %d\n",i,j,k,k+(i*j),(k+1)+(i*j),(k/2)+(i*j),((k+i)/2)+(i*j));
			}
			if(i!=64){
				for(k=0;k<i;k++){
					X_in[k+(i*j)] = X_out[k+(i*j)];
					Y_in[k+(i*j)] = Y_out[k+(i*j)];
				}
			}	
		}
	}
}
