// TI File $Revision: /main/5 $
// Checkin $Date: October 23, 2007   13:34:09 $
//###########################################################################
//
// FILE:	DSP2833x_Adc.c
//
// TITLE:	DSP2833x ADC Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################

#pragma CODE_SECTION(ConfigAdc, "ramfuncs");
#pragma CODE_SECTION(StartAdc, "ramfuncs");

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define ADC_usDELAY  5000L

//---------------------------------------------------------------------------
// InitAdc:
//---------------------------------------------------------------------------
// This function initializes ADC to a known state.
//
void InitAdc(void)
{
    extern void DSP28x_usDelay(Uint32 Count);


    // *IMPORTANT*
	// The ADC_cal function, which  copies the ADC calibration values from TI reserved
	// OTP into the ADCREFSEL and ADCOFFTRIM registers, occurs automatically in the
	// Boot ROM. If the boot ROM code is bypassed during the debug process, the
	// following function MUST be called for the ADC to function according
	// to specification. The clocks to the ADC MUST be enabled before calling this
	// function.
	// See the device data manual and/or the ADC Reference
	// Manual for more information.

	    EALLOW;
		SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
		ADC_cal();
		EDIS;




    // To powerup the ADC the ADCENCLK bit should be set first to enable
    // clocks, followed by powering up the bandgap, reference circuitry, and ADC core.
    // Before the first conversion is performed a 5ms delay must be observed
	// after power up to give all analog circuits time to power up and settle

    // Please note that for the delay function below to operate correctly the
	// CPU_RATE define statement in the DSP2833x_Examples.h file must
	// contain the correct CPU clock period in nanoseconds.

    AdcRegs.ADCTRL3.all = 0x00E0;  // Power up bandgap/reference/ADC circuits
    DELAY_US(ADC_usDELAY);         // Delay before converting ADC channels
}

void ConfigAdc(void)
{
		AdcRegs.ADCTRL1.bit.CPS = 0;				// ADCCLK = 75MHz/(3*2)/(1+1) = 6.25MHz
		AdcRegs.ADCTRL1.bit.ACQ_PS = 4;				// 샘플/홀드 사이클 = ACQ_PS + 1 = 4 (ADCCLK기준)
		AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;			// 시퀀스 모드 설정: 직렬 시퀀스 모드 (0:병렬 모드, 1:직렬 모드)
//		AdcRegs.ADCTRL3.bit.SMODE_SEL = 0; 			// Setup simultaneous sampling mode
		AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ = 1; 		// ePWM_SOCB로 ADC 시퀀스 시동
		AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;		// ADC 시퀀스 완료시 인터럽트 발생 설정
		//AdcRegs.ADCTRL2.bit.INT_ENA_SEQ2 = 1;
		AdcRegs.ADCTRL3.bit.ADCCLKPS = 0;	   		// ADCCLK = HSPCLK/(ADCCLKPS*2)/(CPS+1)

	    AdcRegs.ADCMAXCONV.all = 13;  		 	// ADC 채널수 설정: 7개(=MAX_CONV+1)채널을 ADC
	    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0; 				// ADC 순서 설정: 첫번째로 ADCINA0 채널을 ADC
		AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 1;
		AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 2;
		AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 3;
		AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 4;
		AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 5;
		AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 6;
		AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 7;
		AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 8;
		AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 9;
		AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 10;
		AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 11;
		AdcRegs.ADCCHSELSEQ4.bit.CONV12 = 12;
		AdcRegs.ADCCHSELSEQ4.bit.CONV13 = 13;
		AdcRegs.ADCCHSELSEQ4.bit.CONV14 = 14;


}

void StartAdc(void)
{
	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;					// ADC 시퀀스 시작
	//AdcRegs.ADCTRL2.bit.SOC_SEQ2 = 1;
	DELAY_US(1.72L);								// ADC 시퀀스 변환시간(약1.72usec)만큼 지연
/*
#if RECTIFIER
	AdcValue.inputRi = (AdcRegs.ADCRESULT0>>4) & 0x0FFF;
	AdcValue.inputSi = (AdcRegs.ADCRESULT1>>4) & 0x0FFF;
	AdcValue.inputTi = (AdcRegs.ADCRESULT2>>4) & 0x0FFF;
	AdcValue.batteryIdc = (AdcRegs.ADCRESULT3>>4) & 0x0FFF;
	AdcValue.mrv = (AdcRegs.ADCRESULT4>>4) & 0x0FFF;
	AdcValue.msv = (AdcRegs.ADCRESULT5>>4) & 0x0FFF;
	AdcValue.mtv = (AdcRegs.ADCRESULT6>>4) & 0x0FFF;
	AdcValue.brv = (AdcRegs.ADCRESULT7>>4) & 0x0FFF;
	AdcValue.bsv = AdcRegs.ADCRESULT8 & 0x0FFF;
	AdcValue.btv = AdcRegs.ADCRESULT9 & 0x0FFF;
	AdcValue.batVdcp = AdcRegs.ADCRESULT10 & 0x0FFF;
	AdcValue.batVdcn = AdcRegs.ADCRESULT11 & 0x0FFF;
	AdcValue.temperature = AdcRegs.ADCRESULT12 & 0x0FFF;
	AdcValue.batVdc = AdcValue.batVdcp + AdcValue.batVdcn;
#endif//#if RECTIFIER
*/
	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;					// ADC 시퀀서 리셋
	//AdcRegs.ADCTRL2.bit.RST_SEQ2 = 1;
	DELAY_US(0.64L);									// ADC 시퀀서 리셋시간(약0.64usec)만큼 지연

/*
	p->mrv = 0.0007326 * p->mrv;
	p->mrv = (p->mrv - 1.5) * 354.011;

	p->msv = 0.0007326 * p->msv;
	p->msv = (p->msv - 1.5) * 359.002;

	p->mtv = 0.0007326 * p->mtv;
	p->mtv = (p->mtv - 1.5) * 355.150;

	p->Conv_ri = 0.0007326 * p->Conv_ri;
	p->Conv_ri = (p->Conv_ri - 1.5) * 143.089;

	p->Conv_si = 0.0007326 * p->Conv_si;
	p->Conv_si = (p->Conv_si - 1.5) * 134.969;

	p->Conv_ti = 0.0007326 * p->Conv_ti;
	p->Conv_ti = (p->Conv_ti - 1.5) * 139.683;

	p->Bat_VdcP = 0.0007326 * p->Bat_VdcP;
	p->Bat_VdcP = 407.89 * p->Bat_VdcP;
	p->Bat_VdcP = p->Bat_VdcP - 401.58;

	p->Bat_VdcN = 0.0007326 * p->Bat_VdcN;
	p->Bat_VdcN = 276.79 * p->Bat_VdcN;
	p->Bat_VdcN = p->Bat_VdcN - 170.54;
*/

}


//===========================================================================
// End of file.
//===========================================================================
