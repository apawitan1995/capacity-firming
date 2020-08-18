#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#define CPU_FREQ				150E6
#define LSPCLK_FREQ				CPU_FREQ/2
#define SCI_FREQ				38400

void scib_xmit(int a)
{
  while (ScibRegs.SCIFFTX.bit.TXFFST != 0) {}
  ScibRegs.SCITXBUF=a;
}

void scib_xmit_Int(int a)
{
	scib_xmit(a/100+48);
	scib_xmit((a%100)/10+48);
	scib_xmit(a%10+48);
}
void scib_xmit_Float0(float a)
{
	int temp = (int)(a*1000);
	if(a<0)
	{
		scib_xmit('-');
		temp = (int)(-a);
	}
	scib_xmit((temp/1000)+48);
	scib_xmit('.');
	scib_xmit((temp%1000)/100+48);
	scib_xmit((temp%100)/10+48);
	scib_xmit((temp%10)+48);
}

void scib_xmit_Float10(float a)
{
	int temp = (int)(a*100);
	if(a<0)
	{
		scib_xmit('-');
		temp = (int)(-a*100);
	}
	scib_xmit((temp/1000)+48);
	scib_xmit((temp%1000)/100+48);
	scib_xmit('.');
	scib_xmit((temp%100)/10+48);
	scib_xmit((temp%10)+48);
}

void scib_xmit_Float100(float a)
{
	int temp = (int)(a*10);
	if(a<0)
	{
		scib_xmit('-');
		temp = (int)(-a*10);
	}
	scib_xmit((temp/1000)+48);
	scib_xmit((temp%1000)/100+48);
	scib_xmit((temp%100)/10+48);
	scib_xmit('.');
	scib_xmit((temp%10)+48);
}

void InitSCI(void)
{
	EALLOW;
	GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;    // Enable pull-up for GPIO22 (SCITXDB)
	GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;    // Enable pull-up for GPIO23 (SCIRXDB)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 3;  // Asynch input GPIO23 (SCIRXDB)
	GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 3;   // Configure GPIO22 for SCITXDB operation
	GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 3;   // Configure GPIO23 for SCIRXDB operation
	EDIS;

	ScibRegs.SCIFFTX.all=0xE040;
	ScibRegs.SCIFFRX.all=0x204f;
	ScibRegs.SCIFFCT.all=0x0;

	ScibRegs.SCICCR.all =0x0007;
	ScibRegs.SCICTL1.all =0x0003;
	ScibRegs.SCICTL2.all =0x0003;
	//ScibRegs.SCICTL2.bit.TXINTENA =1;
	//ScibRegs.SCICTL2.bit.RXBKINTENA =1;

//ScibRegs.SCIHBAUD    =0x0001;
//	ScibRegs.SCILBAUD    =0x00E7;

//	ScicRegs.SCIHBAUD = 0x0000;  // 115200 baud @LSPCLK = 37.5MHz.
//	ScicRegs.SCILBAUD = 0x0027;

//	ScibRegs.SCIHBAUD = 0x0000;
//	ScibRegs.SCILBAUD = (LSPCLK_FREQ/(115200*8))-1;			//  - [SCIHBAUD,SCILBAUD] => 0x01E7 => 9600bps

	ScibRegs.SCIHBAUD = 0x0000;
	ScibRegs.SCILBAUD = (LSPCLK_FREQ/(SCI_FREQ*8))-1;			//  - [SCIHBAUD,SCILBAUD] => 0x01E7 => 9600bps

	ScibRegs.SCICTL1.all =0x0023;

	/*
	ScibRegs.SCIFFTX.all = 0xE040;
	ScibRegs.SCIFFRX.all = 0x204f;
	ScibRegs.SCIFFCT.all = 0x0;


	ScibRegs.SCICTL1.bit.SWRESET = 0;

	ScibRegs.SCICCR.bit.SCICHAR = 7;
	ScibRegs.SCICCR.bit.STOPBITS = 0;
	ScibRegs.SCICTL1.bit.TXENA = 1;
	//	    ScibRegs.SCIHBAUD = 0x0000;
	//	    ScibRegs.SCILBAUD = (LSPCLK_FREQ/(SCI_FREQ*8))-1;			//  - [SCIHBAUD,SCILBAUD] => 0x01E7 => 9600bps

	ScibRegs.SCIHBAUD = 0x0000;
	ScibRegs.SCILBAUD = 0x0027;			//  - [SCIHBAUD,SCILBAUD] => 0x01E7 => 9600bps


	ScibRegs.SCICTL1.bit.SWRESET = 1;
	*/
}

/*

void print_char(char x){
		ScibRegs.SCITXBUF = x & 0x00FF;
}


void macro_print(char *msg, ...){
		va_list ap;
    int i = 0, j = 0;
    int ival;
    float fval;
    char buf[256];
    
    va_start(ap, msg);

    while(msg[i] != '\0'){
    	if(msg[i] == '%'){
    		i++;
    		if(msg[i] == 'd'){
    			ival = va_arg(ap, int);
    			istr(buf, ival);
    			while(buf[j] != '\0'){
    				//if(ScibRegs.SCICTL2.bit.TXRDY){
    				//	print_char(buf[j]);
    				scib_xmit(buf[j]);
    					j++;
    				//}
    			}
    			j = 0;
    		}
    		else if(msg[i] == 'f'){
    			fval = va_arg(ap, float);
    			fstr(buf, fval, 3);
    			while(buf[j] != '\0'){
    			    //if(ScibRegs.SCICTL2.bit.TXRDY){
    			    //	print_char(buf[j]);
    				scib_xmit(buf[j]);
    			    	j++;
    			   // }
    			}
    			j = 0;
    		}
	    	else{}
	    	i++;
    	}
    	else{
    		//if(ScibRegs.SCICTL2.bit.TXRDY){
	    	//	print_char(msg[i]);
    		scib_xmit(buf[j]);
	    		i++;
	    	//}
    	}
    }
    
    va_end(ap);
}

void revstr(char *str){
	int i;
	char tmp;
	int len = strlen(str) - 1;

	for(i = 0; i <= len/2; i++){
		tmp = str[i];
		str[i] = str[len - i];
		str[len - i] = tmp;
	}
}

int istr(char *buf, int src){
	int i = 0;

	if(src < 0){
		src = ~src + 1;

		while(src > 0){
			buf[i] = src%10 + 48;
			src /= 10;
			i++;
		}
		buf[i] = '-';
		i++;
	}
	else if(src > 0){
		while(src > 0){
			buf[i] = src%10 + 48;
			src /= 10;
			i++;
		}
	}
	else{
		buf[i] = src%10 + 48;
		i++;
	}
	buf[i] = '\0';
	revstr(buf);

	return i;
}
int fstr(char *buf, float src, int exp){
	int i = 0;
	unsigned int frac_up, frac_dn;

	if(src < 0){
		buf[i] = '-';
		i++;
		src = -src;
	}

	frac_up = src;
	frac_dn = (src - frac_up) * powf(10, exp);

	i += istr(&buf[i], frac_up);
	buf[i] = '.';
	i++;
	if(frac_dn<100) // fixed By sjy 170808
		{
			buf[i] = '0';
			i++;
		}
		if (frac_dn<10)
		{
			buf[i] = '0';
			i++;
		}
	i += istr(&buf[i], frac_dn);

	return i;
}
*/
