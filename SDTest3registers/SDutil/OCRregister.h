//Based on SD Association SD PHY Specification v6.00 (now v8.00)
//Ported from Arduino SD Library

#ifndef _OCRREGISTER_H_
#define _OCRREGISTER_H_

#define SD_REGISTER_OCR_SIZE   4

struct OCR_Register
{
    unsigned switch_1_8_V_accepted :1; //byte 0 bit 0
    unsigned reserved1 :4;
    unsigned uhs2_card_status :1;
    unsigned card_capacity_status :1;
    unsigned card_power_up_status_busy :1; 
    unsigned _2_8_V_to_2_9_V :1; //byte 1 bit 0
    unsigned _2_9_V_to_3_0_V :1;
    unsigned _3_0_V_to_3_1_V :1;
    unsigned _3_1_V_to_3_2_V :1;
    unsigned _3_2_V_to_3_3_V :1;
    unsigned _3_3_V_to_3_4_V :1;
    unsigned _3_4_V_to_3_5_V :1;
    unsigned _3_5_V_to_3_6_V :1; 
    unsigned reserved2 :7; //byte 2 bit 0
    unsigned _2_7_V_to_2_8_V :1; 
    unsigned reserved3 :7; //byte 3 bit 0
    unsigned reserved_low_voltage :1;
};

union OCR_Register_t
{
    uint8_t bytes[SD_REGISTER_OCR_SIZE];
    struct OCR_Register OCR;
};

#endif//_OCRREGISTER_H_