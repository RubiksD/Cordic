#include <stdio.h>
#include <math.h>
#include "../include/fft.h"


void calculate_rotation_angle(double f_sample, double f_in,int *word_mag, int *word_sign,double *scale_out)
{
	double points;
	double angle;
	double temp_tan = 1;
	double temp_angle = atan(temp_tan);
	double cur_angle = 0;
	double scale=1;
	int i;
	double temp = 1;
	points = f_sample*1.0/f_in;
	angle = (2.0*pi)/points;
	scale = 1;
	
	for(i=0;i<32;i++){
		if(cur_angle == angle){
			break;
		} else{ 
			if(angle > cur_angle){
				*word_mag |= BIT((31-i));
				*word_sign |= BIT((31-i));
				cur_angle += temp_angle;
			} else if(angle < cur_angle){
				*word_mag |= BIT((31-i));
				cur_angle -= temp_angle;
			}
			scale = scale /(sqrt((1 + (temp_tan*temp_tan))));
			temp_tan = temp_tan /2;
			temp_angle = atan(temp_tan);
			temp = temp /2;
		}

	}
	*scale_out = scale;
}

double fft_outX[64],fft_outY[64];

int main()
{
	int X_in,Y_in;
	int X_out,Y_out;

	int fft_in[64];
	
	int word_mag;
	int word_sign;
	int i,j,k;
	double scale;

	calculate_rotation_angle(F_SAMPLE,F_OUT,&word_mag,&word_sign,&scale);
	printf("Rotation Magnitude = 0x%x\nRotation sign = 0x%x\nScale factor = %lf\n",word_mag,word_sign,scale);
	
	X_in = 0x8000;
	printf("Amplitude = %d\n",X_in);
	Y_in = 0;
	
	for(j=0;j<999;j++){
		for(i=31;(word_mag & BIT(i)) && (i>=0);i--){
			if(word_sign & BIT(i)){
				X_out = X_in - (Y_in >> (31-i));
				Y_out = (X_in >> (31-i)) + Y_in ;
			} else {
				X_out = X_in + (Y_in >> (31-i));
				Y_out = -(X_in >> (31-i)) + Y_in;
			}
			X_in = X_out;
			Y_in = Y_out;
		}
		X_in *= scale;
		Y_in *= scale;
		fft_in[j&63]= X_in;
		if((j%63 == 0) && (j>0)){
			printf("\n");
			fft_64pt(fft_in,fft_outX,fft_outY);
			for(k=0;k<64;k++){
				printf("%lf\n",sqrt((fft_outX[k]*fft_outX[k])+(fft_outY[k]*fft_outY[k])));
			}
			printf("\n\n");
		}
	}

	return 0;
}
