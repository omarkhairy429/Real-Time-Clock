/*
 * CLCD_interface.h
 *
 *  Created on: Sep 14, 2024
 *      Author: omarf
 */

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_



void CLCD_voidSendData(u8 Copy_u8Data);

void CLCD_voidSendCommand(u8 Copy_u8Command);


// Initializing the LCD
void CLCD_voidInit(void);

// Sending String to LCD
void CLCD_voidSendString(const char * Copy_pString);


// Sending number
void CLCD_voidSendInteger(u32 Copy_u32Integer);


// Position

void CLCD_voidSetXYPosition(u8 Copy_u8XPosition, u8 Copy_u8YPosition);


void CLCD_voidCreateCustomChar(u8 Copy_u8Location, u8 *Copy_u8Pattern);

void CLCD_voidDisplaySinName(void);

void CLCD_voidClear(void);



#endif /* CLCD_INTERFACE_H_ */
