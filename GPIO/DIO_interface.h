/*
 * DIO_interface.h
 *
 *  Created on: Sep 7, 2024
 *      Author: omarf
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H


// Set the direction of a pin(port, pin_index, direction [input or output])
void DIO_voidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction);

// Set the value of a pin(port, pin_index, value [high or low])
void DIO_voidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value);


// Get the value of a pin (port, pin_index)
u8 DIO_u8GetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin);


// Set the direction of a port (port, [input or output], decimal value which pins)
void DIO_voidSetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction);

// Set the value of a port (port, [high or low], decimal value which pins)
void DIO_voidSetPortValue(u8 Copy_u8Port ,u8 Copy_u8Value);

// Get the port value (port)
u8 DIO_u8GetPortValue(u8 Copy_u8Port);

// NO MAGIC NUMBERS IN CODE

#define DIO_u8INPUT 			0
#define DIO_u8OUTPUT 			1

#define DIO_u8PORTINPUT         0
#define DIO_u8PORTOUTPUT        0xFF

#define DIO_u8PORTA             0
#define DIO_u8PORTB             1
#define DIO_u8PORTC             2
#define DIO_u8PORTD             3

#define DIO_u8HIGH              1
#define DIO_u8LOW               0

#define DIO_u8PIN0              0
#define DIO_u8PIN1              1
#define DIO_u8PIN2              2
#define DIO_u8PIN3              3
#define DIO_u8PIN4              4
#define DIO_u8PIN5              5
#define DIO_u8PIN6              6
#define DIO_u8PIN7              7



#endif /* DIO_INTERFACE_H_ */
