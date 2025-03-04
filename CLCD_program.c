/*
 * CLCD_program.c
 *
 *  Created on: Sep 14, 2024
 *      Author: omarf
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"


#include "DIO_interface.h"
#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"


/*
			Function to send data to LCD
*/

void CLCD_voidSendData(u8 Copy_u8Data) {
	// make rs = 1         Data    not command
	DIO_voidSetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8HIGH);

	// make rw = 0         write   not read
	DIO_voidSetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_u8LOW);

	// Send the data
	DIO_voidSetPortValue(CLCD_DATA_PORT, Copy_u8Data);

	// Enable              enables writing
	DIO_voidSetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8HIGH);

	_delay_ms(5);
	// Disable             disables writing
	DIO_voidSetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8LOW);

}

/*
 	 	 End of send data function
 */



/*
 	 Function to send command to LCD
 */

void CLCD_voidSendCommand(u8 Copy_u8Command) {
	// make rs = 0         Command not Data
	DIO_voidSetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8LOW);
	// make rw = 0         write not read
	DIO_voidSetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_u8LOW);

	// Put data (The command)
	DIO_voidSetPortValue(CLCD_DATA_PORT, Copy_u8Command);

	// Enable			   Enables writing
	DIO_voidSetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8HIGH);

	_delay_ms(5);
	// Disable             Disables writing
	DIO_voidSetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8LOW);
}

/*
 	  End of Function to send command to LCD
 */





/*
  	  	 Function to initialize the LCD
 */

void CLCD_voidInit(void) {
	// Wait for more than 30 ms
	_delay_ms(50);
	// Function Set
	CLCD_voidSendCommand(0b00111000);

	// Display ON/OFF
	CLCD_voidSendCommand(0b00001111);
	// Display Clear
	CLCD_voidSendCommand(0b00000001);
}

/*
  	  	 End of Function to initialize the LCD
 */




/*
 	 	Function to send string
 */
void CLCD_voidSendString(const char * Copy_pString) {

    u8 Local_u8Counter = 0;

    while( (Copy_pString[Local_u8Counter]) != '\0') {  // Correct null terminator check
        CLCD_voidSendData(Copy_pString[Local_u8Counter]);
        Local_u8Counter++;
    }
}
/*
 	 	End of  function to send string
 */




/*
 	 	Function to send integer
 */

void CLCD_voidSendInteger(u32 Copy_u32Integer) {

	u8 Local_Number[10]; // 10 digits is the max of u32
	u8 i = 0;           // counter

	while (Copy_u32Integer >= 10) {
		Local_Number[i] = (Copy_u32Integer  %  10) + ZERO_ASCII;
		Copy_u32Integer = Copy_u32Integer / 10;
		i++;
	}
	Local_Number[i] = Copy_u32Integer + ZERO_ASCII;

	for (s8 j = i; j >= 0 ; j--) {
		CLCD_voidSendData(Local_Number[j]);
	}

}
/*
 	 	End of Function to send integer
 */





/*
 	 Function to set X, Y positions
 */
void CLCD_voidSetXYPosition(u8 Copy_u8XPosition, u8 Copy_u8YPosition) {
	u8 Local_u8Address;

	if (Copy_u8YPosition == 0) {
		Local_u8Address = Copy_u8XPosition;
	}

	else if (Copy_u8YPosition == 1) {
		Local_u8Address = Copy_u8XPosition + 0x40;
	}

	SET_BIT(Local_u8Address, 7);

	CLCD_voidSendCommand(Local_u8Address);

}
/*
 	 End of Function to set X, Y positions
 */



void CLCD_voidCreateCustomChar(u8 Copy_u8Location, u8 *Copy_u8Pattern) {
    // Ensure the location is within 0-7 range
    Copy_u8Location = Copy_u8Location & 0x07; // Only 8 locations (0-7)

    // Set CGRAM address, command is 0x40 + (location * 8)
    CLCD_voidSendCommand(0x40 | (Copy_u8Location << 3));

    // Send 8 bytes for the custom character
    for (u8 i = 0; i < 8; i++) {
        CLCD_voidSendData(Copy_u8Pattern[i]);
    }
}


void CLCD_voidDisplaySinName(void) {
    u8 x = 0;
    u8 y = 0;
    u8 direction_flag = 0;
    u8 vertical_flag = 0;

    while (1) {
        _delay_ms(800);
        CLCD_voidClear();
        CLCD_voidSetXYPosition(x, y);
        CLCD_voidSendString("Omar");

        // Moving to The right
        if (direction_flag == 0) {
            if (x < (16 - 4) ) {
            	if (vertical_flag == 0) {
            		y = 1;
            		x += 3;
            		vertical_flag++;
            	}
            	else {
            		y = 0;
            		x+=3;
            		vertical_flag--;

            	}
            }

            else {
                direction_flag = 1;
            }
        }

        // Moving to the left

        else { // directional_flag = 1
            if (x > 0) {
            	if (vertical_flag == 0) {
            		y = 1;
            		x -= 3;
            		vertical_flag++;
            	}
            	else {
            		y = 0;
            		x-=3;
            		vertical_flag--;

            	}
            }

            else {  // Reached the start, move forward again
                direction_flag = 0;

            }
        }
    }
}



void CLCD_voidClear(void) {
	CLCD_voidSendCommand(0b00000001);
}






