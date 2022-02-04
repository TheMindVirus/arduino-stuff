//Based on SD Association SD PHY Specification v6.00 (now v8.00)
//Ported from Arduino SD Library

#ifndef _RESPONSE_H_
#define _RESPONSE_H_

#pragma pack(push) //Remove padding from structs
#pragma pack(1)

#include "OCRregister.h"
#include "CSDregister.h"
#include "CIDregister.h"
#include "SCRregister.h"

#define SD_RESPONSE_INVALID         0xFF
#define SD_RESPONSE_VALID_MASK      0x80
#define SD_RESPONSE_CHECK_PATTERN   0xAA

#define SD_RESPONSE_R1_SIZE         1
#define SD_RESPONSE_R2_SIZE         2
#define SD_RESPONSE_R3_SIZE         5
#define SD_RESPONSE_R7_SIZE         5

struct Response1 //General
{
    unsigned in_idle_state :1; //byte 0 bit 0
    unsigned erase_reset :1;
    unsigned illegal_command :1;
    unsigned com_crc_error :1;
    unsigned erase_sequence_error :1;
    unsigned address_error :1;
    unsigned param_error :1;
    unsigned reserved :1;
};

struct Response2 //SEND_STATUS (CMD13)
{
    struct Response1 R1; //byte 0
    unsigned card_is_locked :1; //byte 1 bit 0
    unsigned wp_erase_skip_lock_unlock_cmd_failed :1;
    unsigned error_ :1;
    unsigned cc_error :1;
    unsigned card_ecc_failed :1;
    unsigned wp_violation :1;
    unsigned erase_param :1;
    unsigned out_of_range_csd_overwrite :1;
};

struct Response3 //READ_OCR (CMD58)
{
    struct Response1 R1; //byte 0
    struct OCR_Register OCR; //bytes 1-4
};

struct Response7 //SEND_IF_COND (CMD8)
{
    struct Response1 R1; //byte 0
    unsigned reserved1 :4; //byte 1 bit 0
    unsigned cmd_ver :4;
    uint8_t reserved2; //byte 2
    unsigned voltage_accepted :4; //byte 3 bit 0
    unsigned reserved3 :4;
    uint8_t check_pattern; //byte 4
};

union Response1_t //General
{
    uint8_t bytes[SD_RESPONSE_R1_SIZE];
    struct Response1 R1;
};

union Response2_t //SEND_STATUS (CMD13)
{
    uint8_t bytes[SD_RESPONSE_R2_SIZE];
    struct Response2 R2;
};

union Response3_t //READ_OCR (CMD58)
{
    uint8_t bytes[SD_RESPONSE_R3_SIZE];
    struct Response3 R3;
};

union Response7_t //SEND_IF_COND (CMD8)
{
    uint8_t bytes[SD_RESPONSE_R7_SIZE];
    struct Response7 R7;
};

#pragma pack(pop)

#endif//_RESPONSE_H_