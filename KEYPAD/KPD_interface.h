/*
 * KPD_interface.h
 *
 *  Created on: Sep 20, 2024
 *      Author: omarf
 */

#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_

void KPD_voidInit(void);

u8 KPD_u8GetPressedKey(void);

u8 KPD_u8ProcessInput(u8 magicKey);

#define NOT_PRESSED 99

#endif /* KPD_INTERFACE_H_ */
