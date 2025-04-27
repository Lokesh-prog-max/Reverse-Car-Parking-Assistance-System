#include<LPC21XX.H>
#include"Header.h"
#define sw1 ((IOPIN0>>14)&1)
#define buzzer (1<<21)   
#define LED (1<<17)      

CAN1 v1,t,t1;
u32 flag,c=0,flag1=0;
int main()
{
		
	can2_init();
	uart0_init(9600);
	config_vic();
	en_int();

	//for remote frame
	t.id=0x45;                         
	t.rtr=1;
	t.dlc=4;	 
	//for data frame
	t1.id=0x23;
	t1.rtr=0;
	t1.dlc=2;
	t1.byteA=0x44332211;

	IODIR0=buzzer|LED;
	IOCLR0=buzzer;
	IOSET0=LED;
	uart0_tx_string("welcome\r\n");
	while(1)
	{
		if(sw1==0)
		{
			while(sw1==0);
		//c^=1;
		c=1;
			uart0_tx_integer(c);
			uart0_tx_string("\r\n");
			if(c)
			{  
			    flag1=1;
			    uart0_tx_string("remote frame transmited\r\n");
				can2_tx(t);											
				
			}
			else
			{
				flag1=0;
				can2_tx(t1);											
				uart0_tx_string("data frame transmited\r\n"); 
			}
		}

		if(flag==1)
		{
		    flag=0;
				if(c==1)
			{

			uart0_tx_string("frame received\r\n");
			if((v1.byteA<=100) && (v1.byteA>=60))
			{
				uart0_tx_string("100-60\r\n");
				IOSET0=buzzer;
				IOCLR0=LED;
				delay_ms(500);
				IOCLR0=buzzer;
				IOSET0=LED;
				delay_ms(500);
			}
			if((v1.byteA<=60) && (v1.byteA>=40))
			{
				uart0_tx_string("60-40\r\n");
				IOSET0=buzzer;
				IOCLR0=LED;
				delay_ms(200);
				IOCLR0=buzzer;
				IOSET0=LED;
				delay_ms(200);
			}
			if((v1.byteA<=40) && (v1.byteA>=20))
			{
				uart0_tx_string("40-20\r\n");
				IOSET0=buzzer;
				IOCLR0=LED;
				delay_ms(100);
				IOCLR0=buzzer;
				IOSET0=LED;
				delay_ms(100);
			}
			if((v1.byteA<=20) && (v1.byteA>=10))
			{
				uart0_tx_string("20-10\r\n");
				IOSET0=buzzer;
				IOCLR0=LED;
				delay_ms(50);
				IOCLR0=buzzer;
				IOSET0=LED;	
				delay_ms(50);

			}
			if((v1.byteA<=10))
			{
				uart0_tx_string("10\r\n");
				IOSET0=buzzer;
				IOCLR0=LED;
			 }
			 else
			 {
			     IOCLR0=buzzer;
				 IOSET0=LED;
			 }
			 //delay_ms(1);
			}
		}
	} 
}

