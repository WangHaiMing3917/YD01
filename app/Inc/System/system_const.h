#ifndef _SYSTEM_CONST_H_
#define _SYSTEM_CONST_H_


enum{

   Tx_Idle=0,
   Tx_Request,
   Tx_Delayed,
   Tx_WaitAck,
   Tx_WaitComplete,
   Tx_Repeat,

};

enum{

    without_change_flag =0,
    change_flag,

};

#define RELAY_OFF      0u
#define RELAY_ON       1u

#define CLOSE_STATE    1u
#define OPEN_STATE     2u
#define AUTO_STATE     4u

#define MonDay         0x01
#define Tuesday        0x02
#define Wednesday      0x04
#define Thursday       0x08
#define Friday         0x10
#define Saturday       0x20
#define Sunday         0x40

#define CHANNEL_1      0x01
#define CHANNEL_2      0x02
#define CHANNEL_3      0x04
#define CHANNEL_4      0x08
#define CHANNEL_5      0x10
#define CHANNEL_6      0x20
#define CHANNEL_7      0x40

#define Hours_Flash    0x01
#define Minute_Flash   0x02
#define Week_Flash     0x03







#endif
