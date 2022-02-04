//Based on SD Association SD PHY Specification v6.00 (now v8.00)
//Ported from Arduino SD Library

#ifndef _SDCARD_H_
#define _SDCARD_H_

#include <SPI.h>
#include <stdint.h>

#include "SDutil/response.h"
#include "SDutil/crc.h"

//Definitions
#define SDCARD_SPI_SPEED         50000000 //baud
#define SDCARD_BLOCK_LENGTH      512
#define SDCARD_PREAMBLE          0xFF
#define SDCARD_PREAMBLE_LENGTH   10
#define SDCARD_RESPONSE_DELAY    10 //ms
#define SDCARD_RETRY_LIMIT       20
#define SDCARD_CMD_SIZE          6

class SDcard
{
public:
    enum status_t
    {
        STATUS_OK = 0,
        STATUS_BUSY,
        STATUS_ERR_IO,
        STATUS_ERR_PROTOCOL,
        STATUS_ERR_NOT_FOUND,
        STATUS_ERR_BAD_ADDRESS,
        STATUS_ERR_BAD_DATA,
        STATUS_ERR_NOT_INITIALIZED,
        STATUS_ERR_UNSUPPORTED_DEV,
    };

    enum type_t
    {
        TYPE_UNUSABLE = 0,
        TYPE_1,
        TYPE_2,
        TYPE_2_HC
    };

    enum version_t
    {
        VERSION_UNKNOWN = 0,
        VERSION_1_0X,
        VERSION_1_10,
        VERSION_2_00,
        VERSION_3_0X,
        VERSION_4_XX,
        VERSION_5_XX,
        VERSION_6_XX
    };

    SPIClass bus; //Ported to Arduino SPI, ideally make completely independent
    SPISettings settings = SPISettings(SDCARD_SPI_SPEED, MSBFIRST, SPI_MODE0);
    enum status_t status;
    enum type_t type;
    enum version_t version;
    size_t length;
    size_t capacity;
    union OCR_Register_t OCR;
    union CSD_Register_t CSD;
    union CID_Register_t CID;
    union SCR_Register_t SCR;

    //External Methods
    enum status_t begin(SPIClass& spi_bus);
    enum status_t read(size_t block, uint8_t* buffer);
    enum status_t write(size_t block, uint8_t* buffer);

private:
    //Command Format: CMD | 0x40, Args << 24, Args << 16, Args << 8, Args, CRC
    uint8_t ACMD[SDCARD_CMD_SIZE]      = {0x77, 0x00, 0x00, 0x00, 0x00, 0xFF};   //ACMD Mode (R1???)
    uint8_t CMD0[SDCARD_CMD_SIZE]      = {0x40, 0x00, 0x00, 0x00, 0x00, 0x95};   //GO_IDLE_STATE (R1)
    uint8_t CMD8[SDCARD_CMD_SIZE]      = {0x48, 0x00, 0x00, 0x01, 0xAA, 0x87};   //SEND_IF_COND (R7)
    uint8_t ACMD41_V1[SDCARD_CMD_SIZE] = {0x69, 0x00, 0x00, 0x00, 0x00, 0xFF};   //SD_SEND_OP_COND V1 (R1)
    uint8_t ACMD41_V2[SDCARD_CMD_SIZE] = {0x69, 0x40, 0x00, 0x00, 0x00, 0xFF};   //SD_SEND_OP_COND V2 (R1)
    uint8_t CMD58[SDCARD_CMD_SIZE]     = {0x7A, 0x00, 0x00, 0x00, 0x00, 0xFF};   //READ_OCR (R3)
    uint8_t CMD10[SDCARD_CMD_SIZE]     = {0x4A, 0x00, 0x00, 0x00, 0x00, 0xFF};   //SEND_CID (R1)
    uint8_t CMD9[SDCARD_CMD_SIZE]      = {0x49, 0x00, 0x00, 0x00, 0x00, 0xFF};   //SEND_CSD (R1)
    uint8_t ACMD51[SDCARD_CMD_SIZE]    = {0x73, 0x00, 0x00, 0x00, 0x00, 0xFF};   //SEND_SCR (R1)
    uint8_t CMD17[SDCARD_CMD_SIZE]     = {0x51, 0x00, 0x00, 0x00, 0x00, 0xFF};   //READ_SINGLE_BLOCK (R1)
    uint8_t CMD24[SDCARD_CMD_SIZE]     = {0x58, 0x00, 0x00, 0x00, 0x00, 0xFF};   //WRITE_BLOCK (R1)

    //Internal Methods
    enum status_t _command(uint8_t* command);
    enum status_t _response(uint8_t* response, size_t length, bool check_valid);
    enum status_t _read_OCR();
    enum status_t _read_CSD();
    enum status_t _read_CID();
    enum status_t _read_SCR();
};

//Macros
#define SDCARD_ASSERT_OK(STATUS) if (STATUS != STATUS_OK) { Serial.println("SD_ERROR_NOT_OK"); status = STATUS; return status; }
#define SDCARD_ASSERT(CONDITION, STATUS) if (CONDITION) { Serial.println("SD_ERROR_CONDITION"); status = STATUS; return status; }
#define SDCARD_ACMD41_V(SDTYPE) ((SDTYPE == TYPE_2) ? ACMD41_V2 : ACMD41_V1)

#endif//_SDCARD_H_
