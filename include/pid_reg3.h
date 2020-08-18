/* =================================================================================
File name:       PID_REG3.H  (IQ version)                    
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type, and macro definitions for the PIDREG3.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 10-15-2009	Version 1.0
------------------------------------------------------------------------------*/
#ifndef __PIDREG3_H__
#define __PIDREG3_H__

typedef struct {	float32  Ref;   			// Input: Reference input
					float32  Fdb;   			// Input: Feedback input
					float32  Err;				// Variable: Error
					float32  Err_pre;
					float32  Kp;				// Parameter: Proportional gain
					float32  Up;				// Variable: Proportional output
					float32  Ui;				// Variable: Integral output
					float32  Ud;				// Variable: Derivative output
					float32  OutPreSat; 		// Variable: Pre-saturated output
					float32  OutMax;		    // Parameter: Maximum output
					float32  OutMin;	    	// Parameter: Minimum output
					float32  Out;   			// Output: PID output
					float32  Out_pre;
					float32  SatErr;			// Variable: Saturated difference
					float32  Ki;			    // Parameter: Integral gain
					float32  Ka;		     	// Parameter: Integral correction gain
					float32  Kd; 		        // Parameter: Derivative gain
					float32  Up1;		   	    // History: Previous proportional output
		 	 	} PIDREG3;	            

typedef PIDREG3 *PIDREG3_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the PIDREG3 object.
-----------------------------------------------------------------------------*/                     
#define PIDREG3_DEFAULTS { 0, 			\
                           0, 			\
                           0, 			\
                           0,			\
                           0, 			\
                           0, 			\
                           0, 			\
                           0,			\
                           0,			\
                           0,			\
                           0, 			\
                           0, 			\
                           0,			\
                           0,			\
                           0,			\
                           0, 			\
                           0,			\
                           0,			\
                           }


/*------------------------------------------------------------------------------
 	PID Macro Definition
------------------------------------------------------------------------------*/


/*
#define PID_MACRO(v)												\
		v.Err = v.Ref - v.Fdb; 											\
		v.Up= v.Kp * v.Err;												\
		v.SatErr = v.Out - v.OutPreSat;									\
		v.Ui += v.Err -(v.Ka * v.SatErr);								\
		v.OutPreSat= v.Up + v.Ki * v.Ui;								\
		if(v.OutPreSat > v.OutMax)			v.Out = v.OutMax;			\
		else if(v.OutPreSat < v.OutMin)		v.Out = v.OutMin;			\
		else v.Out = v.OutPreSat;										\
		v.Up1 = v.Up;
*/

#define PID_MACRO(v)												\
		v.Out_pre = v.Out;											\
		v.Err_pre = v.Err;											\
		v.Err = v.Ref - v.Fdb; 											\
		v.Up = v.Kp * (v.Err-v.Err_pre);								\
		v.Ui = v.Ki * v.Err;			                 				\
		v.Out = v.Out_pre + v.Up + v.Ui;								\
		if(v.Out > v.OutMax)			v.Out = v.OutMax;			\
		else if(v.Out < v.OutMin)		v.Out = v.OutMin;			\
		else v.Out = v.Out;										\
		v.Up1 = v.Up;


#endif // __PIDREG3_H__


