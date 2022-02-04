//Based on SD Association SD PHY Specification v6.00 (now v8.00)
//Ported from Arduino SD Library

#ifndef _CSDREGISTER_H_
#define _CSDREGISTER_H_

#define SD_REGISTER_CSD_SIZE   16

struct CSD_Register_V1
{
    unsigned reserved1 :6; //byte 0 bit 0
    unsigned csd_ver :2;
    uint8_t taac; //byte 1
    uint8_t nsac; //byte 2
    uint8_t tran_speed; //byte 3
    uint8_t ccc_high; //byte 4
    unsigned read_bl_len :4; //byte 5 bit 0
    unsigned ccc_low :4;
    unsigned c_size_high :2; //byte 6 bit 0
    unsigned reserved2 :2;
    unsigned dsr_imp :1;
    unsigned read_blk_misalign :1;
    unsigned write_blk_misalign :1;
    unsigned read_bl_partial :1; 
    uint8_t c_size_mid; //byte 7
    unsigned vdd_r_curr_max :3; //byte 8 bit 0
    unsigned vdd_r_curr_min :3;
    unsigned c_size_low :2; 
    unsigned c_size_mult_high :2; //byte 9 bit 0
    unsigned vdd_w_cur_max :3;
    unsigned vdd_w_curr_min :3;
    unsigned sector_size_high :6; //byte 10 bit 0
    unsigned erase_blk_en :1;
    unsigned c_size_mult_low :1; 
    unsigned wp_grp_size :7; //byte 11 bit 0
    unsigned sector_size_low :1; 
    unsigned write_bl_len_high :2; //byte 12 bit 0
    unsigned r2w_factor :3;
    unsigned reserved3 :2;
    unsigned wp_grp_enable :1;
    unsigned reserved4 :5; //byte 13 bit 0
    unsigned write_partial :1;
    unsigned write_bl_len_low :2;
    unsigned reserved5 :2; //byte 14 bit 0
    unsigned file_format :2;	
    unsigned tmp_write_protect :1;
    unsigned perm_write_protect :1;	
    unsigned copy :1;	
    unsigned file_format_grp :1;
    unsigned always1 :1; //byte 15 bit 0	
    unsigned crc :7;
};

struct CSD_Register_V2
{
    unsigned reserved1 :6; //byte 0 bit 0
    unsigned csd_structure :2;
    uint8_t taac; //byte 1
    uint8_t nsac; //byte 2
    uint8_t tran_speed; //byte 3
    uint8_t ccc_high; //byte 4
    unsigned read_bl_len :4; //byte 5 bit 0
    unsigned ccc_low :4; 
    unsigned reserved2 :4; //byte 6 bit 0
    unsigned dsr_imp :1;
    unsigned read_blk_misalign :1;
    unsigned write_blk_misalign :1;
    unsigned read_bl_partial :1; 
    unsigned c_size_high :6; //byte 7 bit 0
    unsigned reserved3 :2;
    uint8_t c_size_mid; //bytes 8-9
    uint8_t c_size_low; //bytes 8-9
    unsigned sector_size_high :6; //byte 10 bit 0
    unsigned erase_blk_en :1;
    unsigned reserved4 :1; 
    unsigned wp_grp_size :7; //byte 11 bit 0
    unsigned sector_size_low :1; 
    unsigned write_bl_len_high :2; //byte 12 bit 0
    unsigned r2w_factor :3;
    unsigned reserved5 :2;
    unsigned wp_grp_enable :1;
    unsigned reserved6 :5; //byte 13 bit 0
    unsigned write_partial :1;
    unsigned write_bl_len_low :2; 
    unsigned reserved7 :2; //byte 14 bit 0
    unsigned file_format :2;
    unsigned tmp_write_protect :1;
    unsigned perm_write_protect :1;
    unsigned copy :1;
    unsigned file_format_grp :1;
    unsigned always1 :1; //byte 15 bit 0
    unsigned crc :7;
};

union CSD_Register_t
{
    uint8_t bytes[SD_REGISTER_CSD_SIZE];
    struct CSD_Register_V1 V1;
    struct CSD_Register_V2 V2;
};

#endif//_CSDREGISTER_H_