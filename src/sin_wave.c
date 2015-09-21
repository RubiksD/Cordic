#include <stdio.h>
#include <math.h>
#ifdef MEASURE_TIME
#include <sys/time.h>
#endif
#include "fft.h"
#include "cordic.h"

int main()
{
	int X_in,Y_in;

	int fft_in[N_POINT];
	
	int word_mag;
	int word_sign;
	int j,k;
	double scale;
#ifdef MEASURE_TIME
	struct timeval tv1,tv2;
#endif

	calculate_rotation_angle(F_SAMPLE,F_OUT,&word_mag,&word_sign,&scale);
	printf("Rotation Magnitude = 0x%x\nRotation sign = 0x%x\nScale factor = %lf\n",word_mag,word_sign,scale);
	
	X_in = 0x8000;
	printf("Amplitude = %d\n",X_in);
	Y_in = 0;
	
	for(j=0;j<9999;j++){
		cordic_rotate(word_mag,word_sign,scale,&X_in,&Y_in);
		fft_in[j&(N_POINT-1)]= X_in;
#ifdef DISPLAY_OUTPUT
		if(((j%N_POINT) == 0) && (j>0)){
			for(k=0;k<N_POINT;k++){
				printf("%d\n",fft_in[k]);
			}
			printf("\n");
		}
#endif
	}

	return 0;
}
