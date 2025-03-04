/*
 * TWI_register.h
 *
 *  Created on: Nov 17, 2024
 *      Author: omarf
 */

#ifndef TWI_REGISTER_H_
#define TWI_REGISTER_H_

#define TWBR		*((volatile u8*)(0x20))
#define TWCR		*((volatile u8*)(0x56))
#define TWINT		7
#define TWSTA 		5
#define TWEN 		2
#define TWEA		6
#define TWSTO 		4
#define TWSR		*((volatile u8*)(0x21))
#define TWDR		*((volatile u8*)(0x23))
#define TWAR		*((volatile u8*)(0x22))




#endif /* TWI_REGISTER_H_ */
