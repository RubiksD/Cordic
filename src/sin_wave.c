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

	int sin_wave[N_POINT];
	
	int word_mag;
	int word_sign;
	int j,k;
	double scale;
#ifdef MEASURE_TIME
	struct timeval tv1,tv2;
#endif
	
	int f_sample;
	int f_out;
	int arguments_recieved=0;

	while(!arguments_recieved){
		printf("Enter sampling frequency:");
		while(!(scanf("%d",&f_sample)));
		printf("Enter sine wave frequency:");
		while(!(scanf("%d",&f_out)));
		if(f_sample > 4*f_out){
			arguments_recieved = 1;
		}
	}
	calculate_rotation_angle(f_sample,f_out,&word_mag,&word_sign,&scale);
	printf("Rotation Magnitude = 0x%x\nRotation sign = 0x%x\nScale factor = %lf\n",word_mag,word_sign,scale);
	
	X_in = 0x8000;
	printf("Amplitude = %d\n",X_in);
	Y_in = 0;
	
	for(j=0;j<9999;j++){
		cordic_rotate(word_mag,word_sign,scale,&X_in,&Y_in);
		sin_wave[j&(N_POINT-1)]= X_in;
#ifdef DISPLAY_OUTPUT
		if(((j%N_POINT) == (N_POINT-1)) && (j>0)){
			for(k=0;k<N_POINT;k++){
				printf("%d\t%d\n",j,sin_wave[k]);
			}
		}
#endif
	}

	return 0;
}
