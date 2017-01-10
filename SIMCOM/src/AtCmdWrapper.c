/*
 * AtCmdWrapper.c
 *
 * Created: 26-12-2016 07:39:14 PM
 *  Author: K8
 */ 
 #include "AtCmdWrapper.h"
 #include "delay.h"
 #include <string.h>
 uint8_t replybuffer[255];
 char aux_str[350];
 char aux;

 char apn[]="airtelgprs.com";

 
 //uint16_t timeout = FONA_DEFAULT_TIMEOUT_MS;
 
 int8_t send_http(float battery_volt, float pt1000_temp, float ds18b20_temp, float mpx_pressure, int soil_moisture_01, int soil_moisture_02, float bme280_temp, float bme280_pressure, float bme280_humidity){
	uint8_t answer=0;

	// Sets CID parameter
		answer = sendATcommand("AT+HTTPPARA=\"CID\",1\r\n", "OK", 5000);
		if (answer == 1)
		{
			// Sets url
			
			snprintf(aux_str, sizeof(aux_str), "AT+HTTPPARA=\"URL\",\"io.adafruit.com/api/groups/atmelr21_sensors/send.json?x-aio-key=b34fcc99b8dc433a90de7cd175e4514d&battery_volt=%.2f&pt1000_temp=%.2f&ds18b20_temp=%.2f&mpx_pressure=%.2f&soil_moisture_01=%d&soil_moisture_02=%d&bme280_temp=%.2f&bme280_pressure=%.2f&bme280_humidity=%.2f\"\r\n", battery_volt, pt1000_temp, ds18b20_temp, mpx_pressure, soil_moisture_01, soil_moisture_02, bme280_temp, bme280_pressure,bme280_humidity);
			answer = sendATcommand(aux_str, "OK", 5000);
			if (answer == 1)
			{
				// Starts GET action
				answer = sendATcommand("AT+HTTPACTION=0\r\n", "+HTTPACTION:", 10000);
				
				if (answer == 1)
				{
						sprintf(aux_str, "AT+HTTPREAD=0,400\r\n");
						if (sendATcommand2(aux_str, "+HTTPREAD:", "ERROR", 30000) == 1)
						{
							readline(3000, 1);
						}
						else if (answer == 2)
						{
							printf("Error from HTTP\n");
						}					
				}
				else
				{
					printf("Error getting the url\n");
				}
			}
			else
			{
				printf("Error setting the url\n");
			}
		}
		else
		{
			printf("Error setting the CID\n");
		}
	
	//sendATcommand("AT+HTTPTERM", "OK", 5000);

	delay_ms(5000);
 }
 int8_t gsminit(){
	printf("starting....\r\n");	
	power_on();
	uint8_t string[] = "ATE0\r\n";
	sendATcommand("ATE0\r\n", "OK", 1000);

 }
 int8_t gprsinit(){

	 while (sendATcommand("AT+CREG?\r\n", "+CREG: 0,1", 2000) == 0);
	 // sets APN 
	 sendATcommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r\n", "OK", 2000);
	 snprintf(aux_str, sizeof(aux_str), "AT+SAPBR=3,1,\"APN\",\"%s\"\r\n", apn);
	 sendATcommand(aux_str, "OK", 2000);
	 if (sendATcommand("AT+SAPBR=2,1\r\n", "SAPBR: 1,1,", 1000) == 1)
	 {
		 return;
	 }
	 else
	 {
		while (sendATcommand("AT+SAPBR=1,1\r\n", "OK", 20000) == 0)
		{
			delay_ms(5000);
		}
		// Initializes HTTP service
		while (sendATcommand("AT+HTTPINIT\r\n", "OK", 10000) == 0);
	 }

 }
 void power_on(){
	    uint8_t answer=0;

	    // checks if the module is started
	    answer = sendATcommand("AT\r\n", "OK", 3000);
	    if (answer == 0)
	    {
		    // waits for an answer from the module
		    while(answer == 0){
			    // Send AT every two seconds and wait for the answer
			    answer = sendATcommand("AT\r\n", "OK", 2000);
		    }
	    }
		puts("module is on\r\n");
 }
 int8_t sendATcommand(const uint8_t* ATcommand, const uint8_t* expected_answer1, unsigned int timeout){
	
	uint8_t x=0,  answer=0;
	char response[100];

	memset(response, '\0', 100);    // Initialize the string
	while (*ATcommand != '\0')
	{
		usart_write_wait(&usart_instance_one, *ATcommand);    // Send the AT command
		ATcommand++;

	}

	//delay_ms(100);


	x = 0;
	uint16_t temp;

	// this loop waits for the answer
	do{
		if ((timeout--) != 0)
		{
			if(usart_read_wait(&usart_instance_one, &temp) == 0){
				response[x] = temp;
				//printf("%c",response[x]);
				x++;
				// check if the desired answer is in the response of the module
				if (strstr(response, expected_answer1) != NULL)
				{
					//printf("\n");
					answer = 1;
				}
			}
		}
		else{ break;}
		delay_ms(1);
		// Waits for the answer with time out
	}
	while((answer == 0));

	return answer;

 }

 int8_t sendATcommand2(const uint8_t* ATcommand, const uint8_t* expected_answer1, const uint8_t* expected_answer2, unsigned int timeout){
	
	uint8_t x=0,  answer=0;
	char response[100];

	memset(response, '\0', 100);    // Initialize the string
	while (*ATcommand != '\0')
	{
		usart_write_wait(&usart_instance_one, *ATcommand);    // Send the AT command
		ATcommand++;

	}

	//delay_ms(100);


	x = 0;
	uint16_t temp;

	// this loop waits for the answer
	do{
		if ((timeout--) != 0)
		{
			if(usart_read_wait(&usart_instance_one, &temp) == 0){
				response[x] = temp;
				//printf("%c",response[x]);
				x++;
				// check if the desired answer is in the response of the module
				if (strstr(response, expected_answer1) != NULL)
				{
					//printf("\n");
					answer = 1;
				}
				// check if the desired answer 2 is in the response of the module
				if (strstr(response, expected_answer2) != NULL)
				{
					//printf("\n");
					answer = 2;
				}
			}
		}
		else{ break;}
		delay_ms(1);
		// Waits for the answer with time out
	}
	while((answer == 0));

	return answer;
 }
 uint16_t readline(uint16_t timeout, uint8_t multiline) 
  {
	 uint16_t temp;
	 uint16_t replyidx = 0;

	 while (timeout--) {
		 if (replyidx >= 254) {
			 //DEBUG_PRINTLN(F("SPACE"));
			 break;
		 }
		 while (usart_read_wait(&usart_instance_one, &temp) == 0)
		 {
			 if (temp == '\r')
			 { 
				  continue;
			 }
			 if (temp == 0xA)
			 {
				 if(replyidx == 0)
				 {
					  continue;
				 }
				 if (!multiline)
				 {
					 timeout = 0;
					 break;
				 }
			 }
			 replybuffer[replyidx] = temp;
			 //while (usart_write_wait(&usart_instance_two, temp) != STATUS_OK) {}
			 replyidx++;
		 }
		 
		 if (timeout == 0) {
			 //DEBUG_PRINTLN(F("TIMEOUT"));
			 break;
		 }
		 delay_ms(1);
	 }
	 replybuffer[replyidx] = 0;  // null term
	 puts(replybuffer);
	 return replyidx;
 }
 
 