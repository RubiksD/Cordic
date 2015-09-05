#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include "../include/fft.h"
#include "../include/cordic.h"

double fft_outX[N_POINT],fft_outY[N_POINT];

int main()
{
	int X_in,Y_in;
	double T_sample = 1.0/F_SAMPLE;
	double T_total = N_POINT*T_sample;
	double F_res = 1/T_total;//! F_SAMPLE/N_POINT

	int fft_in[N_POINT];
	int fft_out[N_POINT];
	
	int word_mag;
	int word_sign;
	int j,k;
	double scale;
	struct timeval tv1,tv2;
	calculate_rotation_angle(F_SAMPLE,F_OUT,&word_mag,&word_sign,&scale);
	printf("Rotation Magnitude = 0x%x\nRotation sign = 0x%x\nScale factor = %lf\n",word_mag,word_sign,scale);
	
	X_in = 0x8000;
	printf("Amplitude = %d\n",X_in);
	Y_in = 0;
	
	for(j=0;j<9999;j++){
		cordic_rotate(word_mag,word_sign,scale,&X_in,&Y_in);
		fft_in[j&(N_POINT-1)]= X_in;
		if((j%(N_POINT) == 0) && (j>0)){
			printf("\n");
			gettimeofday(&tv1,NULL);
			fft_Npt(fft_in,fft_outX,fft_outY,N_POINT);
			for(k=0;k<N_POINT;k=k+2){
				fft_out[k] = cordic_vector((int)fft_outX[k],(int)fft_outY[k]);
				fft_out[k+1] = cordic_vector((int)fft_outX[k+1],(int)fft_outY[k+1]);
			}
			gettimeofday(&tv2,NULL);
			printf("Time1 = %ld.%ld sec\nTime1 = %ld.%ld sec\n",tv2.tv_sec,tv2.tv_usec,tv1.tv_sec,tv1.tv_usec);
			printf("Time taken = %ld usec\n",tv2.tv_usec-tv1.tv_usec);
			for(k=0;k<N_POINT;k++){
				printf("%f\t%d\t%10d\n",k*F_res,fft_out[k]/N_POINT,fft_in[k]);
			}
			printf("\n\n");
		}
	}

	return 0;
}
