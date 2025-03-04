/*


 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "rtc_interface.h"
#include "TWI_interface.h"
#include "util/delay.h"

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "rtc_interface.h"
#include "TWI_interface.h"


/* Helper function to convert Decimal to BCD */
static u8 DecimalToBCD(u8 decimal) {
    return ((decimal / 10) << 4) | (decimal % 10);
}

/* Function to set time on DS1307 RTC */
void rtc_voidsettime(u8 Copy_u8sec, u8 Copy_u8min, u8 Copy_u8hours) {
    /* Convert Decimal values to BCD */
    u8 bcdSec = DecimalToBCD(Copy_u8sec);
    u8 bcdMin = DecimalToBCD(Copy_u8min);
    u8 bcdHours = DecimalToBCD(Copy_u8hours);

    /* Sending the Start Condition */
    TWI_voidSendStartCondition();

    /* Choosing the DS1307 Slave address with write (0x68) */
    TWI_voidSendSlaveAddressWithWrite(0x68);

    /* Sending the register address (0x00 for seconds register) */
    TWI_voidMasterSendDatawithAck(0x00);

    /* Sending the time data in BCD format */
    TWI_voidMasterSendDatawithAck(bcdSec);   // Send seconds
    TWI_voidMasterSendDatawithAck(bcdMin);   // Send minutes
    TWI_voidMasterSendDatawithAck(bcdHours); // Send hours

    /* Sending the Stop Condition */
    TWI_voidSendStopCondition();
    _delay_ms(10);  // Wait for RTC to process the time set
}


/* Function to read time from DS1307 RTC */
void rtc_u8Readtime(u8 *Copy_u8sec, u8 *Copy_u8min, u8 *Copy_u8hours) {
    /* Sending Start Condition */
    TWI_voidSendStartCondition();

    /* Sending Slave Address with write to specify register to read */
    TWI_voidSendSlaveAddressWithWrite(0x68);

    /* Sending the register address (0x00 for seconds register) */
    TWI_voidMasterSendDatawithAck(0x00);

    /* Sending the repeated Start Condition to switch to read mode */
    TWI_voidSendRepeatedStart();

    /* Sending Slave Address with read */
    TWI_voidSendSlaveAddressWithRead(0x68);

    /* Receiving data from the RTC */
    *Copy_u8sec = TWI_voidMasterReceivewithAck();  // Receive seconds
    *Copy_u8min = TWI_voidMasterReceivewithAck();  // Receive minutes
    *Copy_u8hours = TWI_voidMasterReceivewithoutAck(); // Receive hours

    /* Convert BCD to Decimal for each value */
    *Copy_u8sec = ((*Copy_u8sec & 0x0F) + (((*Copy_u8sec >> 4) & 0x0F) * 10));
    *Copy_u8min = ((*Copy_u8min & 0x0F) + (((*Copy_u8min >> 4) & 0x0F) * 10)) ;
    *Copy_u8hours = ((*Copy_u8hours & 0x0F) + (((*Copy_u8hours >> 4) & 0x0F) * 10));

    /* Sending the Stop Condition */
    TWI_voidSendStopCondition();
}
/* Function to read the date from DS1307 RTC */
void rtc_voidReadDate(u8 *Copy_u8Day, u8 *Copy_u8Date, u8 *Copy_u8Month, u8 *Copy_u8Year) {
    /* Sending Start Condition */
    TWI_voidSendStartCondition();

    /* Sending Slave Address with write to specify register to read */
    TWI_voidSendSlaveAddressWithWrite(0x68);

    /* Sending the register address (0x03 for day register) */
    TWI_voidMasterSendDatawithAck(0x03);

    /* Sending the repeated Start Condition to switch to read mode */
    TWI_voidSendRepeatedStart();

    /* Sending Slave Address with read */
    TWI_voidSendSlaveAddressWithRead(0x68);

    /* Receiving data from the RTC */
    *Copy_u8Day = TWI_voidMasterReceivewithAck();     // Receive day
    *Copy_u8Date = TWI_voidMasterReceivewithAck();    // Receive date
    *Copy_u8Month = TWI_voidMasterReceivewithAck();   // Receive month
    *Copy_u8Year = TWI_voidMasterReceivewithoutAck(); // Receive year

    /* Convert BCD to Decimal for each value */
    *Copy_u8Day = ((*Copy_u8Day & 0x0F) + (((*Copy_u8Day >> 4) & 0x0F) * 10));
    *Copy_u8Date = ((*Copy_u8Date & 0x0F) + (((*Copy_u8Date >> 4) & 0x0F) * 10));
    *Copy_u8Month = ((*Copy_u8Month & 0x0F) + (((*Copy_u8Month >> 4) & 0x0F) * 10));
    *Copy_u8Year = ((*Copy_u8Year & 0x0F) + (((*Copy_u8Year >> 4) & 0x0F) * 10));

    /* Sending the Stop Condition */
    TWI_voidSendStopCondition();
}
/* Function to set the date on DS1307 RTC */
void rtc_voidSetDate(u8 Copy_u8Day, u8 Copy_u8Date, u8 Copy_u8Month, u8 Copy_u8Year) {
    /* Convert Decimal values to BCD */
    u8 bcdDay = DecimalToBCD(Copy_u8Day);
    u8 bcdDate = DecimalToBCD(Copy_u8Date);
    u8 bcdMonth = DecimalToBCD(Copy_u8Month);
    u8 bcdYear = DecimalToBCD(Copy_u8Year);

    /* Sending the Start Condition */
    TWI_voidSendStartCondition();

    /* Sending the DS1307 Slave address with write (0x68) */
    TWI_voidSendSlaveAddressWithWrite(0x68);

    /* Sending the register address (0x03 for day register) */
    TWI_voidMasterSendDatawithAck(0x03);

    /* Sending the date data in BCD format */
    TWI_voidMasterSendDatawithAck(bcdDay);   // Send day
    TWI_voidMasterSendDatawithAck(bcdDate);  // Send date
    TWI_voidMasterSendDatawithAck(bcdMonth); // Send month
    TWI_voidMasterSendDatawithAck(bcdYear);  // Send year

    /* Sending the Stop Condition */
    TWI_voidSendStopCondition();
    _delay_ms(10);  // Wait for RTC to process the date set
}
