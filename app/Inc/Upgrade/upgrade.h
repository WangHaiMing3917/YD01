#ifndef _UPGRADE_H_
#define _UPGRADE_H_

#include "upgrade_typedef.h"

#define SOH     (0x01)
#define STX     (0x02)
#define EOT     (0x04)
#define ACK     (0x06)
#define NAK     (0x15)
#define CAN     (0x18)
#define CTRLZ   (0x1A)
#define C       (0x43)

uint16_t Crc16_Xmodem(uint8_t *data,uint16_t length);
void Send_C_Check_Xmodem_Mode(void);
void Update_Recive(XMODEM_STRUCT *Rtr);
void Send_over_Update(void);
void X_Modem_Timer(void);
void Update_PowerDown_error_clear_All(void);
void Update_CAN_Process(void);
void Xmodem_error_clear(void);

void Send_Nak_Xmodem(void);


#endif
