/*
 * rtc_interface.h
 *
 *  Created on: Dec 4, 2024
 *      Author: Ahmed
 */

#ifndef RTC_INTERFACE_H_
#define RTC_INTERFACE_H_

void rtc_voidsettime( u8 Copy_u8sec,u8 Copy_u8min,u8 Copy_u8hours);

void rtc_u8Readtime(u8 *Copy_u8sec,u8 *Copy_u8min,u8 *Copy_u8hours);

void rtc_voidReadDate(u8 *Copy_u8Day, u8 *Copy_u8Date, u8 *Copy_u8Month, u8 *Copy_u8Year);

void rtc_voidSetDate(u8 Copy_u8Day, u8 Copy_u8Date, u8 Copy_u8Month, u8 Copy_u8Year);
#endif /* RTC_INTERFACE_H_ */
