#include <stdio.h>
#include <math.h>
#include "../include/cordic.h"

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

void cordic_rotate(int word_mag, int word_sign,double scale,int *X_in,int *Y_in)
{
	int i;
	int X_out,Y_out;
	for(i=31;(word_mag & BIT(i)) && (i>=0);i--){
		if(word_sign & BIT(i)){
			X_out = *X_in - (*Y_in >> (31-i));
			Y_out = (*X_in >> (31-i)) + *Y_in ;
		} else {
			X_out = *X_in + (*Y_in >> (31-i));
			Y_out = -(*X_in >> (31-i)) + *Y_in;
		}
		*X_in = X_out;
		*Y_in = Y_out;
	}
	*X_in *= scale;
	*Y_in *= scale;
}

void cordic_rotate_2(int *X_in,int *Y_in,double angle)
{
	int i;
	int X_out,Y_out;
	int change_sign =0;
	double error=angle;
	double cur_tan = 1;
	double scale = 1;
	if( (angle > (pi/2)) && ( angle < pi)){
		error = error - pi;
		change_sign = 1;
	} else if((angle < (-pi/2)) && ( angle > -pi)){
		error = error + pi;
		change_sign = 1;
	}
	for(i=0;(error) && (i<32);i++){
		if(error > 0){
			X_out = *X_in - (*Y_in >> i);
			Y_out = (*X_in >> i) + *Y_in ;
			error -= atan(cur_tan);
		} else {
			X_out = *X_in + (*Y_in >> i);
			Y_out = -(*X_in >> i) + *Y_in;
			error += atan(cur_tan);
		}
		scale = scale/(1+(cur_tan*cur_tan));
		cur_tan = cur_tan/2;
		*X_in = X_out;
		*Y_in = Y_out;
	}
	scale = sqrt(scale);
	*X_in *= scale;
	*Y_in *= scale;
	if(change_sign){
		*X_in *= -1;
		*Y_in *= -1;
	}
}
int cordic_vector(int X_in,int Y_in)
{
	int i=0;
	int X_out,Y_out;

	if(X_in<0){
		X_in = -X_in;
	}
	for(i=0;i<16;i++){
		if(Y_in == 0){
			break;
		}else if(Y_in > 0){
			X_out = X_in + (Y_in >> i);
			Y_out = -(X_in >> i) + Y_in;
		}else{
			X_out = X_in - (Y_in >> i);
			Y_out = (X_in >> i) + Y_in ;
		}
		X_in = X_out;
		Y_in = Y_out;
	}
	X_in *= 0.6027252935;
	Y_in *= 0.6027252935;

	return X_in;
}
