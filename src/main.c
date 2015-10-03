#include <stdio.h>
#include <math.h>
#ifdef MEASURE_TIME
#include <sys/time.h>
#endif
#include "fft.h"
#include "cordic.h"

int fft_outX[N_POINT],fft_outY[N_POINT];
int ifft_outX[N_POINT],ifft_outY[N_POINT];
int main()
{
	int X_in,Y_in;
#ifdef DISPLAY_OUTPUT
	double F_res = (double)F_SAMPLE/N_POINT ;
#endif

	int fft_in[N_POINT];
	int fft_out[N_POINT];
	int ifft_out[N_POINT];
	
	int word_mag;
	int word_sign;
	int j,k;
	double scale;
#ifdef MEASURE_TIME
	struct timeval tv1,tv2;
#endif

	create_lookup_table();
	calculate_rotation_angle(F_SAMPLE,F_OUT,&word_mag,&word_sign,&scale);
	printf("Rotation Magnitude = 0x%x\nRotation sign = 0x%x\nScale factor = %lf\n",word_mag,word_sign,scale);
	
	X_in = 0x8000;
	printf("Amplitude = %d\n",X_in);
	Y_in = 0;
	
	for(j=0;j<9999;j++){
		cordic_rotate(word_mag,word_sign,scale,&X_in,&Y_in);
		fft_in[j&(N_POINT-1)]= X_in;
		if(((j%(N_POINT-1)) == 0) && (j>0)){
			printf("\n");
#ifdef MEASURE_TIME
			gettimeofday(&tv1,NULL);
#endif
			fft_Npt(fft_in,fft_outX,fft_outY,N_POINT);
			ifft_Npt(fft_outX,fft_outY,ifft_outX,ifft_outY,N_POINT);
			for(k=0;k<N_POINT;k=k+2){
				fft_out[k] = cordic_vector(fft_outX[k],fft_outY[k]);
				fft_out[k+1] = cordic_vector(fft_outX[k+1],fft_outY[k+1]);
				//ifft_out[k] = cordic_vector(ifft_outX[k],ifft_outY[k]);
				//ifft_out[k+1] = cordic_vector(ifft_outX[k+1],ifft_outY[k+1]);
				ifft_out[k] = ifft_outX[k];
				ifft_out[k+1] = ifft_outX[k+1];
			}
#ifdef MEASURE_TIME
			gettimeofday(&tv2,NULL);
			printf("Time1 = %ld.%ld sec\nTime1 = %ld.%ld sec\n",tv2.tv_sec,tv2.tv_usec,tv1.tv_sec,tv1.tv_usec);
			printf("Time taken = %ld usec\n",tv2.tv_usec-tv1.tv_usec);
#endif
#ifdef DISPLAY_OUTPUT
			for(k=0;k<N_POINT;k++){
				printf("%.8f\t%d\t%10d\n",((k*1.0)/F_SAMPLE),ifft_out[k],fft_in[k]);
			}
			for(k=0;k<N_POINT;k++){
				printf("%.2f\t%d\t%10d\n",k*F_res,fft_out[k],fft_in[k]);
			}
#endif
			printf("\n\n");
		}
	}

	return 0;
}
