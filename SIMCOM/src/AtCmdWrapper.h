/*
 * AtCmdWrapper.h
 *
 * Created: 26-12-2016 07:38:18 PM
 *  Author: K8
 */ 
 #include <compiler.h>
 #include <status_codes.h>
 #include "sim_usart.h"

#ifndef ATCMDWRAPPER_H_
#define ATCMDWRAPPER_H_

#define FONA_DEFAULT_TIMEOUT_MS 1000



//function prototypes
void power_on();
int8_t gsminit();
int8_t gprsinit();
int8_t send_http(int temperature, int humidity, int wind);
uint16_t readline(uint16_t timeout, uint8_t multiline);
int8_t sendATcommand(const uint8_t* ATcommand, const uint8_t* expected_answer1, unsigned int timeout);
int8_t sendATcommand2(const uint8_t* ATcommand, const uint8_t* expected_answer1, const uint8_t* expected_answer2, unsigned int timeout);




#endif /* ATCMDWRAPPER_H_ */