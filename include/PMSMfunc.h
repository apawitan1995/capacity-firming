#include "math.h"


typedef struct PMSMsrc
{
	double PMSM_sin;
	double PMSM_cos;

	double inverter_Ia;
	double inverter_Ib;
	double inverter_Ic;

	double inp_speed;

}PMSMsrc;

typedef struct PMSMcalcopt
{
	double motor_angle;

	double opt_asin;
	double opt_bsin;
	double opt_csin;

	double conv_alpha;
	double conv_beta;

	double conv_d;
	double conv_q;

	Uint16 res_asin;
	Uint16 res_bsin;
	Uint16 res_csin;

}PMSMcalcopt;


extern PMSMsrc motorsrc;
extern PMSMcalcopt motorcalc, PI_calc;

extern int counter;


extern unsigned int init_flag;
extern double Vsn;
extern unsigned int init_cnt;
extern unsigned int vector_cnt;
extern unsigned int Speed_Reference;
extern float32 Torque_ref;
extern unsigned int direction;


