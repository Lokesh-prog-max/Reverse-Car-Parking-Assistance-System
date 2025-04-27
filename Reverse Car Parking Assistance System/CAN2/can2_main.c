#include <LPC21XX.h>
#include"Header1.h"
#define TRIG (1<<6)      
#define ECHO (1<<7)      
#define echo ((IOPIN0>>7)&1)

CAN1 v1,r1;
u32 flag,f=0;
int main(void)
{
	float distance=0;
  
	can2_init();
	 uart0_init(9600);
	config_vic();
	en_int();
	
	IO0DIR |= TRIG;		              
	uart0_tx_string("welcome\r\n");

	while(1)
	{
		if(flag==1)
		{
			uart0_tx_string("interrupt triggered\r\n");
			f=0;
			if(v1.rtr==1)                          //if it is remote frame
			{
				uart0_tx_string("remote frame received\r\n");

			
			
				IO0SET = TRIG;
				delay_us(10);
				IO0CLR = TRIG;

				while(!echo);    
				T0TC=T0PC=0;
				T0TCR=1;        
				while(echo);  
				T0TCR=0;        
				distance = T0TC;
				distance = (0.0343 * distance)/2; 
				//distance=T0TC/59;
				uart0_tx_integer(distance);
				uart0_tx_string("\r\n");
				delay_ms(50);                         	
				if(f==1)

					goto L1;

				r1.id=v1.id;
				r1.dlc=v1.dlc;
				r1.rtr=0;
				r1.byteA=distance;
				can2_tx(r1);  
				uart0_tx_string("ultrasonic sensor data transmitted\r\n");
			}
L1:
			if(v1.rtr==0)
			{
				flag=0;
				uart0_tx_string("data frame received\r\n");
			}
		}

	}

}
