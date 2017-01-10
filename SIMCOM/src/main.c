
#include <stdlib.h>
#include "asf.h"
#include "sim_usart.h"
#include "AtCmdWrapper.h"

void rand_genarator();
float ic_temp=1.1, battery_volt = 0.3, pt1000_temp = 0.0, ds18b20_temp = 0.0, mpx_pressure = 0.0, bme280_temp = 0.0, bme280_pressure = 0.0, bme280_humidity = 0.0;
int soil_moisture_01 = 0, soil_moisture_02 = 0;

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
		
		rand_genarator();
		delay_ms(200);
		if (sendATcommand("AT+SAPBR=2,1\r\n", "SAPBR: 1,1,", 1000) == 1)
		{
			send_http(battery_volt, pt1000_temp, ds18b20_temp, mpx_pressure, soil_moisture_01, soil_moisture_02, bme280_temp, bme280_pressure, bme280_humidity);
		}
		else
		{
			gprsinit();
		}
		delay_s(300);
		
		
	}

}
void rand_genarator(){
	battery_volt =((float)rand()/(float)(RAND_MAX)) * 5.0;										//rand() % 50;
	pt1000_temp = ((float)rand()/(float)(RAND_MAX)) * 50.0;
	ds18b20_temp = ((float)rand()/(float)(RAND_MAX)) * 50.0;
	mpx_pressure = ((float)rand()/(float)(RAND_MAX)) * 40.0;
	soil_moisture_01 = rand() % 50;
	soil_moisture_02 = rand() % 50; 
	bme280_temp = ((float)rand()/(float)(RAND_MAX)) * 50.0;
	bme280_pressure = ((float)rand()/(float)(RAND_MAX)) * 45.0;
	bme280_humidity = ((float)rand()/(float)(RAND_MAX)) * 50.0;
}

#ifdef __cplusplus
}
#endif
