//Based on SD Association SD PHY Specification v6.00 (now v8.00)
//Ported from Arduino SD Library

#ifndef _CRC_H_
#define _CRC_H_

//Macros
#define XOR(A, B) (A ^ B)
#define BIT(DATA, BITNO) ((DATA >> BITNO) & 1)
#define SETBIT(DATA, BITNO, VALUE) ((VALUE > 0) ? DATA | (1 << BITNO) : DATA & ~(1 << BITNO))

//Forward Declarations
uint8_t CRC7(uint8_t* data, uint16_t length);
uint16_t CRC16(uint8_t* data, uint16_t length);

#endif//_CRC_H_