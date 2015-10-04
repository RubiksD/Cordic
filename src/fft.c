#include <stdio.h>
#include <math.h>
#include "fft.h"
#include "cordic.h"

inline int bit_rev(int num,int N)
{
	int rev=0;
	while(N!=1){
		rev = (rev<<1)|(num&1);
		num = num>>1;
		N=N/2;
	}
	return rev;
}

void fft_Npt(int *input, int *X_out, int *Y_out,int N)
{
	int i,j,k;
	int offset=0;
	int Set_Count=1;
#ifdef DOUBLE_CALCULATIONS
	double theta = convert_to_cordic_weight(2*pi/N);
	double Set_theta,Butterfly_theta;
#else
	int theta = convert_to_cordic_weight(2*pi/N);
	int Set_theta,Butterfly_theta;
#endif
	int X_in[1024],Y_in[1024];
	int X_temp[3],Y_temp[3];
	for(i=0;i<N;i++){
		X_in[i]=input[i];
		Y_in[i]=0;
	}

	Set_theta = theta;
	for(i=N/2;i>=1;i=i/2){
		offset = 0;
		for(j=0;j<Set_Count;j++){
			Butterfly_theta = 0;
			for(k=0;k<i;k++){
				X_temp[0] = X_in[k+offset]+X_in[k+i+offset];
				Y_temp[0] = Y_in[k+offset]+Y_in[k+i+offset];

				X_temp[1] = X_in[k+offset]-X_in[k+i+offset];
				Y_temp[1] = Y_in[k+offset]-Y_in[k+i+offset];

				//X_temp[2] = (X_temp[1]*cos(Butterfly_theta)) + (Y_temp[1]*sin(Butterfly_theta));
				//Y_temp[2] = (-(X_temp[1]*sin(Butterfly_theta))) + (Y_temp[1]*cos(Butterfly_theta));
#ifdef DOUBLE_CALCULATIONS
				cordic_rotate_double(&X_temp[1],&Y_temp[1],-Butterfly_theta);
#else
				cordic_rotate_int(&X_temp[1],&Y_temp[1],-Butterfly_theta);
#endif
				X_temp[2] = X_temp[1];
				Y_temp[2] = Y_temp[1];

				X_in[k+offset] = X_temp[0]>>1;
				Y_in[k+offset] = Y_temp[0]>>1;
				X_in[k+i+offset] = X_temp[2]>>1;
				Y_in[k+i+offset] = Y_temp[2]>>1;

				Butterfly_theta += Set_theta;
			}
			offset +=i*2;
		}
		Set_Count = Set_Count*2;
		Set_theta = Set_theta*2;
	//	printf("---------\n");
	}
	for(i=0;i<N;i++){
		j = bit_rev(i,N);
		X_out[i] = X_in[j];
		Y_out[i] = Y_in[j];
	}
}

void ifft_Npt(int *inputX, int *inputY, int *X_out, int *Y_out,int N)
{
	int i,j,k;
	int offset=0;
	int Set_Count=1;
#ifdef DOUBLE_CALCULATIONS
	double theta = convert_to_cordic_weight(2*pi/N);
	double Set_theta,Butterfly_theta;
#else
	int theta = convert_to_cordic_weight(2*pi/N);
	int Set_theta,Butterfly_theta;
#endif
	int X_in[1024],Y_in[1024];
	int X_temp[3],Y_temp[3];
	for(i=0;i<N;i++){
		X_in[i]=inputX[i];
		Y_in[i]=inputY[i];
	}

	Set_theta = theta;
	for(i=N/2;i>=1;i=i/2){
		offset = 0;
		for(j=0;j<Set_Count;j++){
			Butterfly_theta = 0;
			for(k=0;k<i;k++){
				X_temp[0] = X_in[k+offset]+X_in[k+i+offset];
				Y_temp[0] = Y_in[k+offset]+Y_in[k+i+offset];

				X_temp[1] = X_in[k+offset]-X_in[k+i+offset];
				Y_temp[1] = Y_in[k+offset]-Y_in[k+i+offset];

				//X_temp[2] = (X_temp[1]*cos(Butterfly_theta)) + (Y_temp[1]*sin(Butterfly_theta));
				//Y_temp[2] = (-(X_temp[1]*sin(Butterfly_theta))) + (Y_temp[1]*cos(Butterfly_theta));
#ifdef DOUBLE_CALCULATIONS
				cordic_rotate_double(&X_temp[1],&Y_temp[1],-Butterfly_theta);
#else
				cordic_rotate_int(&X_temp[1],&Y_temp[1],-Butterfly_theta);
#endif
				X_temp[2] = X_temp[1];
				Y_temp[2] = Y_temp[1];

				X_in[k+offset] = X_temp[0]>>1;
				Y_in[k+offset] = Y_temp[0]>>1;
				X_in[k+i+offset] = X_temp[2]>>1;
				Y_in[k+i+offset] = Y_temp[2]>>1;

				Butterfly_theta += Set_theta;
			}
			offset +=i*2;
		}
		Set_Count = Set_Count*2;
		Set_theta = Set_theta*2;
	//	printf("---------\n");
	}
	for(i=0;i<N;i++){
		j = bit_rev(i,N);
		X_out[i] = X_in[j];
		Y_out[i] = Y_in[j];
	}
}
void fft_Npt_DiT(int *input, double *X_out, double *Y_out,int N)
{
	int i,j,k;
	int offset=0;
	int Set_Count=1;
	double theta = 2*pi/N;
	double X_in[1024],Y_in[1024];
	double X_temp[3],Y_temp[3];
	for(i=0;i<N;i++){
		j = bit_rev(i,N);
		X_in[j]=(double)input[i];
		Y_in[j]=0;
	}

	for(i=N/2;i>=1;i=i/2){
		offset = 0;
		for(j=0;j<N/(i*2);j++){
			for(k=0;k<i;k++){
				X_temp[0] = X_in[k+offset]+X_in[k+i+offset];
				Y_temp[0] = Y_in[k+offset]+Y_in[k+i+offset];

				X_temp[1] = X_in[k+offset]-X_in[k+i+offset];
				Y_temp[1] = Y_in[k+offset]-Y_in[k+i+offset];

				X_temp[2] = (X_temp[1]*cos(theta*Set_Count*k)) + (Y_temp[1]*sin(theta*Set_Count*k));
				Y_temp[2] = (-(X_temp[1]*sin(theta*Set_Count*k))) + (Y_temp[1]*cos(theta*Set_Count*k));

				X_in[k+offset] = X_temp[0];
				Y_in[k+offset] = Y_temp[0];
				X_in[k+i+offset] = X_temp[2];
				Y_in[k+i+offset] = Y_temp[2];
			}
			offset +=i*2;
		}
		Set_Count = Set_Count*2;
		printf("---------\n");
	}
}
