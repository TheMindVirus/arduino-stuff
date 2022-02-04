//Based on SD Association SD PHY Specification v6.00 (now v8.00)
//Ported from Arduino SD Library

#ifndef _SCRREGISTER_H_
#define _SCRREGISTER_H_

#define SD_REGISTER_SCR_SIZE   8

struct SCR_Register
{
    unsigned sd_spec :4; //byte 0 bit 0
    unsigned scr_structure :4; 
    unsigned sd_bus_widths :4; //byte 1 bit 0
    unsigned sd_security :3;
    unsigned data_stat_after_erase :1;
    unsigned sd_specx_high :2; //byte 2 bit 0
    unsigned sd_spec4 :1;
    unsigned ex_security :4;
    unsigned sd_spec3 :1;
    unsigned cmd_support :4; //byte 3 bit 0
    unsigned reserved1 :2;
    unsigned sd_specx_low :2; 
    uint8_t reserved2[4]; //bytes 4-7
};

union SCR_Register_t
{
    uint8_t bytes[SD_REGISTER_SCR_SIZE];
    struct SCR_Register SCR;
};

#endif//_SCRREGISTER_H_