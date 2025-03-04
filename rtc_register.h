/*
 * rtc_register.h
 *
 *  Created on: Dec 4, 2024
 *      Author: Ahmed
 */

#ifndef RTC_REGISTER_H_
#define RTC_REGISTER_H_


#define sec			*((volatile u8*)(0x00))
#define min			*((volatile u8*)(0x01))
#define hour		*((volatile u8*)(0x02))
#define day			*((volatile u8*)(0x03))
#define date		*((volatile u8*)(0x04))
#define mounth		*((volatile u8*)(0x05))
#define year		*((volatile u8*)(0x06))
#define control		*((volatile u8*)(0x0E))
#define status		*((volatile u8*)(0x0F))

#endif /* RTC_REGISTER_H_ */
