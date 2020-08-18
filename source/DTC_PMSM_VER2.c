
#pragma CODE_SECTION(Start2DSvm, "ramfuncs");
#pragma CODE_SECTION(StartDac, "ramfuncs");

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

void StartDac(float32 dac_value, Uint16 scale, Uint16 channel, Uint16 polarity)
{
	int16 dac_int_value;
	Uint16 dac_hex_value;

	switch(polarity)
	{
			case 0:
				dac_int_value = (dac_value * 2048) / scale;
				dac_hex_value = dac_int_value + 2048;

				break;

			case 1:
				dac_int_value = (dac_value * 4095) / scale;
				dac_hex_value = dac_int_value;

				break;
	}

	if(dac_hex_value >= 4096)	dac_hex_value = 4095;
	else if(dac_hex_value <= 0)	dac_hex_value = 0;

	channel = channel<<14;
	dac_hex_value = dac_hex_value | channel;

//	GpioDataRegs.GPBSET.bit.GPIO57 = 1;
	GpioDataRegs.GPASET.bit.GPIO29 = 1;
//	while(SpiaRegs.SPISTS.bit.BUFFULL_FLAG);
    SpiaRegs.SPITXBUF = dac_hex_value;
//    while(SpiaRegs.SPITXBUF != SpiaRegs.SPIRXBUF);
    DELAY_US(1);
//	while(SpiaRegs.SPISTS.bit.BUFFULL_FLAG==0);
//	GpioDataRegs.GPBCLEAR.bit.GPIO57 = 1;
    GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;
}

/*void Start2DSvm(float32 VdRef, float32 VqRef, float32 wt, float32 Ts, float32 Vdc)
{
//		----------------------------------------------------------
//						(d-q-o -> a-b-o) 변환
//		----------------------------------------------------------

		SvmValue.vAlpha = (VdRef * cos(wt) - VqRef * sin(wt));
		SvmValue.vBeta  = (VdRef * sin(wt) + VqRef * cos(wt));

//		SvmValue.vAlpha = (VdRef);
//		SvmValue.vBeta  = (VqRef);
		SvmValue.Vdc = Vdc;
		SvmValue.Ts = Ts;

//		----------------------------------------------------------
//							공간벡터 위치 판별
//		----------------------------------------------------------

		SvmValue.vaSection = SvmValue.vBeta;
		SvmValue.vbSection = -0.5 * SvmValue.vBeta + 0.866 * SvmValue.vAlpha;
		SvmValue.vcSection = -0.5 * SvmValue.vBeta - 0.866 * SvmValue.vAlpha;

		if(SvmValue.vaSection>0)	SvmValue.VaSign=1;
		else	SvmValue.VaSign=0;

		if(SvmValue.vbSection>0)	SvmValue.VbSign=1;
		else	SvmValue.VbSign=0;

		if(SvmValue.vcSection>0)	SvmValue.VcSign=1;
		else	SvmValue.VcSign=0;

		SvmValue.N = SvmValue.VaSign + 2 * SvmValue.VbSign + 4 * SvmValue.VcSign;

//		----------------------------------------------------------
//							타임 인터벌 계산(3D)
//		----------------------------------------------------------

		switch(SvmValue.N)
		{

			case 1:
				SvmValue.Tx = (-1.5 * SvmValue.vAlpha + 0.866 * SvmValue.vBeta);
				SvmValue.Ty = (1.5 * SvmValue.vAlpha + 0.866 * SvmValue.vBeta);
				SvmValue.T0 =(SvmValue.Ts - SvmValue.Tx - SvmValue.Ty) / 2;
				SvmValue.T7 = SvmValue.Ts - SvmValue.Tx - SvmValue.Ty - SvmValue.T0;

				SvmValue.aRef =(SvmValue.T0 + SvmValue.Tx) / 2;
				SvmValue.bRef = SvmValue.T0 / 2;
				SvmValue.cRef =(SvmValue.T0 + SvmValue.Tx + SvmValue.Ty) / 2;

				break;

			case 2:
				SvmValue.Tx = (1.5 * SvmValue.vAlpha + 0.866 * SvmValue.vBeta);
				SvmValue.Ty = (- 1.732 * SvmValue.vBeta);
				SvmValue.T0 =(SvmValue.Ts - SvmValue.Tx - SvmValue.Ty) / 2;
				SvmValue.T7 = SvmValue.Ts - SvmValue.Tx - SvmValue.Ty - SvmValue.T0;

				SvmValue.aRef = SvmValue.T0 / 2;
				SvmValue.bRef =(SvmValue.T0 + SvmValue.Tx + SvmValue.Ty) / 2;
				SvmValue.cRef =(SvmValue.T0 + SvmValue.Tx) / 2;

				break;

			case 3:
				SvmValue.Tx = (1.5 * SvmValue.vAlpha - 0.866 * SvmValue.vBeta);
				SvmValue.Ty = (1.732 * SvmValue.vBeta);
				SvmValue.T0 = (SvmValue.Ts - SvmValue.Tx - SvmValue.Ty) / 2;
				SvmValue.T7 = SvmValue.Ts - SvmValue.Tx - SvmValue.Ty - SvmValue.T0;

				SvmValue.aRef = SvmValue.T0 / 2;
				SvmValue.bRef =(SvmValue.T0 + SvmValue.Tx) / 2;
				SvmValue.cRef =(SvmValue.T0 + SvmValue.Tx + SvmValue.Ty) / 2;

				break;

			case 4:
				SvmValue.Tx = (- 1.732 * SvmValue.vBeta);
				SvmValue.Ty = (- 1.5 * SvmValue.vAlpha + 0.866 * SvmValue.vBeta);
				SvmValue.T0 =(SvmValue.Ts - SvmValue.Tx - SvmValue.Ty) / 2;
				SvmValue.T7 = SvmValue.Ts - SvmValue.Tx - SvmValue.Ty - SvmValue.T0;

				SvmValue.aRef = (SvmValue.T0 + SvmValue.Tx + SvmValue.Ty) / 2;
				SvmValue.bRef = (SvmValue.T0 + SvmValue.Tx) / 2;
				SvmValue.cRef =  SvmValue.T0 / 2;

				break;

			case 5:
				SvmValue.Tx = (1.732 * SvmValue.vBeta);
				SvmValue.Ty = (- 1.5 * SvmValue.vAlpha - 0.866 * SvmValue.vBeta);
				SvmValue.T0 = (SvmValue.Ts - SvmValue.Tx - SvmValue.Ty) / 2;
				SvmValue.T7 = SvmValue.Ts - SvmValue.Tx - SvmValue.Ty - SvmValue.T0;

				SvmValue.aRef = (SvmValue.T0 + SvmValue.Tx + SvmValue.Ty) / 2;
				SvmValue.bRef =  SvmValue.T0 / 2;
				SvmValue.cRef = (SvmValue.T0 + SvmValue.Tx) / 2;

				break;

			case 6:
				SvmValue.Tx = (- 1.5 * SvmValue.vAlpha - 0.866 * SvmValue.vBeta);
				SvmValue.Ty = (1.5 * SvmValue.vAlpha - 0.866 * SvmValue.vBeta);
				SvmValue.T0 =(SvmValue.Ts - SvmValue.Tx - SvmValue.Ty) / 2;
				SvmValue.T7 = SvmValue.Ts - SvmValue.Tx - SvmValue.Ty - SvmValue.T0;

				SvmValue.aRef =(SvmValue.T0 + SvmValue.Tx) / 2;
				SvmValue.bRef =(SvmValue.T0 + SvmValue.Tx + SvmValue.Ty) / 2;
				SvmValue.cRef = SvmValue.T0 / 2;

				break;

		}

//2D-SVM
	SvmValue.aRef = SvmValue.aRef / SvmValue.Vdc + 0.5;
	SvmValue.bRef = SvmValue.bRef / SvmValue.Vdc + 0.5;
	SvmValue.cRef = SvmValue.cRef / SvmValue.Vdc + 0.5;

	SvmValue.aRef = 7500 * SvmValue.aRef;
	SvmValue.bRef = 7500 * SvmValue.bRef;
	SvmValue.cRef = 7500 * SvmValue.cRef;

	if(SvmValue.aRef > 7500)		SvmValue.aRef = 7500;
	else if(SvmValue.aRef < 0)		SvmValue.aRef = 0;

	if(SvmValue.bRef > 7500)		SvmValue.bRef = 7500;
	else if(SvmValue.bRef < 0)		SvmValue.bRef = 0;

	if(SvmValue.cRef > 7500)		SvmValue.cRef = 7500;
	else if(SvmValue.cRef < 0)		SvmValue.cRef = 0;
}*/


void spi_init(void)
{
	EALLOW;

    GpioCtrlRegs.GPBPUD.bit.GPIO54 = 0;   // Enable pull-up on GPIO54 (SPISIMOA)
//    GpioCtrlRegs.GPBPUD.bit.GPIO55 = 0;   // Enable pull-up on GPIO55 (SPISOMIA)
    GpioCtrlRegs.GPBPUD.bit.GPIO56 = 0;   // Enable pull-up on GPIO56 (SPICLKA)
    GpioCtrlRegs.GPBPUD.bit.GPIO57 = 0;   // Enable pull-up on GPIO57 (SPISTEA)

    GpioCtrlRegs.GPBQSEL2.bit.GPIO54 = 3; // Asynch input GPIO16 (SPISIMOA)
//    GpioCtrlRegs.GPBQSEL2.bit.GPIO55 = 3; // Asynch input GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO56 = 3; // Asynch input GPIO18 (SPICLKA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO57 = 3; // Asynch input GPIO19 (SPISTEA)

    GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 1; // Configure GPIO54 as SPISIMOA
//    GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 1; // Configure GPIO55 as SPISOMIA
    GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 1; // Configure GPIO56 as SPICLKA
//    GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 1; // Configure GPIO57 as SPISTEA

	GpioDataRegs.GPBSET.bit.GPIO57 = 0;
	GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO57 = 1;

//  GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1; // Configure GPIO19 as SPISTEA



// Initialize SPI FIFO registers
    SpiaRegs.SPIFFTX.all=0xE040;
    SpiaRegs.SPIFFRX.all=0x204f;
    SpiaRegs.SPIFFCT.all=0x0;

    SpiaRegs.SPICCR.all =0x001F;	             // Reset on, rising edge, 16-bit char bits
	SpiaRegs.SPICTL.all =0x000E;    		     // Enable master mode, normal phase,
                                                 // enable talk, and SPI int disabled.
	SpiaRegs.SPIBRR = 0x004B;
    SpiaRegs.SPICCR.all =0x009F;		         // Relinquish SPI from Reset
    SpiaRegs.SPIPRI.bit.FREE = 1;                // Set so breakpoints don't disturb xmission
}


void spi_xmit(Uint16 ch, Uint16 data)
{
	Uint16 temp = 0;
	temp = (ch & 0x0003) << 14;
	temp |= (data & 0x0FFF);
	SpiaRegs.SPITXBUF = temp;
}


void LPFilter_Cof_init(LPF_PARAM *lpf, float32 cutoff)
{
	float32 alpha, beta, temp;

	alpha = cutoff * 2 * PI;
	beta = 1. * alpha;
	temp = alpha * TS + 2;
	lpf->Cof_A1 = (alpha * TS - 2)/temp;
	lpf->Cof_B0 = (beta * TS)/temp;
	lpf->Cof_B1 = lpf->Cof_B0;

	lpf->w_cur = 0;
	lpf->w_prv = 0;

}

float32 LPFilter(LPF_PARAM *lpf, float32 Vin)
{
	float32 Vout;

	lpf->w_cur = Vin - lpf->Cof_A1 * lpf->w_prv;
	Vout = lpf->Cof_B0 * lpf->w_cur + lpf->Cof_B0 * lpf->w_prv;
	lpf->w_prv = lpf->w_cur;

	return Vout;
}
