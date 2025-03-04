/*
 * stopwatch.c
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



void stopwatch(){
	 // Configure Port A for output (for controlling the LCD)
	         // Flag to track stopwatch running state
	 u8 sec = 0, min = 0, hour = 0; // Stopwatch time
			        u8 stopwatch_running = 0;
	        while (1) {
	            // Check the state of the start button (PIN4)
	            if (DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN4) == 0) { // Button pressed
	                _delay_ms(16); // Debounce delay
	                if (DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN4) == 0) { // Confirm press
	                    stopwatch_running = 1; // Start stopwatch
	                    _delay_ms(300); // Prevent multiple toggles
	                }
	            }

	            // Check the state of the stop button (PIN3)
	            if (DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN3) == 0) { // Button pressed
	                _delay_ms(16); // Debounce delay
	                if (DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN3) == 0) { // Confirm press
	                    stopwatch_running = 0; // Stop stopwatch
	                    _delay_ms(300); // Prevent multiple toggles
	                }
	            }
	            if (DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN5) == 0) { // Button pressed
	                        _delay_ms(16); // Debounce delay
	                        if (DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN5) == 0) { // Confirm press
	                            stopwatch_running = 0; // Stop stopwatch
	                            sec = 0, min = 0, hour = 0;
	                            _delay_ms(300); // Prevent multiple toggles
	                        }
	                    }

	            // Update the stopwatch time if running
	            if (stopwatch_running) {
	                //_delay_ms(1000); // 1 second delay
	                sec++;
	                if (sec == 60) {
	                    sec = 0;
	                    min++;
	                    if (min == 60) {
	                        min = 0;
	                        hour++;
	                        if (hour == 24) {
	                            hour = 0; // Reset after 24 hours
	                        }
	                    }
	                }
	            }

	            // Display the stopwatch time
	            CLCD_voidClear();
	            CLCD_voidSetXYPosition(0, 0); // Set cursor to position 0, 0
	            CLCD_voidSendInteger(hour);  // Display hours
	            CLCD_voidSendData(':');
	            CLCD_voidSendInteger(min);   // Display minutes
	            CLCD_voidSendData(':');
	            CLCD_voidSendInteger(sec);
	            _delay_ms(500);

	            if(KPD_u8GetPressedKey()==13){
	            	    	    		START_UP_MODE();

	            	    	    	}
	        }


}

void stopwatch_init(){

	//DIO_voidSetPortDirection(DIO_u8PORTA, DIO_u8OUTPUT);

		    // Configure Port D for output (LCD RS, RW, and EN) and input (buttons)
		    DIO_voidSetPortDirection(DIO_u8PORTD, 0b00000111); // Pins 0-2 are outputs, others are inputs

		    // Enable pull-up resistors for buttons on PIN3 (stop) and PIN4 (start)
		    DIO_voidSetPinDirection(DIO_u8PORTD, DIO_u8PIN3, DIO_u8INPUT);
		    DIO_voidSetPinDirection(DIO_u8PORTD, DIO_u8PIN4, DIO_u8INPUT);
		    DIO_voidSetPinValue(DIO_u8PORTD, DIO_u8PIN3, DIO_u8HIGH); // Pull-up for PIN3
		    DIO_voidSetPinValue(DIO_u8PORTD, DIO_u8PIN4, DIO_u8HIGH); // Pull-up for PIN4
		    DIO_voidSetPinValue(DIO_u8PORTD, DIO_u8PIN5, DIO_u8HIGH); // Pull-up for PIN5

		    // Initialize TWI and LCD
		    TWI_voidMasterInit();
		    CLCD_voidInit();

		    // Optionally set the time on the RTC
		  //  rtc_voidsettime(0, 0, 0); // Set RTC to 00:00:00 initially

		    // Display "stopwatch mode" message
		    CLCD_voidSendString("Stopwatch Mode:");
		    _delay_ms(2000);
		    CLCD_voidClear();

}
