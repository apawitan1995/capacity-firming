/*
 * HCPOWER_UPS_VER3.h
 *
 *  Created on: 2013. 1. 16.
 *      Author: PELAB_DESKTOP2
 */

#ifndef HCPOWER_UPS_VER3_H_
#define HCPOWER_UPS_VER3_H_

#ifdef __cplusplus
extern "C" {
#endif

struct ADC_VALUE
{

	float32 batVdcp;
	float32 batVdcn;

	float32 batVdc;

	float32 inverterRi;
	float32 inverterSi;
	float32 inverterTi;


	float32 inverterDi;
	float32 inverterQi;


	float32 vwt;

	float32 wmt;
	float32 wet;
	float32 we;

	float32 deltawtCnt;
	float32 wtCnt;
	float32 wtCntPre;
	float32 wtNum;

	float32 inverterAi;
	float32 inverterBi;

	float32 StatorfluxES;

	float32 TorqueES;

	float32 StatorfluxESTheta;

	float32 inverterDiRAW;
	float32 inverterQiRAW;

	float32 StatorAfluxES;
	float32 StatorBfluxES;

	float32 StatorDfluxES;
	float32 StatorQfluxES;

	float32 RotorAfluxES;
	float32 RotorBfluxES;

	float32 RotorDfluxES;
	float32 RotorQfluxES;

	float32 StatorAfluxESpre;
	float32 StatorBfluxESpre;

	float32 inverterAeS;
	float32 inverterBeS;

	float32 inverterAeSpre;
	float32 inverterBeSpre;

	float32 inverterAvS;
	float32 inverterBvS;

	float32 Sin;
	float32 Cos;

	float32 Pedal;
	float32 Break;
};


typedef struct
{
	float32 w;
	float32 wt;
	float32 va;
	float32 vb;
	float32 vc;
	float32 Vd;
	float32 Vq;
	float32 Ti;
} PLL;


typedef struct { float32				TargetValue; 	// Input: Target input (pu)
				 float32				SetpointValue;	// Output: Target output (pu)
				 float32				Offset;
				 Uint32					EqualFlag;		// Output: Flag output (Q0) - independently with global Q
				 float32				Tmp;			// Variable: Temp variable
				 float32				Resolution;
				 float32				Sum;
		  	   } ADCOFFSET_CORRECTION;


 typedef struct
			 {
				float32 w_cur;
				float32 w_prv;
				float32 Cof_A1;
				float32 Cof_B0;
				float32 Cof_B1;

			 }LPF_PARAM;


/*-----------------------------------------------------------------------------
Default initalizer for the RMPCNTL object.
-----------------------------------------------------------------------------*/
#define ADCOFFSET_CORRECTION_DEFAULTS {	0, 		 \
									0,		 \
									0,		 \
									0,       \
									0,       \
									0.0005,       \
									0,       \
                   		  }

/*------------------------------------------------------------------------------
 	RAMP Controller Macro Definition
------------------------------------------------------------------------------*/

#define ADCOFFSET_CORRECTION_MACRO(v)														\
	v.Tmp = v.TargetValue - v.SetpointValue;										\
if (fabs(v.Tmp) >= v.Resolution)				    								\
{																					\
	if (v.TargetValue >= v.SetpointValue)	v.Offset += v.Resolution;		\
	else	v.Offset -= v.Resolution;										\
}																					\
else v.EqualFlag = 1;

extern volatile struct ADC_VALUE AdcValue;
extern volatile struct ADC_VALUE AdcValue2;


extern void StartDac(float32 dac_value, Uint16 scale, Uint16 channel, Uint16 polarity);
extern void Start2DSvm(float32 VdRef, float32 VqRef, float32 wt, float32 Ts, float32 Vdc);
unsigned int LTC1594(void);
void spi_xmit(Uint16 ch, Uint16 data);
void spi_init(void);
float32 LPFilter(LPF_PARAM *lpf, float32 Vin);
void LPFilter_Cof_init(LPF_PARAM *lpf, float32 cutoff);
extern void SVM_DirectTorqueCtrl(void);
extern void FulxandTorqueEstimator(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* HCPOWER_UPS_VER3_H_ */
