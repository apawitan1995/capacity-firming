// TI File $Revision: /main/1 $
// Checkin $Date: August 18, 2006   13:46:19 $
//###########################################################################
//
// FILE:   DSP2833x_EPwm.c
//
// TITLE:  DSP2833x ePWM Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################

#pragma CODE_SECTION(ConfigEPwm, "ramfuncs");
#pragma CODE_SECTION(ConfigEPwm1, "ramfuncs");
#pragma CODE_SECTION(ConfigEPwm2, "ramfuncs");
#pragma CODE_SECTION(ConfigEPwm3, "ramfuncs");
#pragma CODE_SECTION(ConfigEPwm4, "ramfuncs");
#pragma CODE_SECTION(ConfigEPwm5, "ramfuncs");
#pragma CODE_SECTION(ConfigEPwm6, "ramfuncs");
#pragma CODE_SECTION(StartEPwm, "ramfuncs");
#pragma CODE_SECTION(StopEPwm, "ramfuncs");

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define	SYSCLK		150E6	/* 150MHz */
#define	TBCLK		150E6	/* 150MHz */
#define	PWMCARRIER	10E3	/* 10kHz */

//---------------------------------------------------------------------------
// InitEPwm: 
//---------------------------------------------------------------------------
// This function initializes the ePWM(s) to a known state.
//
void InitEPwm(void)
{
   // Initialize ePWM1/2/3/4/5/6

   //tbd...
 
}

//---------------------------------------------------------------------------
// Example: InitEPwmGpio: 
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as ePWM pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.  
// 

void InitEPwmGpio(void)
{
   InitEPwm1Gpio();
   InitEPwm2Gpio();
   InitEPwm3Gpio();
#if DSP28_EPWM4
   InitEPwm4Gpio();
#endif // endif DSP28_EPWM4
#if DSP28_EPWM5    
  InitEPwm5Gpio();
#endif // endif DSP28_EPWM5
#if DSP28_EPWM6
   InitEPwm6Gpio();
#endif // endif DSP28_EPWM6 
//   InitEPwmSyncGpio();
//   InitTzGpio();
}

void ConfigEPwm(void)
{
	ConfigEPwm1();
	ConfigEPwm2();
	ConfigEPwm3();
#if DSP28_EPWM4
	ConfigEPwm4();
#endif // endif DSP28_EPWM4
#if DSP28_EPWM5
	ConfigEPwm5();
#endif // endif DSP28_EPWM5
#if DSP28_EPWM6
	ConfigEPwm6();
#endif // endif DSP28_EPWM6
//	ConfigTz();
}

void StartEPwm(void)
{
	EPwm1Regs.AQCSFRC.bit.CSFA = 0;
	EPwm1Regs.AQCSFRC.bit.CSFB = 0;
	EPwm2Regs.AQCSFRC.bit.CSFA = 0;
	EPwm2Regs.AQCSFRC.bit.CSFB = 0;
	EPwm3Regs.AQCSFRC.bit.CSFA = 0;
	EPwm3Regs.AQCSFRC.bit.CSFB = 0;

	EPwm4Regs.AQCSFRC.bit.CSFA = 0;
	EPwm4Regs.AQCSFRC.bit.CSFB = 0;
	EPwm5Regs.AQCSFRC.bit.CSFA = 0;
	EPwm5Regs.AQCSFRC.bit.CSFB = 0;
	EPwm6Regs.AQCSFRC.bit.CSFA = 0;
	EPwm6Regs.AQCSFRC.bit.CSFB = 0;

	EPwm1Regs.DBCTL.bit.OUT_MODE = 3;
	EPwm2Regs.DBCTL.bit.OUT_MODE = 3;
	EPwm3Regs.DBCTL.bit.OUT_MODE = 3;

	EPwm4Regs.DBCTL.bit.OUT_MODE = 3;
	EPwm5Regs.DBCTL.bit.OUT_MODE = 3;
	EPwm6Regs.DBCTL.bit.OUT_MODE = 3;


//	InitTzGpio();
//	ConfigTz();

}

void StopEPwm(void)
{

	EPwm1Regs.AQCSFRC.bit.CSFA = 2;
	EPwm1Regs.AQCSFRC.bit.CSFB = 2;
	EPwm2Regs.AQCSFRC.bit.CSFA = 2;
	EPwm2Regs.AQCSFRC.bit.CSFB = 2;
	EPwm3Regs.AQCSFRC.bit.CSFA = 2;
	EPwm3Regs.AQCSFRC.bit.CSFB = 2; // new dsp

	EPwm4Regs.AQCSFRC.bit.CSFA = 2;
	EPwm4Regs.AQCSFRC.bit.CSFB = 2;
	EPwm5Regs.AQCSFRC.bit.CSFA = 2;
	EPwm5Regs.AQCSFRC.bit.CSFB = 2;
	EPwm6Regs.AQCSFRC.bit.CSFA = 2;
	EPwm6Regs.AQCSFRC.bit.CSFB = 2; // new dsp


/*
	EPwm1Regs.AQCSFRC.bit.CSFA = 1;
	EPwm1Regs.AQCSFRC.bit.CSFB = 1;
	EPwm2Regs.AQCSFRC.bit.CSFA = 1;
	EPwm2Regs.AQCSFRC.bit.CSFB = 1;
	EPwm3Regs.AQCSFRC.bit.CSFA = 1;
	EPwm3Regs.AQCSFRC.bit.CSFB = 1;
*/
	EPwm1Regs.DBCTL.bit.OUT_MODE = 0;
	EPwm2Regs.DBCTL.bit.OUT_MODE = 0;
	EPwm3Regs.DBCTL.bit.OUT_MODE = 0;

	EPwm4Regs.DBCTL.bit.OUT_MODE = 0;
	EPwm5Regs.DBCTL.bit.OUT_MODE = 0;
	EPwm6Regs.DBCTL.bit.OUT_MODE = 0;


}

void InitEPwm1Gpio(void)
{
   EALLOW;
   
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;    // Enable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;    // Enable pull-up on GPIO1 (EPWM1B)   
   
/* Configure ePWM-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM1 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B
   
    EDIS;
}

void InitEPwm2Gpio(void)
{
   EALLOW;
	
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;    // Enable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;    // Enable pull-up on GPIO3 (EPWM3B)

/* Configure ePWM-2 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM2 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B
   
    EDIS;
}

void InitEPwm3Gpio(void)
{
   EALLOW;
   
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;    // Enable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;    // Enable pull-up on GPIO5 (EPWM3B)
       
/* Configure ePWM-3 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM3 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B
	
    EDIS;
}


#if DSP28_EPWM4
void InitEPwm4Gpio(void)
{
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWM4A)
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;    // Enable pull-up on GPIO7 (EPWM4B)

/* Configure ePWM-4 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM4 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO6 as EPWM4A
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;   // Configure GPIO7 as EPWM4B
	
    EDIS;
}
#endif // endif DSP28_EPWM4  


#if DSP28_EPWM5
void InitEPwm5Gpio(void)
{
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;    // Enable pull-up on GPIO8 (EPWM5A)
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;    // Enable pull-up on GPIO9 (EPWM5B)

/* Configure ePWM-5 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM5 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;   // Configure GPIO8 as EPWM5A
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;   // Configure GPIO9 as EPWM5B
	
    EDIS;
}
#endif // endif DSP28_EPWM5


#if DSP28_EPWM6
void InitEPwm6Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;    // Enable pull-up on GPIO10 (EPWM6A)
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;    // Enable pull-up on GPIO11 (EPWM6B)

/* Configure ePWM-6 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM6 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;   // Configure GPIO10 as EPWM6A
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;   // Configure GPIO11 as EPWM6B
	
    EDIS;
}
#endif // endif DSP28_EPWM6  

//---------------------------------------------------------------------------
// Example: InitEPwmSyncGpio: 
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as ePWM Synch pins
//

void InitEPwmSyncGpio(void)
{

   EALLOW;

/* Configure EPWMSYNCI  */
   
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   // Enable pull-up on GPIO32 (EPWMSYNCI)    

/* Set qualification for selected pins to asynch only */
// This will select synch to SYSCLKOUT for the selected pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO6 = 0;   // Synch to SYSCLKOUT GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 0;  // Synch to SYSCLKOUT GPIO32 (EPWMSYNCI)    

/* Configure EPwmSync pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPwmSync functional pins.
// Comment out other unwanted lines.   

   GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 2;    // Enable pull-up on GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 2;   // Enable pull-up on GPIO32 (EPWMSYNCI)    



/* Configure EPWMSYNC0  */

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWMSYNC0)
   GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;   // Enable pull-up on GPIO33 (EPWMSYNC0)    

// GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 3;    // Enable pull-up on GPIO6 (EPWMSYNC0)
   GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 2;   // Enable pull-up on GPIO33 (EPWMSYNC0)    

}



//---------------------------------------------------------------------------
// Example: InitTzGpio: 
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as Trip Zone (TZ) pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.  
// 

void InitTzGpio(void)
{
EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.
	GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;    // Enable pull-up on GPIO12 (TZ1)
//   GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;    // Enable pull-up on GPIO13 (TZ2)
//   GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;    // Enable pull-up on GPIO14 (TZ3)
//   GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;    // Enable pull-up on GPIO15 (TZ4)

//   GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;    // Enable pull-up on GPIO16 (TZ5)
// GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up on GPIO28 (TZ5)

//  GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;    // Enable pull-up on GPIO17 (TZ6)
// GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;    // Enable pull-up on GPIO29 (TZ6)  
   
/* Set qualification for selected pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.  
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3;  // Asynch input GPIO12 (TZ1)
//   GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3;  // Asynch input GPIO13 (TZ2)
//   GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3;  // Asynch input GPIO14 (TZ3)
//   GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;  // Asynch input GPIO15 (TZ4)

//   GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3;  // Asynch input GPIO16 (TZ5)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (TZ5)

//   GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3;  // Asynch input GPIO17 (TZ6)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 3;  // Asynch input GPIO29 (TZ6)  

   
/* Configure TZ pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be TZ functional pins.
// Comment out other unwanted lines.   
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;  // Configure GPIO12 as TZ1
//   GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 1;  // Configure GPIO13 as TZ2
//   GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 1;  // Configure GPIO14 as TZ3
//   GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 1;  // Configure GPIO15 as TZ4
//   GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 3;  // Configure GPIO16 as TZ5
// GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 3;  // Configure GPIO28 as TZ5
// GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 3;  // Configure GPIO17 as TZ6
// GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 3;  // Configure GPIO29 as TZ6  
EDIS;
}

void ConfigEPwm1(void)
{
// Setup TBCLK
	EPwm1Regs.TBPRD = (SYSCLK/PWMCARRIER)/2;
	EPwm1Regs.TBCTR = 0;

// Set Compare values
	EPwm1Regs.CMPA.half.CMPA = 0;
	EPwm1Regs.CMPB = 0;

// Setup counter mode
	EPwm1Regs.TBCTL.bit.CTRMODE = 2;
	EPwm1Regs.TBPHS.half.TBPHS = 0;
	EPwm1Regs.TBCTL.bit.PHSEN = 0;
	EPwm1Regs.TBCTL.bit.PRDLD = 0;
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;
	EPwm1Regs.TBCTL.bit.CLKDIV = 0;

// Setup shadowing
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = 0;
	EPwm1Regs.CMPCTL.bit.LOADAMODE = 0;

// Set actions
	EPwm1Regs.AQCTLA.bit.CAU = 1;
	EPwm1Regs.AQCTLA.bit.CAD = 2; // New dsp control board

//	EPwm1Regs.AQCTLA.bit.CAU = 2;
//	EPwm1Regs.AQCTLA.bit.CAD = 1; // A dsp

//	EPwm1Regs.AQCTLB.bit.CAU = 1;
//	EPwm1Regs.AQCTLB.bit.CAD = 2;

// Set Dead-time
	EPwm1Regs.DBCTL.bit.IN_MODE = 0;
	EPwm1Regs.DBCTL.bit.OUT_MODE = 3;
	EPwm1Regs.DBCTL.bit.POLSEL = 1;
	EPwm1Regs.DBFED = 2*300;
	EPwm1Regs.DBRED = 2*300;

// Set Interrupts
	EPwm1Regs.ETSEL.bit.INTSEL = 1;
	EPwm1Regs.ETPS.bit.INTPRD = 1;
	EPwm1Regs.ETSEL.bit.INTEN = 1;

	EPwm1Regs.ETSEL.bit.SOCBEN = 1;
	EPwm1Regs.ETSEL.bit.SOCBSEL = 2;
	EPwm1Regs.ETPS.bit.SOCBPRD = 1;
}

void ConfigEPwm2(void)
{
	/* Setup TBCLK */
	EPwm2Regs.TBPRD = (SYSCLK/PWMCARRIER)/2;	/* Set Timer Period */
	EPwm2Regs.TBCTR = 0;						/* Clear Counter */

	/* Set Compare values */
	EPwm2Regs.CMPA.half.CMPA = 0;	/* Set Compare A value to 50% */
	EPwm2Regs.CMPB = 0;

	/* Setup counter mode */
	EPwm2Regs.TBCTL.bit.CTRMODE = 2;		/* Count Up (Asymmetric) */
	EPwm2Regs.TBPHS.half.TBPHS = 0;			/* Phase is 0 */
	EPwm2Regs.TBCTL.bit.PHSEN = 0;			/* Disable phase loading */
	EPwm2Regs.TBCTL.bit.PRDLD = 0;			/* Period Register is loaded from its shadow when CNTR=Zero */
	EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0;		/* Clock ratio to SYSCLKOUT */
	EPwm2Regs.TBCTL.bit.CLKDIV = 0;			/* TBCLK = SYSCLK / (HSPCLKDIV * CLKDIV) */

	/* Setup shadowing */
	EPwm2Regs.CMPCTL.bit.SHDWAMODE = 0;		/* Enable Shadowing */
	EPwm2Regs.CMPCTL.bit.LOADAMODE = 0;		/* Load on CNTR=Zero */

	/* Set actions */
	EPwm2Regs.AQCTLA.bit.CAU = 1;			// Set EPWMxA on event A, up count
	EPwm2Regs.AQCTLA.bit.CAD = 2;			// Clear EPWMxA on event A, down count // New dsp

//	EPwm2Regs.AQCTLA.bit.CAU = 2;			// Set EPWMxA on event A, up count
//	EPwm2Regs.AQCTLA.bit.CAD = 1;			// Clear EPWMxA on event A, down count // Aju dsp

//	EPwm2Regs.AQCTLB.bit.CAU = 1;			// Set EPWMxA on event A, up count
//	EPwm2Regs.AQCTLB.bit.CAD = 2;			// Clear EPWMxA on event A, down count

// Set Dead-time
	EPwm2Regs.DBCTL.bit.IN_MODE = 0;		// EPWMxA is the source for both falling-edge & rising-edge delay
	EPwm2Regs.DBCTL.bit.OUT_MODE = 3;		// Dead-band is fully enabled for both rising-edge delay on EPWMxA and falling-edge delay on EPWMxB
	EPwm2Regs.DBCTL.bit.POLSEL = 1;			// Active High Complementary (AHC). EPWMxB is inverted
	EPwm2Regs.DBFED = 2*300;					// 1usec
	EPwm2Regs.DBRED = 2*300;					// 1usec
}

void ConfigEPwm3(void)
{
	EPwm3Regs.TBPRD = (SYSCLK/PWMCARRIER)/2;
	EPwm3Regs.TBCTR = 0;

	EPwm3Regs.CMPA.half.CMPA = 0;
	EPwm3Regs.CMPB = 0;

	EPwm3Regs.TBCTL.bit.CTRMODE = 2;
	EPwm3Regs.TBPHS.half.TBPHS = 0;
	EPwm3Regs.TBCTL.bit.PHSEN = 0;
	EPwm3Regs.TBCTL.bit.PRDLD = 0;
	EPwm3Regs.TBCTL.bit.HSPCLKDIV = 0;
	EPwm3Regs.TBCTL.bit.CLKDIV = 0;

	EPwm3Regs.CMPCTL.bit.SHDWAMODE = 0;
	EPwm3Regs.CMPCTL.bit.LOADAMODE = 0;

	EPwm3Regs.AQCTLA.bit.CAU = 1;
	EPwm3Regs.AQCTLA.bit.CAD = 2; // New dsp

//	EPwm3Regs.AQCTLA.bit.CAU = 2;
//	EPwm3Regs.AQCTLA.bit.CAD = 1; // Aju dsp

//	EPwm3Regs.AQCTLB.bit.CAU = 1;
//	EPwm3Regs.AQCTLB.bit.CAD = 2;

	EPwm3Regs.DBCTL.bit.IN_MODE = 0;
	EPwm3Regs.DBCTL.bit.OUT_MODE = 3;
	EPwm3Regs.DBCTL.bit.POLSEL = 1;
	EPwm3Regs.DBFED = 2*300;
	EPwm3Regs.DBRED = 2*300;
}

void ConfigEPwm4(void)
{
	/* Setup TBCLK */
	EPwm4Regs.TBPRD = (SYSCLK/PWMCARRIER)/2;	/* Set Timer Period */
	EPwm4Regs.TBCTR = 0;						/* Clear Counter */

	/* Set Compare values */
	EPwm4Regs.CMPA.half.CMPA = 0;	/* Set Compare A value to 50% */
	EPwm4Regs.CMPB = 0;

	/* Setup counter mode */
	EPwm4Regs.TBCTL.bit.CTRMODE = 2;		/* Count Up (Asymmetric) */
	EPwm4Regs.TBPHS.half.TBPHS = 0;			/* Phase is 0 */
	EPwm4Regs.TBCTL.bit.PHSEN = 0;			/* Disable phase loading */
	EPwm4Regs.TBCTL.bit.PRDLD = 0;			/* Period Register is loaded from its shadow when CNTR=Zero */
	EPwm4Regs.TBCTL.bit.HSPCLKDIV = 0;		/* Clock ratio to SYSCLKOUT */
	EPwm4Regs.TBCTL.bit.CLKDIV = 0;			/* TBCLK = SYSCLK / (HSPCLKDIV * CLKDIV) */

	/* Setup shadowing */
	EPwm4Regs.CMPCTL.bit.SHDWAMODE = 0;		/* Enable Shadowing */
	EPwm4Regs.CMPCTL.bit.LOADAMODE = 0;		/* Load on CNTR=Zero */

	/* Set actions */
	EPwm4Regs.AQCTLA.bit.CAU = 1;			// Set EPWMxA on event A, up count
	EPwm4Regs.AQCTLA.bit.CAD = 2;			// Clear EPWMxA on event A, down count
//	EPwm4Regs.AQCTLB.bit.CAU = 2;			// Set EPWMxA on event A, up count
//	EPwm4Regs.AQCTLB.bit.CAD = 1;			// Clear EPWMxA on event A, down count

// Set Dead-time
	EPwm4Regs.DBCTL.bit.IN_MODE = 0;		// EPWMxA is the source for both falling-edge & rising-edge delay
	EPwm4Regs.DBCTL.bit.OUT_MODE = 3;		// Dead-band is fully enabled for both rising-edge delay on EPWMxA and falling-edge delay on EPWMxB
	EPwm4Regs.DBCTL.bit.POLSEL = 1;			// Active High Complementary (AHC). EPWMxB is inverted
	EPwm4Regs.DBFED = 2*300;					// 1usec
	EPwm4Regs.DBRED = 2*300;					// 1usec

// Set Interrupts
	EPwm4Regs.ETSEL.bit.INTSEL = 1;
	EPwm4Regs.ETPS.bit.INTPRD = 1;
	EPwm4Regs.ETSEL.bit.INTEN = 1;

	EPwm4Regs.ETSEL.bit.SOCBEN = 1;
	EPwm4Regs.ETSEL.bit.SOCBSEL = 2;
	EPwm4Regs.ETPS.bit.SOCBPRD = 1;
}

void ConfigEPwm5(void)
{
	/* Setup TBCLK */
	EPwm5Regs.TBPRD = (SYSCLK/PWMCARRIER)/2;	/* Set Timer Period */
	EPwm5Regs.TBCTR = 0;						/* Clear Counter */

	/* Set Compare values */
	EPwm5Regs.CMPA.half.CMPA = 0;	/* Set Compare A value to 50% */
	EPwm5Regs.CMPB = 0;

	/* Setup counter mode */
	EPwm5Regs.TBCTL.bit.CTRMODE = 2;		/* Count Up (Asymmetric) */
	EPwm5Regs.TBPHS.half.TBPHS = 0;			/* Phase is 0 */
	EPwm5Regs.TBCTL.bit.PHSEN = 0;			/* Disable phase loading */
	EPwm5Regs.TBCTL.bit.PRDLD = 0;			/* Period Register is loaded from its shadow when CNTR=Zero */
	EPwm5Regs.TBCTL.bit.HSPCLKDIV = 0;		/* Clock ratio to SYSCLKOUT */
	EPwm5Regs.TBCTL.bit.CLKDIV = 0;			/* TBCLK = SYSCLK / (HSPCLKDIV * CLKDIV) */

	/* Setup shadowing */
	EPwm5Regs.CMPCTL.bit.SHDWAMODE = 0;		/* Enable Shadowing */
	EPwm5Regs.CMPCTL.bit.LOADAMODE = 0;		/* Load on CNTR=Zero */

	/* Set actions */
	EPwm5Regs.AQCTLA.bit.CAU = 1;			// Set EPWMxA on event A, up count
	EPwm5Regs.AQCTLA.bit.CAD = 2;			// Clear EPWMxA on event A, down count
//	EPwm5Regs.AQCTLB.bit.CAU = 2;			// Set EPWMxA on event A, up count
//	EPwm5Regs.AQCTLB.bit.CAD = 1;			// Clear EPWMxA on event A, down count

// Set Dead-time
	EPwm5Regs.DBCTL.bit.IN_MODE = 0;		// EPWMxA is the source for both falling-edge & rising-edge delay
	EPwm5Regs.DBCTL.bit.OUT_MODE = 3;		// Dead-band is fully enabled for both rising-edge delay on EPWMxA and falling-edge delay on EPWMxB
	EPwm5Regs.DBCTL.bit.POLSEL = 1;			// Active High Complementary (AHC). EPWMxB is inverted
	EPwm5Regs.DBFED = 300;					// 1usec
	EPwm5Regs.DBRED = 300;					// 1usec
}

void ConfigEPwm6(void)
{
	/* Setup TBCLK */
	EPwm6Regs.TBPRD = (SYSCLK/PWMCARRIER)/2;	/* Set Timer Period */
	EPwm6Regs.TBCTR = 0;						/* Clear Counter */

	/* Set Compare values */
	EPwm6Regs.CMPA.half.CMPA = 0;	/* Set Compare A value to 50% */
	EPwm6Regs.CMPB = 0;

	/* Setup counter mode */
	EPwm6Regs.TBCTL.bit.CTRMODE = 2;		/* Count Up (Asymmetric) */
	EPwm6Regs.TBPHS.half.TBPHS = 0;			/* Phase is 0 */
	EPwm6Regs.TBCTL.bit.PHSEN = 0;			/* Disable phase loading */
	EPwm6Regs.TBCTL.bit.PRDLD = 0;			/* Period Register is loaded from its shadow when CNTR=Zero */
	EPwm6Regs.TBCTL.bit.HSPCLKDIV = 0;		/* Clock ratio to SYSCLKOUT */
	EPwm6Regs.TBCTL.bit.CLKDIV = 0;			/* TBCLK = SYSCLK / (HSPCLKDIV * CLKDIV) */

	/* Setup shadowing */
	EPwm6Regs.CMPCTL.bit.SHDWAMODE = 0;		/* Enable Shadowing */
	EPwm6Regs.CMPCTL.bit.LOADAMODE = 0;		/* Load on CNTR=Zero */

	/* Set actions */
	EPwm6Regs.AQCTLA.bit.CAU = 1;			// Set EPWMxA on event A, up count
	EPwm6Regs.AQCTLA.bit.CAD = 2;			// Clear EPWMxA on event A, down count
//	EPwm6Regs.AQCTLB.bit.CAU = 2;			// Set EPWMxA on event A, up count
//	EPwm6Regs.AQCTLB.bit.CAD = 1;			// Clear EPWMxA on event A, down count

// Set Dead-time
	EPwm6Regs.DBCTL.bit.IN_MODE = 0;		// EPWMxA is the source for both falling-edge & rising-edge delay
	EPwm6Regs.DBCTL.bit.OUT_MODE = 3;		// Dead-band is fully enabled for both rising-edge delay on EPWMxA and falling-edge delay on EPWMxB
	EPwm6Regs.DBCTL.bit.POLSEL = 1;			// Active High Complementary (AHC). EPWMxB is inverted
	EPwm6Regs.DBFED = 300;					// 1usec
	EPwm6Regs.DBRED = 300;					// 1usec
}

void ConfigTz(void)
{
EALLOW;
//Set Trip Action
	EPwm1Regs.TZSEL.bit.OSHT1 = 1;
	EPwm2Regs.TZSEL.bit.OSHT1 = 1;
	EPwm3Regs.TZSEL.bit.OSHT1 = 1;

	EPwm4Regs.TZSEL.bit.OSHT1 = 1;
	EPwm5Regs.TZSEL.bit.OSHT1 = 1;
	EPwm6Regs.TZSEL.bit.OSHT1 = 1;

//	EPwm1Regs.TZSEL.bit.OSHT2 = 1;
//	EPwm2Regs.TZSEL.bit.OSHT2 = 1;
//	EPwm3Regs.TZSEL.bit.OSHT2 = 1;

// What do we want the TZ1, TZ2 to do?
	EPwm1Regs.TZCTL.bit.TZA = 1;
	EPwm1Regs.TZCTL.bit.TZB = 1;
	EPwm2Regs.TZCTL.bit.TZA = 1;
	EPwm2Regs.TZCTL.bit.TZB = 1;
	EPwm3Regs.TZCTL.bit.TZA = 1;
	EPwm3Regs.TZCTL.bit.TZB = 1;

	EPwm4Regs.TZCTL.bit.TZA = 1;
	EPwm4Regs.TZCTL.bit.TZB = 1;
	EPwm5Regs.TZCTL.bit.TZA = 1;
	EPwm5Regs.TZCTL.bit.TZB = 1;
	EPwm6Regs.TZCTL.bit.TZA = 1;
	EPwm6Regs.TZCTL.bit.TZB = 1;

// Enable TZ interrupt
	EPwm1Regs.TZEINT.bit.OST = 1;
	EPwm2Regs.TZEINT.bit.OST = 1;
	EPwm3Regs.TZEINT.bit.OST = 1;

	EPwm4Regs.TZEINT.bit.OST = 1;
	EPwm5Regs.TZEINT.bit.OST = 1;
	EPwm6Regs.TZEINT.bit.OST = 1;
EDIS;
/*
EALLOW;
//Set Trip Action
	EPwm4Regs.TZSEL.bit.OSHT5 = 1;
	EPwm5Regs.TZSEL.bit.OSHT5 = 1;
	EPwm6Regs.TZSEL.bit.OSHT5 = 1;

// What do we want the TZ1, TZ2 to do?
  	EPwm4Regs.TZCTL.bit.TZA = 2;
   	EPwm4Regs.TZCTL.bit.TZB = 2;
   	EPwm5Regs.TZCTL.bit.TZA = 2;
  	EPwm5Regs.TZCTL.bit.TZB = 2;
	EPwm6Regs.TZCTL.bit.TZA = 2;
   	EPwm6Regs.TZCTL.bit.TZB = 2;

// Enable TZ interrupt
	EPwm4Regs.TZEINT.bit.OST = 1;
	EPwm5Regs.TZEINT.bit.OST = 1;
	EPwm6Regs.TZEINT.bit.OST = 1;
EDIS;
*/
}

//===========================================================================
// End of file.
//===========================================================================
