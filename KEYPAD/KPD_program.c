/*
 * KPD_program.c


 *
 *  Created on: Sep 20, 2024
 *      Author: omarf
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "util/delay.h"

#include "KPD_config.h"
#include "KPD_interface.h"
#include "KPD_private.h"
#include "CLCD_interface.h"

#define MAX_DIGITS 10  // Maximum number of digits for input

u8 DigitBuffer[MAX_DIGITS] = {0};  // Buffer to store digits
u8 DigitIndex = 0;  // Index for storing digits
u8 StoredValue = 0;  // Variable to store the number when magic key is pressed





void KPD_voidInit(void) {
	DIO_voidSetPortDirection(KPD_PORT, 0x0F); //   0000(inputs)  1111 (outputs)

	DIO_voidSetPortValue(KPD_PORT, 0xFF);     //   1111(pull up resistance)              1111 (High at the beginning)

}




u8 KPD_u8GetPressedKey(void)
{
    u8 Local_u8PressedKey = NOT_PRESSED;

    u8 Local_KeyArr[4][4] = {
        { 7, 8, 9,  84},
        { 4, 5, 6, 81 },
        { 1, 2, 3, 82 },
        { 13, 0, 80, 83 }
    };

    for (u8 col = 0; col < 4; col++)
    {
        DIO_voidSetPinValue(KPD_PORT, col, DIO_u8LOW);

        for (u8 row = 0; row < 4; row++)
        {
            if ((DIO_u8GetPinValue(KPD_PORT, row + 4)) == 0)
            {
                Local_u8PressedKey = Local_KeyArr[row][col];
                _delay_ms(2);  // Debounce delay

                while ((DIO_u8GetPinValue(KPD_PORT, row + 4)) == 0)
                {
                    asm("NOP");  // Wait for the key to be released
                }
            }
        }

        DIO_voidSetPinValue(KPD_PORT, col, DIO_u8HIGH);  // Reset the column pin
    }

    return Local_u8PressedKey;
}

/**
 * @brief Captures and processes keypad input, handles display, and stores the value on magic key press.
 * @param magicKey The special key (magic number) that triggers storing the current value.
 * @return The stored value when the magic key is pressed.
 */
u8 KPD_u8ProcessInput(u8 magicKey) {
	while(1) {


    u8 Local_u8Key = KPD_u8GetPressedKey();
    static u8 CurrentValue = 0;  // Static to retain the value between function calls

    if (Local_u8Key != NOT_PRESSED) {
        // If the key pressed is not the magic number
        if (Local_u8Key != magicKey) {
            // Add the pressed key to the digit buffer
            if (DigitIndex < MAX_DIGITS) {
                DigitBuffer[DigitIndex++] = Local_u8Key;
                CurrentValue = 0;

                // Rebuild the current value from the buffer
                for (u8 i = 0; i < DigitIndex; i++) {
                    CurrentValue = CurrentValue * 10 + DigitBuffer[i];
                }
                CLCD_voidClear();  // Clear the display before showing the updated value
                CLCD_voidSendInteger(CurrentValue);  // Display the updated value
            }
        } else {
            // When magic number is pressed, store the current value
            StoredValue = CurrentValue;
            CLCD_voidSendString(" Stored!");
            _delay_ms(1000);  // Delay to show the message briefly
            CLCD_voidClear();  // Clear the screen
            DigitIndex = 0;  // Reset the buffer
            CurrentValue = 0;  // Reset the current value
            break;

        }
    }
	}

    return StoredValue;


}










