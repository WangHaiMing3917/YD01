#include "system.h"

#define CRC16_POLY                   0x8005

//****************************************************************//
//函数名称: uint32_t Crc32_Cal(uint8_t *data, uint16_t length)
//函数功能: 
//参    数: 
//返 回 值: 
//说    明：Crc校验计算
//修改记录: 2023.6.13 
//***************************************************************//

uint32_t Crc32_Cal(uint8_t *data, uint16_t length){

    uint8_t i;
    uint32_t Crc = 0xffffffff;        // Initial value
    while(length--)
    {
        Crc ^= *data++;                // crc ^= *data; data++;
        
        for (i = 0; i < 8; i++)
        {
            if (Crc & 1)
                Crc = (Crc >> 1) ^ 0xEDB88320;// 0xEDB88320= reverse 0x04C11DB7
            else
                Crc = (Crc >> 1);
        }
    }
    return ~Crc;
}


//****************************************************************//
//函数名称: uint16_t Crc16_Cal(uint8_t *data, uint16_t length)
//函数功能: 
//参    数: 
//返 回 值: 
//说    明：Crc校验计算
//修改记录: 2023.6.13 
//***************************************************************//
uint16_t Crc16_Cal(uint8_t *data, uint16_t length){

     uint8_t i,crc_in;

     uint16_t crc_sum = 0xFFFF;

     while (length --) {

        crc_in = * (data ++);

        for (i=0u;i<8u;i++) {

           if (((crc_sum & 0x8000) >> 8) ^ (crc_in & 0x80))
              crc_sum = (crc_sum << 1) ^ CRC16_POLY;
           else
              crc_sum = (crc_sum << 1);
           
           crc_in <<= 1;
        }
     }
     return crc_sum;

}

