/*
 * CLCD_config.h
 *
 *  Created on: Sep 14, 2024
 *      Author: omarf
 */

#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_


/*
 	 Options:
 	 1: DIO_u8PORTA
 	 2: DIO_u8PORTB
 	 3: DIO_u8PORTC
 	 4: DIO_u8PORTD
 */

#define CLCD_DATA_PORT       DIO_u8PORTA

/*

 */

#define CLCD_CTRL_PORT  	 DIO_u8PORTD


























#define CLCD_RS_PIN 		 DIO_u8PIN0
#define CLCD_RW_PIN 		 DIO_u8PIN1
#define CLCD_E_PIN 		 	 DIO_u8PIN2


#endif /* CLCD_CONFIG_H_ */
