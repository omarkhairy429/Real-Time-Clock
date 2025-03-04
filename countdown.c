/*
 * countdown.c
 *
 *  Created on: Dec 5, 2024
 *      Author: Ahmed
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "rtc_interface.h"
#include "TWI_interface.h"
#include "CLCD_interface.h"
#include "util/delay.h"

// Global Variables for Countdown Time
u8 countdown_hours = 0;
u8 countdown_minutes = 0;
u8 countdown_seconds = 0;

// Update LCD Display
void update_display(u8 hours, u8 minutes, u8 seconds) {
   // CLCD_voidSetXYPosition(0, 0); // Set cursor to position 0, 0

    // Display hours with leading zero if needed
    if (hours < 10) {
        CLCD_voidSendData('0');
    }
    CLCD_voidSendInteger(hours);
    CLCD_voidSendData(':');

    // Display minutes with leading zero if needed
    if (minutes < 10) {
        CLCD_voidSendData('0');
    }
    CLCD_voidSendInteger(minutes);
    CLCD_voidSendData(':');

    // Display seconds with leading zero if needed
    if (seconds < 10) {
        CLCD_voidSendData('0');
    }
    CLCD_voidSendInteger(seconds);
}


// Countdown Initialization
void countdown_init() {
    // Configure Port A for LCD and Port D for Buttons
   // DIO_voidSetPortDirection(DIO_u8PORTA, DIO_u8OUTPUT);
    DIO_voidSetPortDirection(DIO_u8PORTD, 0b10000111); // Pins 0-2 outputs, others inputs

    // Configure Buttons (Stop, Start, Reset)
    DIO_voidSetPinDirection(DIO_u8PORTD, DIO_u8PIN3, DIO_u8INPUT); // Stop
    DIO_voidSetPinDirection(DIO_u8PORTD, DIO_u8PIN4, DIO_u8INPUT); // Start
    DIO_voidSetPinDirection(DIO_u8PORTD, DIO_u8PIN5, DIO_u8INPUT); // Reset

    // Enable Pull-up Resistors
    DIO_voidSetPinValue(DIO_u8PORTD, DIO_u8PIN3, DIO_u8HIGH);
    DIO_voidSetPinValue(DIO_u8PORTD, DIO_u8PIN4, DIO_u8HIGH);
    DIO_voidSetPinValue(DIO_u8PORTD, DIO_u8PIN5, DIO_u8HIGH);

    // Initialize TWI and LCD
    TWI_voidMasterInit();
    CLCD_voidInit();

    // Initial Display Message
    CLCD_voidSendString("Countdown Timer");
    _delay_ms(2000);
    CLCD_voidClear();
}

// Countdown Logic
void countdown(u8 initial_hours, u8 initial_minutes, u8 initial_seconds) {
    countdown_hours = initial_hours;
    countdown_minutes = initial_minutes;
    countdown_seconds = initial_seconds;

    update_display(countdown_hours, countdown_minutes, countdown_seconds);

    u8 countdown_running = 0; // Flag to track countdown state
    while (1) {
        // Button Handling
        if (DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN4) == 0) { // Start Button (PIN4)
            _delay_ms(16); // Debounce
            if (DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN4) == 0) {
                countdown_running = 1;
                _delay_ms(300); // Prevent multiple toggles
            }
        }

        if (DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN3) == 0) { // Stop Button (PIN3)
            _delay_ms(16); // Debounce
            if (DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN3) == 0) {
                countdown_running = 0;
                _delay_ms(300); // Prevent multiple toggles
            }
        }

        if (DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN5) == 0) { // Reset Button (PIN5)
            _delay_ms(16); // Debounce
            if (DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN5) == 0) {

                countdown_running = 0;
                countdown_hours = initial_hours;
                countdown_minutes = initial_minutes;
                countdown_seconds = initial_seconds;
                DIO_voidSetPinValue(DIO_u8PORTD, DIO_u8PIN7, 0); // Reset Alert
                CLCD_voidClear();
                update_display(countdown_hours, countdown_minutes, countdown_seconds);
                _delay_ms(300); // Prevent multiple toggles
            }
        }

        // Countdown Logic
        if (countdown_running) {
            if (countdown_seconds == 0) {
                if (countdown_minutes == 0) {
                    if (countdown_hours == 0) {
                        countdown_running = 0; // Stop countdown
                   //     DIO_voidSetPinValue(DIO_u8PORTD, DIO_u8PIN7, 1); // Trigger Alert
                        DIO_voidSetPinValue(DIO_u8PORTC, DIO_u8PIN3, DIO_u8HIGH);
                    	while (1) {
                        		DIO_voidSetPinValue(DIO_u8PORTC, DIO_u8PIN2, DIO_u8HIGH);
                        		_delay_ms(1);
                        		DIO_voidSetPinValue(DIO_u8PORTC, DIO_u8PIN2, DIO_u8LOW);
                        		_delay_ms(1);

                        		if (DIO_u8GetPinValue(DIO_u8PORTC, DIO_u8PIN3) == DIO_u8LOW) {
                        				break;
                        		}
                        	}
                    } else {
                        countdown_hours--;
                        countdown_minutes = 59;
                        countdown_seconds = 59;
                    }
                } else {
                    countdown_minutes--;
                    countdown_seconds = 59;
                }
            } else {
                countdown_seconds--;
            }

            // Update LCD Display
            CLCD_voidClear();
            update_display(countdown_hours, countdown_minutes, countdown_seconds);
            _delay_ms(1000); // Wait 1 second
        }

        if(KPD_u8GetPressedKey()==13){
        	   START_UP_MODE();

        }
    }
}
