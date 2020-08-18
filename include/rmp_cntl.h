/* =================================================================================
File name:        RMP_CNTL.H  
===================================================================================*/

#ifndef __RMP_CNTL_H__
#define __RMP_CNTL_H__

typedef struct { double				TargetValue; 	// Input: Target input (pu)
				 unsigned long		RampDelayMax;	// Parameter: Maximum delay rate (Q0) - independently with global Q			
		 	 	 double				RampLowLimit;	// Parameter: Minimum limit (pu)				  
				 double				RampHighLimit;	// Parameter: Maximum limit (pu)
				 unsigned long		RampDelayCount; // Variable: Incremental delay (Q0) - independently with global Q	
				 double				SetpointValue;	// Output: Target output (pu)				 
				 unsigned long		EqualFlag;		// Output: Flag output (Q0) - independently with global Q
				 double				Tmp;			// Variable: Temp variable
				 double				Resolution;
		  	   } RMPCNTL;	            


/*-----------------------------------------------------------------------------
Default initalizer for the RMPCNTL object.
-----------------------------------------------------------------------------*/                     
#define RMPCNTL_DEFAULTS {  0, 		 \
                            0,		 \
							0,		 \
                            0,		 \
                            0,       \
                          	0,       \
                          	0,       \
                          	0,       \
							0,       \
                   		  }

/*------------------------------------------------------------------------------
 	RAMP Controller Macro Definition
------------------------------------------------------------------------------*/

#define RC_MACRO(v)																	\
	v.Tmp = v.TargetValue - v.SetpointValue;										\
if (fabs(v.Tmp) >= v.Resolution)				    								\
{																					\
	v.RampDelayCount++	;															\
		if (v.RampDelayCount >= v.RampDelayMax)										\
		{																			\
			if (v.TargetValue >= v.SetpointValue)									\
				v.SetpointValue += v.Resolution;									\
			else																	\
				v.SetpointValue -= v.Resolution;									\
			if(v.SetpointValue > v.RampHighLimit)		v.SetpointValue = v.RampHighLimit;			\
			else if(v.SetpointValue < v.RampLowLimit)	v.SetpointValue = v.RampLowLimit;			\
			v.RampDelayCount = 0;													\
																					\
		}																			\
}																					\
else v.EqualFlag = 1;

#endif // __RMP_CNTL_H__

