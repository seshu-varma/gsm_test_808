
#include <stdlib.h>
#include "asf.h"
#include "sim_usart.h"
#include "AtCmdWrapper.h"

void rand_genarator();
int wind=0,temperature=0,humidity=0;
#ifdef __cplusplus
extern "C" {
#endif

int main(void)
{

	system_init();
	/*Initialize the delay driver*/
	delay_init();
	/*Initialize the usart driver*/
	sim_usart_init();
	delay_ms(100);
	gsminit();
	//gprsinit();
	
	//! [main_loop]
	while (true) {
		
		delay_ms(200);
		if (sendATcommand("AT+SAPBR=2,1\r\n", "SAPBR: 1,1,", 1000) == 1)
		{
			send_http(temperature, humidity, wind);
		}
		else
		{
			gprsinit();
		}
		rand_genarator();
		delay_s(300);
		
		
	}

}
void rand_genarator(){
	temperature = rand() % 50;
	humidity	= rand() % 50;
	wind		= rand() % 50;
	
}

#ifdef __cplusplus
}
#endif
