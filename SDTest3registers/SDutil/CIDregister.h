//Based on SD Association SD PHY Specification v6.00 (now v8.00)
//Ported from Arduino SD Library

#ifndef _CIDREGISTER_H_
#define _CIDREGISTER_H_

#define SD_REGISTER_CID_SIZE   16

struct CID_Register
{
    uint8_t manufacturer_id; //byte 0
    uint8_t application_id_high; //byte 1
    uint8_t application_id_low; //byte 2
    uint8_t product_name[5]; //bytes 3-7
    uint8_t product_revision; //byte 8
    uint8_t product_serial_number[4]; //bytes 9-12
    unsigned manufacturing_date_high :4; //byte 13 bit 0
    unsigned reserved1 :4; 
    uint8_t manufacturing_date_low; //byte 14
    unsigned always1 :1; //byte 15 bit 0
    unsigned crc7 :7;
};

union CID_Register_t
{
    uint8_t bytes[SD_REGISTER_CID_SIZE];
    struct CID_Register CID;
};

#endif//_CIDREGISTER_H_