#ifndef _CRC32_H_
#define _CRC32_H_



#include "stdint.h"

uint32_t Crc32_Cal(uint8_t *data, uint16_t length);

 uint16_t Crc16_Cal(uint8_t *data, uint16_t length);

#endif
