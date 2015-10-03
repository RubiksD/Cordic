#define BIT(_X) 1<<_X
#define F_SAMPLE 1000
#define F_OUT 10
#define pi 3.141592653589793

void calculate_rotation_angle(double f_sample, double f_in,int *word_mag, int *word_sign,double *scale_out);
void cordic_rotate(int word_mag, int word_sign,double scale,int *X_in,int *Y_in);
int cordic_vector(int X_in,int Y_in);
void cordic_rotate_2(int *X_in,int *Y_in,double angle);
void create_lookup_table();
