#include "control.h"


void ACR_PI_Clear(ACR *p)
{
	p->eL_k = 0.;
	p->eL_k1 = 0.;
	p->Duty = 0.;
	p->Vo = 0.;
}

void ACR_PI(float IRef, float Imeas, float Vb, float Vs, ACR *p)
{
	if(IRef> IL_MAX) IRef = IL_MAX;
	if(IRef< IL_MIN) IRef = IL_MIN;

	p->eL_k1 = p->eL_k;
	p->eL_k = IRef - Imeas;

	p->Vo += KPC*(p->eL_k - p->eL_k1) + KIC*TS*p->eL_k;
	p->Duty = (p->Vo + Vb)/Vs;

	if(p->Duty > 0.95)
	{
		p->Vo = KPC*p->eL_k;
		p->Duty  = 0.95;
	}
	else if(p->Duty  < 0.)
	{
		p->Vo = KPC*p->eL_k;
		p->Duty  = 0.;
	}

}
