#include "main.h"
#include "control.h"

unsigned int CntM = 0;
unsigned int CntInit = 0;


float g = 0.;
float s1 = 0.;
float s2 = 0.;
float s3 = 0.;
float k1 = 0.;
float k2 = 0.;
float k3 = 0.;
float u1 = 0.;
float u2 = 0.;
float u3 = 0.;
float u1_batt = 0.;
float u2_batt = 0.;
float u3_batt = 0.;
float Va = 0.;
float sa = 0.;
float var=0.;

// efficiency test
float test_t=0;
float test_increment =0;
float test_current = -6;

float UcRef = 300.;
float q1_max=0.,q1_min = 0.;
float q2_max=0.,q2_min = 0.;
float q3_max=0.,q3_min = 0.;
float qa_max=0.,qa_min = 0.;
float I_max=0.,I_min = 0.;

// converter operations
unsigned int Run = 0;
unsigned int ErrorFlag = 0;
unsigned int charge_flag = 0;
unsigned int ECnt = 0;

// Measuermnets
float Vs = 0;
float Is = 0;
float Ir = 0;
float V1 = 0;
float V2 = 0;
float I1 = 0;
float I2 = 0;
float V3 = 0;
float V4 = 0;
float I3_B = 0;
float I3_L = 0;
float I3 = 0;
float I4_B = 0;
float I4_L = 0;
// CUrrent controllers
float IRef1 = 0.;
float IRef2 = 0.;
float IRef3 = 0.;
float IRef4 = 0.;
float Vdc = 0.;
float Vo_1 = 0.;
float Vo_2 = 0.;
float Vo_3 = 0.;
float Vo_4 = 0.;
float V1f = 0.;
float V2f = 0.;
float V3f = 0.;
float Vsf = 0.;
float Isf = 0.;
float Irf = 0.;
float I1f = 0.;
float I2f = 0.;
float I3f = 0.;

float Ps = 0.;

ACR ACR1 = {0,0,0,0};
ACR ACR2 = {0,0,0,0};
ACR ACR3 = {0,0,0,0};
ACR ACR4 = {0,0,0,0};

float p_uc = 0.;
float p_c = 0.;
float i_uc = 0.;
float i_c = 0.;
float q_max = 0.;
float q_min = 0.;
float S_MAX = 0.62;
float S_MIN = 0.58;


// Power supply control
double dac_V = 85;//200;
double dac_I = 5;//5;
double dac_I_offset = 5.;
double disturbance = 0.2;
//SCI
int32 sendReqflag = 0;
int32 sendCNT = 0;
int packLock = 0;

float offset = 0.9;
float t = 0.;

float v_droop = 0.;
float v_droopf = 0.;

float errV = 0.;
float    integ_errV = 0.;
float i_droop = 0.;



float err_droop = 0;

float integ_err_droop = 0;

float delta_droop = 0;


float PRef = 0.;
float integ_errP = 0.;
float errP = 0.;
float comp = 0.;

interrupt void EPWM1_INT_ISR(void)     // EPWM-1
{
	// Check Monitor
	if(sendCNT > 100){
		if(packLock == 0)
		{
			sendReqflag = 1;
		}
		sendCNT = 0;

	}
	else
		sendCNT++;

// Error check
	if(ErrorFlag)
		Run=0;
// FIltering
	V1f = A_LPF*V1f + B_LPF*V1;
	V2f = A_LPF*V2f + B_LPF*V2;
	V3f = A_LPF*V3f + B_LPF*V3;

	I1f = A_LPF_F*I1f + B_LPF_F*I1;
	I2f = A_LPF_F*I2f + B_LPF_F*I2;
	I3f = A_LPF_F*I3f + B_LPF_F*I3;

	Vsf = A_LPF*Vsf + B_LPF*Vs;
	Isf = A_LPF*Isf + B_LPF*Is;
	Irf = A_LPF*Irf + B_LPF*Ir;

// Insert ISR Code here
	if(Run == 0){
		checkError();
		StopEPwm();
		dac_I = dac_I_offset;
		setExtV(0.);
		setExtI(0.);
		t = 0.;
		ACR_PI_Clear(&ACR1);
		ACR_PI_Clear(&ACR2);
		ACR_PI_Clear(&ACR3);
		ACR_PI_Clear(&ACR4);
		s1 = V1/V1_MAX; // the supercap capacity
		s2 = V2/V2_MAX;
		s3 = V3/V3_MAX;
		ECnt = 0;
	}

	else if(Run == 1)
	{
		//Reference
		t += TS;
		/*
		dac_I = dac_I_offset + 0.5 * cos(TWOPI*0.1*t);
		if(dac_I>dac_I_offset) dac_I = dac_I_offset+0.5;
		else if(dac_I<dac_I_offset) dac_I = dac_I_offset-0.5;
		else{}
		*/
		//dac_I = 4. + cos(TWOPI*0.1*t);

		//dac_I = 4.;

		setExtV(dac_V);
		setExtI(dac_I-0.2);

		if(t>5.)
			Run = 2;
	}
	else if(Run == 2)
	{
		setExtV(dac_V);
		setExtI(dac_I-0.2);
		// Measurement for One-step MPC
		s1+= K1_BARS * I1f; // kind of coloumb counting
		s2+= K2_BARS * I2f;
		s3+= K3_BARS * I3f;
		sa = (s1+s2+s3)/3.;

		CntM++;
		if(CntM>CNT_M)
		{
			CntM = 0;

			//Va = (V1+V2)*0.5;
			k1 = K1_BAR/V1f;
			k2 = K2_BAR/V2f;
			k3 = K3_BAR/V3f;

			g = k1*k2 + k2*k3 + k1*k3;

			Ps = Vsf*Isf;

			//qa_max = ((S_MAX - sa)*3)/(K1_BAR+K2_BAR+K3_BAR);
			//qa_min = ((S_MIN - sa)*3)/(K1_BAR+K2_BAR+K3_BAR);

			//I_max = MIN(IL_MAX, qa_max);
			//I_min = MAX(IL_MIN, qa_min);

			q1_max = (S_MAX - s1)/K1_BAR;
			q1_min = (S_MIN - s1)/K1_BAR;
			q2_max = (S_MAX - s2)/K2_BAR;
			q2_min = (S_MIN - s2)/K2_BAR;
			q3_max = (S_MAX - s3)/K3_BAR;
			q3_min = (S_MIN - s3)/K3_BAR;

		}

		ACR_PI(IRef1, I1f, V1f, Vsf, &ACR1);
		ACR_PI(IRef2, I2f, V2f, Vsf, &ACR2);
		ACR_PI(IRef3, I3f, V3f, Vsf, &ACR3);

		EPwm1Regs.CMPA.half.CMPA = (unsigned int)(7500*ACR1.Duty);
		EPwm2Regs.CMPA.half.CMPA = (unsigned int)(7500*ACR2.Duty);
		EPwm3Regs.CMPA.half.CMPA = (unsigned int)(7500*ACR3.Duty);
		EPwm4Regs.CMPA.half.CMPA = (unsigned int)(7500*ACR4.Duty);


		StartEPwm();
		if(ECnt++>10)
		{
			ECnt = 5;
			checkError();
		}

	}
	else if(Run == 3)
	{
		//Reference
		t += TS;

		if (t > 80. ){
		S_MAX = 0.65;
		S_MIN = 0.55;
		}


		if(t>5. && t< 15.) dac_I_offset = 3.;
		else if(t>15. && t< 35.) dac_I_offset = 5.;
		else if(t>35. && t< 57.) dac_I_offset = 3.;
		else if(t>57. && t< 85.) dac_I_offset = 5.;
		else if(t>85. && t< 100.) dac_I_offset = 3.;
		else if(t>100. && t< 105.) dac_I_offset = 5.;
		else if(t>105.) dac_I_offset = 3.;

		/*
        v_droop =  (delta_droop + 122.5 - (Irf-Isf)*0.25); //droop vref no load = 122.5 = 120 +5/2  Rd = 0.25
        v_droopf = v_droop;//A_LPF*v_droopf + B_LPF*v_droop;

        errV = v_droopf - Vsf;

        integ_errV = integ_errV + 0.1225*0.05*errV; // was 0.005225 0.005125
        if (integ_errV > 1000){integ_errV=1000;}

        if (integ_errV <-1000){integ_errV=-1000;}

        i_droop = 0.185*0.05*errV + integ_errV; // was 0.725 0.72525


		 */

		dac_I = dac_I_offset + disturbance * sin(TWOPI*0.1*t);
		if(dac_I<0) dac_I = 0;

		setExtV(dac_V);
		setExtI(dac_I);


		// Measurement for One-step MPC
		s1+= K1_BARS * I1f; // kind of coloumb counting
		s2+= K2_BARS * I2f;
		s3+= K3_BARS * I3f;
		sa = (s1+s2+s3)/3.;

		errP = UcRef-Vsf*Irf; //0;

		integ_errP = integ_errP + 0.0005*errP;

		if (integ_errP > 10){integ_errP=10;}

		if (integ_errP <-10){integ_errP=-10;}

		comp = errP*0.25 +  integ_errP;

		if (comp > 100){comp=100;}

		if (comp <-100){comp=-100;}

		PRef = comp + UcRef; // + v_droop*i_droop;


		CntM++;
		if(CntM>CNT_M)
		{
			CntM = 0;

			//Va = (V1+V2)*0.5;
			k1 = K1_BAR/V1f;
			k2 = K2_BAR/V2f;
			k3 = K3_BAR/V3f;

			g = k1*k2 + k2*k3 + k1*k3;

			var=0.01;

			p_uc = Vsf*Isf - PRef;

			i_uc = p_uc/((V1f+V2f+V3f)/3);

			q_max = (S_MAX - sa)/((K1_BAR+K2_BAR+K3_BAR)/3);
			q_min = (S_MIN - sa)/((K1_BAR+K2_BAR+K3_BAR)/3);

			if(i_uc > MIN((3*IL_MAX), q_max))
				i_uc = MIN((3*IL_MAX), q_max);
			if(i_uc < MAX((3*IL_MIN), q_min))
				i_uc = MAX((3*IL_MIN), q_min);

			i_c = i_uc;

			p_c = i_c*((V1f+V2f+V3f)/3);

			//p_c = p_uc;

			Ps = Vsf*Isf;
			u1 = (-(k2+k3)*s1*var + k3*s2*var + k2*s3*var + (k2*k3) *(p_c))/g;
			u1_batt = (-(k2+k3)*s1*var + k3*s2*var + k2*s3*var)/g;
			u2 = (-(k3+k1)*s2*var + k3*s1*var + k1*s3*var + (k1*k3) *(p_c))/g;
			u2_batt = (-(k2+k3)*s1*var + k3*s2*var + k2*s3*var)/g;
			u3 = (-(k1+k2)*s3*var + k2*s1*var + k1*s2*var + (k1*k2) *(p_c))/g;
			u3_batt = (-(k2+k3)*s1*var + k3*s2*var + k2*s3*var)/g;

			IRef1 = (u1)/V1f;
			IRef2 = (u2)/V2f;
			IRef3 = (u3)/V3f;

			//if (t >5 && t < 30 ){
			//	IRef1 = (Vsf*Isf - PRef)/(V1f+V2f+V3f);
			//	IRef2 = IRef1;
			//	IRef3 = IRef1;
			//	}

			//qa_max = ((S_MAX - sa)*3)/(K1_BAR+K2_BAR+K3_BAR);
			//qa_min = ((S_MIN - sa)*3)/(K1_BAR+K2_BAR+K3_BAR);

			//I_max = MIN(IL_MAX, qa_max);
			//I_min = MAX(IL_MIN, qa_min);

			q1_max = (S_MAX - s1)/K1_BAR;
			q1_min = (S_MIN - s1)/K1_BAR;
			q2_max = (S_MAX - s2)/K2_BAR;
			q2_min = (S_MIN - s2)/K2_BAR;
			q3_max = (S_MAX - s3)/K3_BAR;
			q3_min = (S_MIN - s3)/K3_BAR;

			if(IRef1 > MIN(IL_MAX, q1_max))
				IRef1 = MIN(IL_MAX, q1_max);
			if(IRef1 < MAX(IL_MIN, q1_min))
				IRef1 = MAX(IL_MIN, q1_min);

			if(IRef2 > MIN(IL_MAX, q2_max))
				IRef2 = MIN(IL_MAX, q2_max);
			if(IRef2 < MAX(IL_MIN, q2_min))
				IRef2 = MAX(IL_MIN, q2_min);

			if(IRef3 > MIN(IL_MAX, q3_max))
				IRef3 = MIN(IL_MAX, q3_max);
			if(IRef3 < MAX(IL_MIN, q3_min))
				IRef3 = MAX(IL_MIN, q3_min);
		}

		ACR_PI(IRef1, I1f, V1f, Vsf, &ACR1);
		ACR_PI(IRef2, I2f, V2f, Vsf, &ACR2);
		ACR_PI(IRef3, I3f, V3f, Vsf, &ACR3);

		EPwm1Regs.CMPA.half.CMPA = (unsigned int)(7500*ACR1.Duty);
		EPwm2Regs.CMPA.half.CMPA = (unsigned int)(7500*ACR2.Duty);
		EPwm3Regs.CMPA.half.CMPA = (unsigned int)(7500*ACR3.Duty);
		EPwm4Regs.CMPA.half.CMPA = (unsigned int)(7500*ACR4.Duty);


		StartEPwm();
		if(ECnt++>10)
		{
			ECnt = 5;
			checkError();
		}

	}

	else if(Run == 4)
	{

		if(V1f< 0.55*V1_MAX)
			IRef1 = 3.;
		if(V1f>0.55*V1_MAX)
			IRef1 = -3.;

		if(V2f>0.6*V2_MAX)
			IRef2 = -3.;
		if(V2f<0.6*V2_MAX)
			IRef2 = 3.;

		if(V3f>0.65*V3_MAX)
			IRef3 = -3.;
		if(V3f<0.65*V3_MAX)
			IRef3 = 3.;

		setExtV(dac_V);
		setExtI(dac_I-0.2);

		ACR_PI(IRef1, I1f, V1f, Vsf, &ACR1);
		ACR_PI(IRef2, I2f, V2f, Vsf, &ACR2);
		ACR_PI(IRef3, I3f, V3, Vsf, &ACR3);
		ACR_PI(IRef4, I4_L, V4, Vsf, &ACR4);

		EPwm1Regs.CMPA.half.CMPA = (unsigned int)(7500*ACR1.Duty);
		EPwm2Regs.CMPA.half.CMPA = (unsigned int)(7500*ACR2.Duty);
		EPwm3Regs.CMPA.half.CMPA = (unsigned int)(7500*ACR3.Duty);
		EPwm4Regs.CMPA.half.CMPA = (unsigned int)(7500*ACR4.Duty);

		setExtV(dac_V);
		setExtI(dac_I);

		StartEPwm();
		if(ECnt++>10)
		{
			ECnt = 5;
			checkError();
		}
	}

	else if(Run == 5)
	    {

	        t += TS;
	        setExtV(dac_V);
	        setExtI(dac_I);
	        // Measurement for One-step MPC
	        s1+= K1_BARS * I1f; // kind of coloumb counting
	        s2+= K2_BARS * I2f;
	        s3+= K3_BARS * I3f;
	        sa = (s1+s2+s3)/3.;

	        CntM++;
	        if(CntM>CNT_M)
	        {
	            CntM = 0;

	            //Va = (V1+V2)*0.5;
	            k1 = K1_BAR/V1f;
	            k2 = K2_BAR/V2f;
	            k3 = K3_BAR/V3f;

	            g = k1*k2 + k2*k3 + k1*k3;

	            Ps = Vsf*Isf;

	            if( (t-test_t)>2){
	                test_t=t;

	                test_increment = 6*0.2;

	                test_current = test_increment+test_current;
	                IRef1 = test_current;
	                IRef2 = 0;
	                IRef3 = 0;

	            }

	            if ( t > 30) { Run = 0 ; }

                if(IRef1 > IL_MAX)
                    IRef1 = IL_MAX;
                if(IRef1 < IL_MIN)
                    IRef1 = IL_MIN;

	        }

	        ACR_PI(IRef1, I1f, V1f, Vsf, &ACR1);
	        ACR_PI(IRef2, I2f, V2f, Vsf, &ACR2);
	        ACR_PI(IRef3, I3f, V3f, Vsf, &ACR3);

	        EPwm1Regs.CMPA.half.CMPA = (unsigned int)(7500*ACR1.Duty);
	        EPwm2Regs.CMPA.half.CMPA = (unsigned int)(7500*ACR2.Duty);
	        EPwm3Regs.CMPA.half.CMPA = (unsigned int)(7500*ACR3.Duty);
	        EPwm4Regs.CMPA.half.CMPA = (unsigned int)(7500*ACR4.Duty);


	        StartEPwm();
	        if(ECnt++>10)
	        {
	            ECnt = 5;
	            checkError();
	        }

	    }

	else
	{
		Run = 0;
	}
// Clear INT flag for this timer
	EPwm1Regs.ETCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
// Next two lines for debug only to halt the processor here
// Remove after inserting ISR Code
//	asm ("      ESTOP0");
//	for(;;);
}



int main(void)
{
 	InitDsp();
	//MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
	//InitFlash();
	while(1){
		if(sendReqflag && ( Run == 5 )){
			sendReqflag = 0;
			packLock = 1;
			scib_xmit('D');
			scib_xmit('A');
			scib_xmit('T');
			scib_xmit('A');
			scib_xmit(',');
			scib_xmit('T');
			scib_xmit('I');
			scib_xmit('M');
			scib_xmit('E');
			scib_xmit(',');
			scib_xmit_Float0(s1);
			scib_xmit(',');
		 	scib_xmit_Float10(I1f);
		 	scib_xmit(',');
		 	scib_xmit_Float0(s2);
		 	scib_xmit(',');
		 	scib_xmit_Float10(I2f);
		 	scib_xmit(',');
		 	scib_xmit_Float0(s3);
		 	scib_xmit(',');
		 	scib_xmit_Float10(I3f);
		 	scib_xmit(',');
		 	scib_xmit_Float100(Vsf);
		 	scib_xmit(',');
		 	scib_xmit_Float10(Isf);
		 	scib_xmit(',');
		 	scib_xmit_Float10(Irf);
		 	scib_xmit(',');
		 	scib_xmit_Float10(V1f);
		 	scib_xmit(',');
		 	scib_xmit_Float10(V2f);
		 	scib_xmit(',');
		 	scib_xmit_Float10(V3f);
		 	scib_xmit('\n');
			packLock = 0;
		}
	}

}

// INT1.6
interrupt void  ADCINT_ISR(void)     // ADC
{
// Insert ISR Code here
	/*Volt_Source		 =	(float32)((((AdcRegs.ADCRESULT0>>4) & 0x0FFF)-2128.0f)*((1000.0f/12.7f)*(3.0f/4096.0f)*(15.0f/3.3f*2.0f)));
	Volt_Battery	 =	(float32)((((AdcRegs.ADCRESULT1>>4) & 0x0FFF)-2144.0f)*((100.0f/12.7f)*(3.0f/4096.0f)*(15.0f/3.3f*2.0f)));
	Current_Load 	 =	-(float32)((((AdcRegs.ADCRESULT2>>4) & 0x0FFF)-2142.0f)*((25.0f/13.95f)*(3.0f/4096.0f)*(15.0f/3.3f*2.0f)));
	Current_Source   =	(float32)((((AdcRegs.ADCRESULT3>>4) & 0x0FFF)-2149.0f)*((25.0f/13.95f)*(3.0f/4096.0f)*(15.0f/3.3f*2.0f)));
	Current_Battery  =	-(float32)((((AdcRegs.ADCRESULT4>>4) & 0x0FFF)-2130.0f)*((25.0f/13.95f)*(3.0f/4096.0f)*(15.0f/3.3f*2.0f)));*/

	Vs	 =	(float32)((((AdcRegs.ADCRESULT14>>4) & 0x0FFF)-43.0f)*((1000.0f/14.3f)*(3.0f/4096.0f)*(15.0f/3.3f*1.0f)));
	Is   =	(float32)((((AdcRegs.ADCRESULT12>>4) & 0x0FFF)-39.0f)*((25.0f/15.5f)*(3.0f/4096.0f)*(15.0f/3.3f*1.0f)));
	Ir 	 =	(float32)((((AdcRegs.ADCRESULT10>>4) & 0x0FFF)-39.0f)*((25.0f/15.3f)*(3.0f/4096.0f)*(15.0f/3.3f*1.0f)));

	V1	 =  (float32)((((AdcRegs.ADCRESULT1>>4) & 0x0FFF)-2156.0f)*((100.0f/12.7f)*(3.0f/4096.0f)*(15.0f/3.3f*2.0f)));
	I1	 =  (float32)((((AdcRegs.ADCRESULT2>>4) & 0x0FFF)-2135.0f)*((25.0f/13.95f)*(3.0f/4096.0f)*(15.0f/3.3f*2.0f))) ;

	V2	 =  (float32)((((AdcRegs.ADCRESULT3>>4) & 0x0FFF)-2140.0f)*((100.0f/12.7f)*(3.0f/4096.0f)*(15.0f/3.3f*2.0f)));
	I2	 =  (float32)((((AdcRegs.ADCRESULT0>>4) & 0x0FFF)-2115.0f)*((25.0f/13.95f)*(3.0f/4096.0f)*(15.0f/3.3f*2.0f))) ;

	V3		 =  (float32)((((AdcRegs.ADCRESULT6>>4) & 0x0FFF)-2145.0f)*((100.0f/12.7f)*(3.0f/4096.0f)*(15.0f/3.3f*2.0f)));
	I3_B	 =  (float32)((((AdcRegs.ADCRESULT4>>4) & 0x0FFF)-2123.0f)*((25.0f/13.95f)*(3.0f/4096.0f)*(15.0f/3.3f*2.0f)));
	I3_L	 =  -(float32)((((AdcRegs.ADCRESULT5>>4) & 0x0FFF)-2125.0f)*((25.0f/13.95f)*(3.0f/4096.0f)*(15.0f/3.3f*2.0f)));
	I3 = I3_B;

	V4		 =  (float32)((((AdcRegs.ADCRESULT9>>4) & 0x0FFF)-2132.0f)*((100.0f/12.7f)*(3.0f/4096.0f)*(15.0f/3.3f*2.0f)));
	I4_B	 =  (float32)((((AdcRegs.ADCRESULT7>>4) & 0x0FFF)-2135.0f)*((25.0f/13.95f)*(3.0f/4096.0f)*(15.0f/3.3f*2.0f)));
	I4_L	 =  -(float32)((((AdcRegs.ADCRESULT8>>4) & 0x0FFF)-2130.0f)*((25.0f/13.95f)*(3.0f/4096.0f)*(15.0f/3.3f*2.0f)));

	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1
	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit
	//AdcRegs.ADCTRL2.bit.RST_SEQ2 = 1;
	//AdcRegs.ADCST.bit.INT_SEQ2_CLR = 1;

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

}

void InitDsp(void)
{
	InitSysCtrl();
	InitGpio();
	InitEPwmGpio();
	InitSpiGpio();
//	InitEQepGpio();
//	InitECanbGpio();
	InitSCI();
DINT;

	InitPieCtrl();

	IER = 0x0000;
	IFR = 0x0000;

	InitPieVectTable();

EALLOW;
//	PieVectTable.XINT13 = &cpu_timer1_isr;
	PieVectTable.ADCINT = &ADCINT_ISR;
//	PieVectTable.TINT0 = &TINT0_ISR;
//	PieVectTable.EPWM1_TZINT = &EPWM1_TZINT_ISR;
//	PieVectTable.EPWM2_TZINT = &EPWM2_TZINT_ISR;
//	PieVectTable.EPWM3_TZINT = &EPWM3_TZINT_ISR;
//	PieVectTable.EPWM4_TZINT = &EPWM4_TZINT_ISR;
//	PieVectTable.EPWM5_TZINT = &EPWM5_TZINT_ISR;
//	PieVectTable.EPWM6_TZINT = &EPWM6_TZINT_ISR;
	PieVectTable.EPWM1_INT = &EPWM1_INT_ISR;
//	PieVectTable.EPWM4_INT = &EPWM4_INT_ISR;
	PieVectTable.XINT1 = &XINT1_ISR;
	PieVectTable.XINT2 = &XINT2_ISR;
//	PieVectTable.EQEP1_INT = &EQEP1_INT_ISR;
	PieVectTable.EQEP2_INT = &EQEP2_INT_ISR;
EDIS;

//	IER |= (M_INT1 | M_INT2 | M_INT3 | M_INT5 );
	IER |= (M_INT1 | M_INT3 | M_INT5 );
//	IER |= (M_INT1 | M_INT3 );

	PieCtrlRegs.PIEIER1.bit.INTx4 = 1;	//	interrupt void  XINT1_ISR(void)
	PieCtrlRegs.PIEIER1.bit.INTx5 = 1;	//	interrupt void  XINT2_ISR(void)
	PieCtrlRegs.PIEIER1.bit.INTx6 = 1;	//	interrupt void  ADCINT_ISR(void)     // ADC
//	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;	//	interrupt void  TINT0_ISR(void)      // CPU-Timer 0
//	PieCtrlRegs.PIEIER2.bit.INTx1 = 1;	//	interrupt void EPWM1_TZINT_ISR(void) // EPWM-1
//	PieCtrlRegs.PIEIER2.bit.INTx2 = 1;	//	interrupt void EPWM2_TZINT_ISR(void) // EPWM-2
//	PieCtrlRegs.PIEIER2.bit.INTx3 = 1;	//	interrupt void EPWM3_TZINT_ISR(void) // EPWM-3
//	PieCtrlRegs.PIEIER2.bit.INTx4 = 1;	//	interrupt void EPWM4_TZINT_ISR(void) // EPWM-4
//	PieCtrlRegs.PIEIER2.bit.INTx5 = 1;	//	interrupt void EPWM5_TZINT_ISR(void) // EPWM-5
//	PieCtrlRegs.PIEIER2.bit.INTx6 = 1;	//	interrupt void EPWM6_TZINT_ISR(void) // EPWM-6
	PieCtrlRegs.PIEIER3.bit.INTx1 = 1;	//	interrupt void EPWM1_INT_ISR(void)   // EPWM-1
//	PieCtrlRegs.PIEIER3.bit.INTx4 = 1;	//	interrupt void EPWM4_INT_ISR(void)   // EPWM-4
//	PieCtrlRegs.PIEIER5.bit.INTx1 = 1;	//  interrupt void EQEP1_INT_ISR(void)   // EQEP-1
	PieCtrlRegs.PIEIER5.bit.INTx2 = 1;	//  interrupt void EQEP2_INT_ISR(void)   // EQEP-2

EINT;
ERTM;

	InitEPwm();
	InitAdc();
	InitSpi();
	//InitEQep();
	//InitECanb();

	ConfigEPwm();
	ConfigAdc();
	//ConfigEQep();
	ConfigGpio();

	StopEPwm();
	//StartEPwm();
}



interrupt void EPWM4_INT_ISR(void)     // EPWM-1
{
// Insert ISR Code here

    //EPwm3Regs.CMPA.half.CMPA = (unsigned int)((float32)0.9 * 7500);
    //EPwm4Regs.CMPA.half.CMPA = (unsigned int)((float32)0.0 * 7500);    EPwm3Regs.CMPA.half.CMPA = (unsigned int)(Con_input + 3750);
// Clear INT flag for this timer
    EPwm3Regs.ETCLR.bit.INT = 1;
	EPwm4Regs.ETCLR.bit.INT = 1;
// To receive more interrupts from this PIE group, acknowledge this interrupt
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}




// INT 5.2
interrupt void EQEP2_INT_ISR(void)    // EQEP-2
{
  // Insert ISR Code here

    //EPwm1Regs.CMPA.half.CMPA = (unsigned int)(3750);

	EQep2Regs.QCLR.bit.UTO = 1; //Clear unit time out interrupt flag
	EQep2Regs.QCLR.bit.INT = 1; //Global interrupt clear flag

// To receive more interrupts from this PIE group, acknowledge this interrupt
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
//  asm ("      ESTOP0");
//  for(;;);


}



// INT1.4
interrupt void  XINT1_ISR(void)
{
//  asm ("      ESTOP0");
//  for(;;);
}

// INT1.5
interrupt void  XINT2_ISR(void)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
//  asm ("      ESTOP0");
// for(;;);

}



void setExtV(double value)
{
	if(value > 500.0)
		value = 500.0;
	else if(value < 0)
		value = 0;

	StartDac(value, 500, 4, 0);
}

void setExtI(double value)
{
	if(value > 10.0)
		value = 10.0;
	else if(value < 0)
		value = 0;

	StartDac(value, 10, 1, 0);
}



unsigned int checkError(void)
{
	// error flag : 0x (1)0 (2)0 (3)0 (DC)0
	unsigned int tmp = 0x0000;

	if(Vs > 200.0f)		ErrorFlag|= 0x0001;
	if(Is > 20.0f)		ErrorFlag|= 0x0002;
	if(Ir > 20.0f)		ErrorFlag|= 0x0004;

	if((V1 > 4*14.5f) /*|| (V1 < 0.0f)*/)		ErrorFlag|= 0x1000; //INCREASED SINCE USING 4 UC
	if((I1 > 10.0f) || (I1 < -10.0f))	ErrorFlag|= 0x2000;

	if((V2 > 14.5f) /*|| (V2 < 0.0f)*/)		ErrorFlag|= 0x0100;
	if((I2 > 15.0f) || (I2 < -15.0f))	ErrorFlag|= 0x0200;

	if((V3 > 14.0f) /*|| (V3 < 42.0f)*/)	ErrorFlag|= 0x0010;
	if((I3_B > 15.0f) || (I3_B < -15.0f))	ErrorFlag|= 0x0020;
	if((I3_L > 15.0f) || (I3_L < -15.0f))	ErrorFlag|= 0x0040;

//	if((V4 > 54.0f) || (V4 < 42.0f))		tmp = tmp | 0x00000001;
//	if((I4_B > 10.0f) || (I4_B < -10.0f))	tmp = tmp | 0x00000002;
//	if((I4_L > 10.0f) || (I4_L < -10.0f))	tmp = tmp | 0x00000004;

	return tmp;
}

