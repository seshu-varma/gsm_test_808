/*
 * usart_config.c
 *
 * Created: 28-12-2016 11:50:18
 *  Author: K8
 */ 
 #include "sim_usart.h"


 /* Configure UART console.*/
 static void configure_usart_one(void)
 {
	 struct usart_config usart_conf;

	 usart_get_config_defaults(&usart_conf);
	 usart_conf.mux_setting = EXT1_UART_SERCOM_MUX_SETTING;
	 usart_conf.pinmux_pad0 = EXT1_UART_SERCOM_PINMUX_PAD0;
	 usart_conf.pinmux_pad1 = EXT1_UART_SERCOM_PINMUX_PAD1;
	 usart_conf.pinmux_pad2 = EXT1_UART_SERCOM_PINMUX_PAD2;
	 usart_conf.pinmux_pad3 = EXT1_UART_SERCOM_PINMUX_PAD3;
	 usart_conf.baudrate    = 9600;

	 while(usart_init(&usart_instance_one, EXT1_UART_MODULE, &usart_conf)){}
	 usart_enable(&usart_instance_one);
 }
 static void configure_usart_two(void)
 {
	 struct usart_config usart_conf;

	 usart_get_config_defaults(&usart_conf);
	 usart_conf.mux_setting = USART_RX_1_TX_0_XCK_1;
	 usart_conf.pinmux_pad0 = PINMUX_PA22D_SERCOM5_PAD0;
	 usart_conf.pinmux_pad1 = PINMUX_PA23D_SERCOM5_PAD1;
	 usart_conf.pinmux_pad2 = PINMUX_UNUSED;
	 usart_conf.pinmux_pad3 = PINMUX_UNUSED;
	 usart_conf.baudrate    = 9600;

	 //while(usart_init(&usart_instance_two, SERCOM5, &usart_conf)){}
	 stdio_serial_init(&usart_instance_two, SERCOM5, &usart_conf);
	 usart_enable(&usart_instance_two);
 }

  void sim_usart_init(void){

	configure_usart_one();
	configure_usart_two();

  }

 /* end of usart configuration. */

