/*
 * usart_config.h
 *
 * Created: 28-12-2016 11:48:31
 *  Author: K8
 */ 


#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

 #include "asf.h"

#define STRING_EOL    "\r"
#define STRING_HEADER "-- Getting Started Example --\r"

struct usart_module usart_instance_one;
struct usart_module usart_instance_two;

void sim_usart_init(void);

#endif /* USART_CONFIG_H_ */