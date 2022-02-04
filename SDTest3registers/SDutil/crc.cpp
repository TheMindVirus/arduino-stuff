//Based on SD Association SD PHY Specification v6.00 (now v8.00)
//Ported from Arduino SD Library

#include "crc.h"

uint8_t CRC7(uint8_t* data, uint16_t length)
{
    uint8_t crc = 0;
    for (uint16_t i = 0; i < length; ++i)
    {
        for (int b = 7; b >= 0; --b)
        {
            crc <<= 1;
            crc = SETBIT(crc, 0, XOR(BIT(data[i], b), BIT(crc, 7)));
            crc = SETBIT(crc, 3, XOR(BIT(crc, 3), BIT(crc, 0)));
        }
    }
    return ((crc << 1) | 1) & 0xFF;
}

uint16_t CRC16(uint8_t* data, uint16_t length)
{
    uint32_t crc = 0;
    for (uint16_t i = 0; i < length; ++i)
    {
        for (int b = 7; b >= 0; --b)
        {
            crc <<= 1;
            crc = SETBIT(crc, 0, XOR(BIT(data[i], b), BIT(crc, 16)));
            crc = SETBIT(crc, 5, XOR(BIT(crc, 5), BIT(crc, 0)));
            crc = SETBIT(crc, 12, XOR(BIT(crc, 12), BIT(crc, 0)));
        }
    }
    return crc & 0xFFFF;
}