#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

void TWI_voidMasterInit(void);
void TWI_voidSlaveInit(void);
void TWI_voidSendStartCondition(void);
void TWI_voidSendRepeatedStart(void);
void TWI_voidSendSlaveAddressWithWrite(u8 Copy_u8Address);
void TWI_voidSendSlaveAddressWithRead(u8 Copy_u8Address);
void TWI_voidMasterSendDatawithAck(u8 Copy_u8Data);
void TWI_voidMasterSendDatawithoutAck(u8 Copy_u8Data);
u8 TWI_voidMasterReceivewithAck(void);
u8 TWI_voidMasterReceivewithoutAck(void);
void TWI_voidSendStopCondition(void);

#endif /* TWI_INTERFACE_H_ */

