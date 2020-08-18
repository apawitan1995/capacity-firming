/*
 * control.h
 *
 *  Created on: 2017. 8. 15.
 *      Author: Administrator
 */

#ifndef INCLUDE_CONTROL_H_
#define INCLUDE_CONTROL_H_
#include "DSP28x_Project.h"

#define MIN(X,Y) ((X)<(Y) ? (X) : (Y))
#define MAX(X,Y) ((X)>(Y) ? (X) : (Y))

typedef struct
{
	float out;
}LPF;
#define TAU_LPF (1./(TWOPI*50.))
#define A_LPF (1-TS/TAU_LPF)
#define B_LPF (TS/TAU_LPF)

#define TAU_LPF_F (1./(TWOPI*500.))
#define A_LPF_F (1-TS/TAU_LPF_F)
#define B_LPF_F (TS/TAU_LPF_F)


void Calc_LPF(float var, LPF *p);

//math symbols
#define TWOPI		(2.*PI)

//current controller
#define WCC			(TWOPI*300.)
#define KPC			(LS*WCC)
#define KIC			(RS*WCC)
#define LS			(1e-3)
#define RS 			(0.013)

//outer-loop MPC
#define C1 (58.)
#define C2 (58.)
#define C3 (2*58.)
#define V1_MAX (16.)
#define V2_MAX (16.)
#define V3_MAX (0.75*16.)

#define K1_BAR (TM/V1_MAX/C1) // basicly this is 1/I
#define K2_BAR (TM/V2_MAX/C2)
#define K3_BAR (TM/V3_MAX/C3)
#define K1_BARS (TS/V1_MAX/C1)
#define K2_BARS (TS/V2_MAX/C2)
#define K3_BARS (TS/V3_MAX/C3)

//outer-loop controller
#define TM		(0.05)
#define CNT_M	(TM/TS)
#define ALPHA	(1.)
#define CB		(10.)

#define IL_MAX	(6.)
#define IL_MIN	(-6.)



typedef struct
{
	float eL_k1, eL_k;
	float Vo;
	float Duty;
}ACR;


void ACR_PI(float IRef, float Imeas, float Vb, float Vs, ACR *p);
void ACR_PI_Clear(ACR *p);


#endif /* INCLUDE_CONTROL_H_ */
