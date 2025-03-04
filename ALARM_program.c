/*
 * ALARM_program.c
 *
 *  Created on: Dec 5, 2024
 *      Author: omarf
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "rtc_interface.h"
#include "util/delay.h"

static u8 AlarmHours = 0, AlarmMinutes = 0;
static u8 AlarmEnabled = 0;

/* Function to set the alarm time (hardcoded) */
void Alarm_voidSetTime(u8 hours, u8 minutes) {
    AlarmHours = hours;
    AlarmMinutes = minutes;
    AlarmEnabled = 1;

    CLCD_voidClear();
    CLCD_voidSendString("Alarm Set:");
//    CLCD_voidSetXYPosition(1, 0);
    CLCD_voidSendInteger(hours);
    CLCD_voidSendString(":");
    CLCD_voidSendInteger(minutes);
    _delay_ms(3000);
}


/* Function to monitor and trigger the alarm */
void Alarm_voidMonitor(void) {
    // Check if alarm is enabled
    if (AlarmEnabled == 0) {
        return;
    }

    // Variables to store current time
    u8 currentHours = 0, currentMinutes = 0, currentSeconds = 0;

    // Read the current time from the RTC
    rtc_u8Readtime(&currentSeconds, &currentMinutes, &currentHours);

    // Debugging (Optional): Display current time on LCD
    CLCD_voidClear();
    CLCD_voidSendString("Clock: ");
    CLCD_voidSendInteger(currentHours);
    CLCD_voidSendString(":");
    CLCD_voidSendInteger(currentMinutes);
    CLCD_voidSendString(":");
    CLCD_voidSendInteger(currentSeconds);

    _delay_ms(1000); // Allow user to see the time on LCD

    // Compare current time with alarm time
    if (currentHours == AlarmHours && currentMinutes == AlarmMinutes && AlarmEnabled == 1) {
        // Activate the buzzer
    	DIO_voidSetPinDirection(DIO_u8PORTC, DIO_u8PIN2, DIO_u8OUTPUT);
    	// Display alarm message
    	CLCD_voidClear();
    	CLCD_voidSendString("Alarm Ring!");

    	/* Break The Alarm when the Switch is pressed */

    	/* INPUR FOR THE SWITCH */
    	DIO_voidSetPinDirection(DIO_u8PORTC, DIO_u8PIN3, DIO_u8INPUT);
    	/* Pull Up */
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



        // Disable the alarm to avoid retriggering
        AlarmEnabled = 0;
    }
}
