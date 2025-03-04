/*
 * TWI_program.c
 *
 *  Created on: Nov 17, 2024
 *      Author: omarf
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TWI_config.h"
#include "TWI_interface.h"
#include "TWI_private.h"
#include "TWI_register.h"





/*
 * Description : Function to initialize the TWI driver
 * 	1. Set the required address.
 * 	2. Set the required Prescaler.
 * 	3. Set the required Prescaler bit_rate.
 */

void TWI_voidMasterInit(void) {
	/*MASTER ADDRESS  WHEN IT RECIEVES*/
	if (MASTER_ADDRESS == NO_ADDRESS) {
		asm("NOP");
	}
	else {

		TWAR = MASTER_ADDRESS << 1;
	}
	// CLK Calculation 400kbps
	CLR_BIT(TWSR, 1);
	CLR_BIT(TWSR, 0);
	TWBR = 2;
}

void TWI_voidSlaveInit(void) {
	/* First Bit is used for something else*/
	TWAR = SLAVE_ADDRESS << 1;
}





/*
 * Description : Function to send start  to the frame.
 */
void TWI_voidSendStartCondition(void) {
	/************************** TWCR Description **************************
	 * TWIE   = 0 Disable TWI Interrupt
	 * TWEN   = 1 Enable TWI Module
	 * TWSTO  = 0 We don't need to generate stop condition in generate start condition mode
	 * TWSTA  = 1 generating start condition
	 * TWEA   = 0 We don't need to generate acknowledge pulse in generate start condition mode
	 * TWINT  = 1 Clear the TWINT flag before reading the data
	 ***********************************************************************/
	 TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

	 /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	 while (!(TWCR & (1<<TWINT))) {
		 asm("NOP");
	 }
}





/*
 * Description : Function to send repeated  start
 */
void TWI_voidSendRepeatedStart(void) {
	/************************** TWCR Description **************************
	 * TWIE   = 0 Disable TWI Interrupt
	 * TWEN   = 1 Enable TWI Module
	 * TWSTO  = 0 We don't need to generate stop condition in generate start condition mode
	 * TWSTA  = 1 generating start condition
	 * TWEA   = 0 We don't need to generate acknowledge pulse in generate start condition mode
	 * TWINT  = 1 Clear the TWINT flag before reading the data
	 ***********************************************************************/
	 TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

	 /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	 while (!(TWCR & (1<<TWINT))) {
		 asm("NOP");
	 }
}







void TWI_voidSendSlaveAddressWithWrite(u8 Copy_u8Address) {

	 TWDR = Copy_u8Address << 1;

	 // Write
	 CLR_BIT(TWDR, 0);
	/************************** TWCR Description **************************
	* TWIE   = 0 Disable TWI Interrupt
    * TWEN   = 1 Enable TWI Module
	* TWSTO  = 1 generating stop condition
    * TWSTA  = 0 We don't need to generate start condition in generate stop condition mode
	* TWEA   = 0 We don't need to generate acknowledge pulse in generate stop condition mode
	* TWINT  = 1 Clear the TWINT flag before reading the data
	***********************************************************************/
	 TWCR = (1<<TWINT) | (1<<TWEN);

	 /*Wait for the TWI to complete the transmission of the slave address with the write bit (TWINT flag set)*/
	while (!(TWCR & (1<<TWINT))) {
			 asm("NOP");
	}
}






void TWI_voidSendSlaveAddressWithRead(u8 Copy_u8Address) {
	 TWDR = Copy_u8Address << 1;

	 // READ
	 SET_BIT(TWDR, 0);
		/************************** TWCR Description **************************
		 * TWIE   = 0 Disable TWI Interrupt
		 * TWEN   = 1 Enable TWI Module
		 * TWSTO  = 1 generating stop condition
		 * TWSTA  = 0 We don't need to generate start condition in generate stop condition mode
		 * TWEA   = 0 We don't need to generate acknowledge pulse in generate stop condition mode
		 * TWINT  = 1 Clear the TWINT flag before reading the data
		 ***********************************************************************/
	 TWCR = (1<<TWINT) | (1<<TWEN);



	/*Wait for the TWI to complete the transmission of the slave address with the read bit (TWINT flag set)*/
	while (!(TWCR & (1<<TWINT))) {
			 asm("NOP");
	}
}






/*
 * Description : Function to write a data on TWI data Register and send it.
 */
void TWI_voidMasterSendDatawithAck(u8 Copy_u8Data) {
	/* Put the Data in TWI data register*/
	 TWDR = Copy_u8Data;

	 /************************** TWCR Description **************************
	 * TWIE   = 0 Disable TWI Interrupt
	 * TWEN   = 1 Enable TWI Circuit
	 * TWSTO  = 0 We don't need to generate stop condition in send data mode
     * TWSTA  = 0 We don't need to generate start condition in send data mode
     * TWEA   = 1 We generate acknowledge pulse in send data mode
	 * TWINT  = 1 Clear the TWINT flag before reading the data as we must clear it Software
	 ***********************************************************************/
	 TWCR = (1<<TWINT) | (1<<TWEN) | (1 << TWEA);

	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while (!(TWCR & (1<<TWINT))) {
			asm("NOP");
	}
}






/*
 * Description : Function to write a data on TWI data Register and send it.
 */
void TWI_voidMasterSendDatawithoutAck(u8 Copy_u8Data) {
	/* Put the Data in TWI data register*/
	 TWDR = Copy_u8Data;

	 /************************** TWCR Description **************************
	 * TWIE   = 0 Disable TWI Interrupt
	 * TWEN   = 1 Enable TWI Circuit
	 * TWSTO  = 0 We don't need to generate stop condition in send data mode
     * TWSTA  = 0 We don't need to generate start condition in send data mode
     * TWEA   =  0 We don't generate acknowledge pulse in send data mode
	 * TWINT  = 1 Clear the TWINT flag before reading the data as we must clear it Software
	 ***********************************************************************/
	 TWCR = (1<<TWINT) | (1<<TWEN);

	 /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
		while (!(TWCR & (1<<TWINT))) {
				 asm("NOP");
		}
}







/*
 * Description : Function to read a data and send ACK after reading.
 */
u8 TWI_voidMasterReceivewithAck(void) {
	/************************** TWCR Description **************************
	 * TWIE   = 0 Disable TWI Interrupt
	 * TWEN   = 1 Enable TWI Module
	 * TWSTO  = 0 We don't need to generate stop condition in receive mode
	 * TWSTA  = 0 We don't need to generate start condition in receive mode
	 * TWEA   = 1 generating acknowledge pulse
	 * TWINT  = 1 Clear the TWINT flag before reading the data
	 ***********************************************************************/
	TWCR = (1<<TWINT) | (1<<TWEN) | (1 << TWEA);

	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while (!(TWCR & (1<<TWINT))) {
			 asm("NOP");
	}

	/* Read Data */
	return TWDR;
}








/*
 * Description : Function to read a data and send NACK after reading.
 */
u8 TWI_voidMasterReceivewithoutAck(void) {
	/************************** TWCR Description **************************
	 * TWIE   = 0 Disable TWI Interrupt
	 * TWEN   = 1 Enable TWI Module
	 * TWSTO  = 0 We don't need to generate stop condition in receive mode
	 * TWSTA  = 0 We don't need to generate start condition in receive mode
	 * TWEA   = 0 We don't need to generate acknowledge pulse as we are in receive mode with NACK
	 * TWINT  = 1 Clear the TWINT flag before reading the data
	 ***********************************************************************/
	TWCR = (1<<TWINT) | (1<<TWEN);

	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while (!(TWCR & (1<<TWINT))) {
			 asm("NOP");
	}

	/* Read Data */
	return TWDR;
}






/*
 * Description : Function to send stop bit to the frame.
 */
void TWI_voidSendStopCondition(void) {
	/************************** TWCR Description **************************
	 * TWIE   = 0 Disable TWI Interrupt
	 * TWEN   = 1 Enable TWI Module
	 * TWSTO  = 1 generating stop condition
	 * TWSTA  = 0 We don't need to generate start condition in generate stop condition mode
	 * TWEA   = 0 We don't need to generate acknowledge pulse in generate stop condition mode
	 * TWINT  = 1 Clear the TWINT flag before reading the data
	 ***********************************************************************/
	TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);
}

