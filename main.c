#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "rtc_interface.h"
#include "TWI_interface.h"
#include "CLCD_interface.h"
#include "util/delay.h"
#include "countdown_interface.h"
#include "KPD_interface.h"
#include "stopwatch_interface.h"
#include "ALARM_interface.h"


void ALARM_MODE(void);
void COUNT_DOWN_MODE(void);
void STOP_WATCH_MODE(void);
void REAL_TIME_DATE_MODE(void);
void START_UP_MODE(void);
void ADJUST_TIME_MODE(void);

u8 hour, minute, second;

u8 day, date, month, year;

u8 mode;



int main(void) {
	DIO_voidSetPortDirection(DIO_u8PORTA, DIO_u8PORTOUTPUT); // portA is set all outputs
    DIO_voidSetPinDirection(DIO_u8PORTD, DIO_u8PIN0, DIO_u8OUTPUT); // Direction of first pin
    DIO_voidSetPinDirection(DIO_u8PORTD, DIO_u8PIN1, DIO_u8OUTPUT); // Direction of second pin
    DIO_voidSetPinDirection(DIO_u8PORTD, DIO_u8PIN2, DIO_u8OUTPUT); // Direction of third pin
    // For buzzer
    DIO_voidSetPinDirection(DIO_u8PORTC, DIO_u8PIN2, DIO_u8OUTPUT);
    // Pull up for Adjust Time Mode
    DIO_voidSetPinValue(DIO_u8PORTD, DIO_u8PIN6, DIO_u8HIGH);

    TWI_voidMasterInit();
    CLCD_voidInit();
    KPD_voidInit();

    // rtc_voidsettime(40, 34, 13);
    // rtc_voidSetDate(0, 19, 12, 24);

//	// ALARM_MODE();
    START_UP_MODE();


//
//    //STOP_WATCH_MODE();
//    // ADJUST_TIME_MODE();


}





void ALARM_MODE(void) {
	CLCD_voidSendString("Alarm Mode");
	_delay_ms(2000);
	CLCD_voidClear();
	CLCD_voidSendString("Hour: ");
    hour = KPD_u8ProcessInput(80);
    CLCD_voidClear();
    CLCD_voidSendString("Minute: ");
    minute = KPD_u8ProcessInput(80);
    CLCD_voidClear();


    Alarm_voidSetTime(hour, minute);

    while(1) {
    	Alarm_voidMonitor();

    	if(KPD_u8GetPressedKey()==13){
    		START_UP_MODE();

    	}
    }
}

void COUNT_DOWN_MODE(void) {

			countdown_init();
			KPD_voidInit();
			CLCD_voidSendString("Hours: ");
		 	hour = KPD_u8ProcessInput(80);
		 	CLCD_voidClear();
		 	CLCD_voidSendString("Minutes: ");
		 	minute = KPD_u8ProcessInput(80);
		 	CLCD_voidClear();
		 	CLCD_voidSendString("Seconds: ");
		 	second = KPD_u8ProcessInput(80);
		 	CLCD_voidClear();
		    while (1) {
		    	CLCD_voidClear();
		    	countdown(hour, minute , second);
		    	if(KPD_u8GetPressedKey()==13){
		    	    		START_UP_MODE();

		    	    	}
		    }
}

void STOP_WATCH_MODE(void) {
		stopwatch_init();
	    while (1) {
	    	stopwatch();

	    }

}

void REAL_TIME_DATE_MODE(void) {

	    // Optionally set the time on the RTC (uncomment if you need to set the time initially)
	     //rtc_voidsettime(50, 20, 7); // Set RTC to 09:41:00

	    while (1) {
	        // Read time from RTC
	        rtc_u8Readtime(&second, &minute, &hour);
	        rtc_voidReadDate(&day,&date,&month,&year);

	        // Check if time values are valid
	        if (second == 0 && minute == 0 && hour == 0) {
	            // This could indicate the RTC isn't initialized properly
	            CLCD_voidClear();
	            CLCD_voidSetXYPosition(0, 0);
	            CLCD_voidSendString("RTC Error!");
	            _delay_ms(1000);  // Display error message for 1 second
	        } else {

	            CLCD_voidClear();
	            CLCD_voidSetXYPosition(0, 0); // Set cursor to position 0, 0 (top left)
	            CLCD_voidSendInteger(hour);  // Display hours
	            CLCD_voidSendData(':');
	            CLCD_voidSendInteger(minute);   // Display minutes
	            CLCD_voidSendData(':');
	            CLCD_voidSendInteger(second);   // Display seconds
	            CLCD_voidSetXYPosition(0,1);
	            CLCD_voidSendInteger(year);  // Display hours
	            CLCD_voidSendData('-');
				  CLCD_voidSendInteger(month);   // Display minutes
				CLCD_voidSendData('-');
				CLCD_voidSendInteger(date);

				if(KPD_u8GetPressedKey()==13){
				    		START_UP_MODE();

				    	}


	        }

	        _delay_ms(1000); // Wait for 1 second before updating time
	    }
}

void START_UP_MODE(void) {
	CLCD_voidClear();
	CLCD_voidSendString("Select Mode: ");
	_delay_ms(3000);
	CLCD_voidClear();
	CLCD_voidSendString("A:R4 C:R8 Adj:P1");
	CLCD_voidSetXYPosition(0, 1);
	CLCD_voidSendString("S:R12 RTC:R16");

	 while (1) {
	        mode = KPD_u8GetPressedKey();
	        if (mode != NOT_PRESSED) {
	            if (mode == 84) {  // Check for the key corresponding to Alarm Mode
	            	CLCD_voidClear();
	                ALARM_MODE();
	            }
	            else if (mode == 81) {
	            	CLCD_voidClear();
	            	COUNT_DOWN_MODE();
	            }
	            else if (mode == 82) {
	            	CLCD_voidClear();
	            	STOP_WATCH_MODE();
	            }
	            else if (mode == 83) {
	            	 CLCD_voidClear();
	            	 REAL_TIME_DATE_MODE();
	            }
	        }
            if (DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN6) == 0) {
            	CLCD_voidClear();
            	ADJUST_TIME_MODE();
            }
	    }


}

void ADJUST_TIME_MODE(void) {
	CLCD_voidSendString("Adjust Time ");
	CLCD_voidSetXYPosition(0, 1);
	CLCD_voidSendString("And Date ");
	CLCD_voidSetXYPosition(0, 1);


	_delay_ms(3000);
	CLCD_voidClear();
	CLCD_voidSendString("Hour: ");
 	hour = KPD_u8ProcessInput(80);
 	CLCD_voidClear();

 	CLCD_voidSendString("Minutes: ");
 	minute = KPD_u8ProcessInput(80);
 	CLCD_voidClear();

 	CLCD_voidSendString("Seconds: ");
 	second = KPD_u8ProcessInput(80);
 	CLCD_voidClear();

 	CLCD_voidSendString("Year: ");
 	year = KPD_u8ProcessInput(80);
 	CLCD_voidClear();

 	CLCD_voidSendString("Month: ");
 	month = KPD_u8ProcessInput(80);
 	CLCD_voidClear();

 	CLCD_voidSendString("Day: ");
 	day =  KPD_u8ProcessInput(80);
 	CLCD_voidClear();

 	rtc_voidsettime(second, minute, hour);
 	rtc_voidSetDate(date,day ,month, year);
 	update_display(hour, minute, second);
 	CLCD_voidSetXYPosition(0, 1);
 	update_display(year, month, day);

while (1){

 	if(KPD_u8GetPressedKey()==13){
 	    		START_UP_MODE();

 	    	}
 	}
}
