/*
 * main.h
 *
 *  Created on: 2017. 8. 15.
 *      Author: Administrator
 */

#ifndef INCLUDE_MAIN_H_
#define INCLUDE_MAIN_H_
#include "DSP28x_Project.h"

#define	SW_START		(GpioDataRegs.GPCDAT.bit.GPIO72)
#define	SW_STOP			(GpioDataRegs.GPCDAT.bit.GPIO73)
#define DIGITAL_OUTPUT	(*(Uint32 *)0x00004200)



void setExtV(double value);
void setExtI(double value);
unsigned int checkError(void);
void InitDsp(void);

#endif /* INCLUDE_MAIN_H_ */
