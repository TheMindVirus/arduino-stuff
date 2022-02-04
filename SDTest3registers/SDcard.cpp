//Based on SD Association SD PHY Specification v6.00 (now v8.00)
//Ported from Arduino SD Library

#include "SDcard.h"
#include "SDutil/crc.cpp"

//----------------------------------------------------------------------------------
#pragma region //External Methods

enum SDcard::status_t SDcard::begin(SPIClass& spi_bus)
{
    status = STATUS_OK;
    union Response1_t response_type1;
    union Response7_t response_type7;

    //Initialisation
    bus = spi_bus;
    type = TYPE_UNUSABLE;
    version = VERSION_UNKNOWN;
    length = 0;
    capacity = 0;

    //Check if card exists
    status = _command(CMD0);
    SDCARD_ASSERT_OK(status);
    status = _response(response_type1.bytes, SD_RESPONSE_R1_SIZE, true);
    SDCARD_ASSERT_OK(status);
    
    SDCARD_ASSERT(!response_type1.R1.in_idle_state, STATUS_ERR_NOT_FOUND);

    Serial.println("Checking R1 Response");
    Serial.print(F("in_idle_state: ")); Serial.println(response_type1.R1.in_idle_state);
    Serial.print(F("erase_reset: ")); Serial.println(response_type1.R1.erase_reset);
    Serial.print(F("illegal_command: ")); Serial.println(response_type1.R1.illegal_command);
    Serial.print(F("com_crc_error: ")); Serial.println(response_type1.R1.com_crc_error);
    Serial.print(F("erase_sequence_error: ")); Serial.println(response_type1.R1.erase_sequence_error);
    Serial.print(F("address_error: ")); Serial.println(response_type1.R1.address_error);
    Serial.print(F("param_error: ")); Serial.println(response_type1.R1.param_error);
    Serial.print(F("reserved: ")); Serial.println(response_type1.R1.reserved);
    Serial.println();
    
    //Check card version
    status = _command(CMD8);
    SDCARD_ASSERT_OK(status); //Stuck here with invalid responseWord
    status = _response(response_type7.bytes, SD_RESPONSE_R7_SIZE, true);
    SDCARD_ASSERT_OK(status);

    //Check if card is SDV1
    if (response_type7.R7.R1.illegal_command) { type = TYPE_1; }
    else
    {
        //Check if card is SDV2
        SDCARD_ASSERT(response_type7.R7.check_pattern != SD_RESPONSE_CHECK_PATTERN, STATUS_ERR_PROTOCOL);
        type = TYPE_2;
    }

    //Attempt to initialise SD card
    for (size_t i = 1; i <= SDCARD_RETRY_LIMIT; ++i)
    {
        status = _command(ACMD);
        SDCARD_ASSERT_OK(status);
        status = _response(response_type1.bytes, SD_RESPONSE_R1_SIZE, true);
        SDCARD_ASSERT_OK(status);

        status = _command(SDCARD_ACMD41_V(type));
        SDCARD_ASSERT_OK(status);
        status = _response(response_type1.bytes, SD_RESPONSE_R1_SIZE, true);
        SDCARD_ASSERT_OK(status);

        if (response_type1.R1.illegal_command)
        {
            type = TYPE_UNUSABLE;
            status = STATUS_ERR_NOT_INITIALIZED;
            return status;
        }
        if (!response_type1.R1.in_idle_state) { break; }
        SDCARD_ASSERT(i >= SDCARD_RETRY_LIMIT, STATUS_ERR_NOT_INITIALIZED);
        delay(SDCARD_RESPONSE_DELAY);
    }

    //Read OCR register to check if initialisation was successful
    for (size_t i = 1; i <= SDCARD_RETRY_LIMIT; ++i)
    {
        status = _read_OCR();
        if (status == STATUS_OK) { break; }
        else if (status != STATUS_BUSY) { return status; }
    }

    //Read CSD register to get the capacity of the SD card
    status = _read_CSD();
    SDCARD_ASSERT_OK(status);

    //Read CID register to get manufacturer details
    status = _read_CID();
    SDCARD_ASSERT_OK(status);

    //Read SCR register to get the specification version used
    status = _read_SCR();
    SDCARD_ASSERT_OK(status);
    
    Serial.println("INITIALISATION COMPLETE");
    return status;
}

enum SDcard::status_t SDcard::read(size_t block, uint8_t* buffer)
{
    status = STATUS_OK;
    union Response1_t response_type1;
    uint8_t DATA_CRC[2] = {0, 0};

    //Select which block to read
    if (type != TYPE_2_HC) { block <<= 9; }
    CMD17[1] = block >> 24;
    CMD17[2] = block >> 16 & 0xFF;
    CMD17[3] = block >> 8 & 0xFF;
    CMD17[4] = block & 0xFF;

    //Ask the card to send the requested block
    status = _command(CMD17);
    SDCARD_ASSERT_OK(status);
    status = _response(response_type1.bytes, SD_RESPONSE_R1_SIZE, false);
    SDCARD_ASSERT_OK(status);
Serial.println(response_type1.R1.in_idle_state);
    SDCARD_ASSERT(response_type1.R1.in_idle_state, STATUS_ERR_PROTOCOL);
Serial.println("CHECK2");
    status = _response(buffer, length, true); //!!! Arduino might not like passing buffer through like this...
    SDCARD_ASSERT_OK(status);

    status = _response(DATA_CRC, 2, false);
    SDCARD_ASSERT_OK(status);

    uint16_t data_crc = (DATA_CRC[0] << 8) + DATA_CRC[1];
    uint16_t data_check = CRC16(buffer, length);

    SDCARD_ASSERT(data_crc != data_check, STATUS_ERR_BAD_DATA);

    return status;
}

enum SDcard::status_t SDcard::write(size_t block, uint8_t* buffer)
{
    status = STATUS_OK; //STATUS_ERR_UNSUPPORTED_DEV;
    union Response1_t response_type1;
    //Card might be locked, check for this before attempting to write

    //Select which block to write
    if (type != TYPE_2_HC) { block <<= 9; }
    CMD24[1] = block >> 24;
    CMD24[2] = block >> 16 & 0xFF;
    CMD24[3] = block >> 8 & 0xFF;
    CMD24[4] = block & 0xFF;

    //Ask the card to receive the requested block
    status = _command(CMD24);
    SDCARD_ASSERT_OK(status);
    status = _response(response_type1.bytes, SD_RESPONSE_R1_SIZE, false);
    SDCARD_ASSERT_OK(status);

    SDCARD_ASSERT(response_type1.R1.in_idle_state, STATUS_ERR_PROTOCOL);

    for (size_t i = 0; i < length; ++i) //!!! Writes whole block instead of just buffer length
    {
        bus.beginTransaction(settings); //Might be able to move this out of the for loop?
        bus.transfer(buffer[i]);
        bus.endTransaction();
    }
    //See Arduino Code for this section, involves waiting for not busy

    return status;
}

#pragma endregion
//----------------------------------------------------------------------------------
#pragma region //Internal Methods

enum SDcard::status_t SDcard::_command(uint8_t* command)
{
    status = STATUS_OK;
    uint16_t commandWord = 0x00;
    uint16_t responseWord = 0x00;
  
    //Send Command
    for (size_t i = 0; i < SDCARD_CMD_SIZE; ++i)
    {
        commandWord = command[i];
        bus.beginTransaction(settings);
        responseWord = bus.transfer(commandWord);
        bus.endTransaction();
    }
    //bus.beginTransaction(settings);
    //responseWord = bus.transfer(0x00); //Might only be necessary without endTransaction
    //bus.endTransaction();
    return status;
}

enum SDcard::status_t SDcard::_response(uint8_t* response, uint16_t length, bool check_valid)
{
    status = STATUS_OK;
    uint16_t responseWord = 0;
    
    SDCARD_ASSERT(((response == 0) || (length == 0)), STATUS_ERR_BAD_ADDRESS);

    //Check for a valid response
    if (check_valid)
    {
        for (size_t i = 1; i <= SDCARD_RETRY_LIMIT; ++i)
        {
            bus.beginTransaction(settings);
            responseWord = bus.transfer(SD_RESPONSE_INVALID);
            bus.endTransaction();
            if (!(responseWord & SD_RESPONSE_VALID_MASK))
            {
                response[0] = responseWord & 0xFF;
                break;
            }
            delay(SDCARD_RESPONSE_DELAY);
        }
    }

    //Receive additional bytes
    for (size_t i = (check_valid) ? 1 : 0; i < length; ++i)
    {
        bus.beginTransaction(settings);
        responseWord = bus.transfer(SD_RESPONSE_INVALID);
        bus.endTransaction();
        response[i] = responseWord & 0xFF;
    }

    return status;
}

enum SDcard::status_t SDcard::_read_OCR()
{
    status = STATUS_OK;
    union Response3_t response_type3;

    //Ask card to send OCR Register
    status = _command(CMD58);
    SDCARD_ASSERT_OK(status);
    status = _response(response_type3.bytes, SD_RESPONSE_R3_SIZE, true);
    SDCARD_ASSERT_OK(status);

    SDCARD_ASSERT(response_type3.R3.R1.in_idle_state, STATUS_ERR_PROTOCOL);

    OCR.OCR = response_type3.R3.OCR;
    SDCARD_ASSERT(!response_type3.R3.OCR.card_power_up_status_busy, STATUS_BUSY);
    if ((type == TYPE_2) && (response_type3.R3.OCR.card_capacity_status)) { type = TYPE_2_HC; }

    
    Serial.println("Checking OCR Registers");
    Serial.print(F("switch_1_8_V_accepted: ")); Serial.println(response_type3.R3.OCR.switch_1_8_V_accepted);
    Serial.print(F("reserved1: ")); Serial.println(response_type3.R3.OCR.reserved1);
    Serial.print(F("uhs2_card_status: ")); Serial.println(response_type3.R3.OCR.uhs2_card_status);
    Serial.print(F("card_capacity_status: ")); Serial.println(response_type3.R3.OCR.card_capacity_status);
    Serial.print(F("card_power_up_status_busy: ")); Serial.println(response_type3.R3.OCR.card_power_up_status_busy);
    Serial.print(F("_2_8_V_to_2_9_V: ")); Serial.println(response_type3.R3.OCR._2_8_V_to_2_9_V);
    Serial.print(F("_2_9_V_to_3_0_V: ")); Serial.println(response_type3.R3.OCR._2_9_V_to_3_0_V);
    Serial.print(F("_3_0_V_to_3_1_V: ")); Serial.println(response_type3.R3.OCR._3_0_V_to_3_1_V);
    Serial.print(F("_3_1_V_to_3_2_V: ")); Serial.println(response_type3.R3.OCR._3_1_V_to_3_2_V);
    Serial.print(F("_3_2_V_to_3_3_V: ")); Serial.println(response_type3.R3.OCR._3_2_V_to_3_3_V);
    Serial.print(F("_3_3_V_to_3_4_V: ")); Serial.println(response_type3.R3.OCR._3_3_V_to_3_4_V);
    Serial.print(F("_3_4_V_to_3_5_V: ")); Serial.println(response_type3.R3.OCR._3_4_V_to_3_5_V);
    Serial.print(F("_3_5_V_to_3_6_V: ")); Serial.println(response_type3.R3.OCR._3_5_V_to_3_6_V);
    Serial.print(F("reserved2: ")); Serial.println(response_type3.R3.OCR.reserved2);
    Serial.print(F("_2_7_V_to_2_8_V: ")); Serial.println(response_type3.R3.OCR._2_7_V_to_2_8_V);
    Serial.print(F("reserved3: ")); Serial.println(response_type3.R3.OCR.reserved3);
    Serial.print(F("reserved_low_voltage: ")); Serial.println(response_type3.R3.OCR.reserved_low_voltage);
    Serial.println();

    return status;
}

enum SDcard::status_t SDcard::_read_CSD()
{
    status = STATUS_OK;
    union Response1_t response_type1;
    uint8_t CSD_CRC[2] = {0, 0};

    //Ask card to send CSD Register
    status = _command(CMD9);
    SDCARD_ASSERT_OK(status);
    status = _response(response_type1.bytes, SD_RESPONSE_R1_SIZE, true);
    SDCARD_ASSERT_OK(status);

    SDCARD_ASSERT(response_type1.R1.in_idle_state, STATUS_ERR_PROTOCOL);

    status = _response(CSD.bytes, SD_REGISTER_CSD_SIZE, true);
    SDCARD_ASSERT_OK(status);
    status = _response(CSD_CRC, 2, false);
    SDCARD_ASSERT_OK(status); //TODO: There might not actually be a CRC sent if CRC is off in the card!
    //TODO: Check the CRC here?

    Serial.println("Checking CSD Registers");
    Serial.print(F("reserved1: ")); Serial.println(CSD.V2.reserved1);
    Serial.print(F("csd_structure: ")); Serial.println(CSD.V2.csd_structure);
    Serial.print(F("taac: ")); Serial.println(CSD.V2.taac);
    Serial.print(F("nsac: ")); Serial.println(CSD.V2.nsac);
    Serial.print(F("tran_speed: ")); Serial.println(CSD.V2.tran_speed);
    Serial.print(F("ccc_high: ")); Serial.println(CSD.V2.ccc_high);
    Serial.print(F("read_bl_len: ")); Serial.println(CSD.V2.read_bl_len);
    Serial.print(F("ccc_low: ")); Serial.println(CSD.V2.ccc_low);
    Serial.print(F("reserved2: ")); Serial.println(CSD.V2.reserved2);
    Serial.print(F("dsr_imp: ")); Serial.println(CSD.V2.dsr_imp);
    Serial.print(F("read_blk_misalign: ")); Serial.println(CSD.V2.read_blk_misalign);
    Serial.print(F("c_size_high: ")); Serial.println(CSD.V2.c_size_high);
    Serial.print(F("reserved3: ")); Serial.println(CSD.V2.reserved3);
    Serial.print(F("c_size_mid: ")); Serial.println(CSD.V2.c_size_mid);
    Serial.print(F("c_size_low: ")); Serial.println(CSD.V2.c_size_low);
    Serial.print(F("sector_size_high: ")); Serial.println(CSD.V2.sector_size_high);
    Serial.print(F("erase_blk_en: ")); Serial.println(CSD.V2.erase_blk_en);
    Serial.print(F("reserved4: ")); Serial.println(CSD.V2.reserved4);
    Serial.print(F("wp_grp_size: ")); Serial.println(CSD.V2.wp_grp_size);
    Serial.print(F("sector_size_low: ")); Serial.println(CSD.V2.sector_size_low);
    Serial.print(F("write_bl_len_high: ")); Serial.println(CSD.V2.write_bl_len_high);
    Serial.print(F("r2w_factor: ")); Serial.println(CSD.V2.r2w_factor);
    Serial.print(F("reserved5: ")); Serial.println(CSD.V2.reserved5);
    Serial.print(F("wp_grp_enable: ")); Serial.println(CSD.V2.wp_grp_enable);
    Serial.print(F("reserved6: ")); Serial.println(CSD.V2.reserved6);
    Serial.print(F("write_partial: ")); Serial.println(CSD.V2.write_partial);
    Serial.print(F("write_bl_len_low: ")); Serial.println(CSD.V2.write_bl_len_low);
    Serial.print(F("reserved7: ")); Serial.println(CSD.V2.reserved7);
    Serial.print(F("file_format: ")); Serial.println(CSD.V2.file_format);
    Serial.print(F("tmp_write_protect: ")); Serial.println(CSD.V2.tmp_write_protect);
    Serial.print(F("perm_write_protect: ")); Serial.println(CSD.V2.perm_write_protect);
    Serial.print(F("copy: ")); Serial.println(CSD.V2.copy);
    Serial.print(F("file_format_grp: ")); Serial.println(CSD.V2.file_format_grp);
    Serial.print(F("always1: ")); Serial.println(CSD.V2.always1);
    Serial.print(F("crc: ")); Serial.println(CSD.V2.crc);
    Serial.println();

    //Calculate SD card capacity from CSD data
    if (type >= TYPE_2)
    {
        SDCARD_ASSERT(!CSD.V2.always1, STATUS_ERR_PROTOCOL);

        length = 512; //Size of 1 Block //TODO: Add support for block lengths >512?
        capacity = ((CSD.V2.c_size_high << 16)
        | (CSD.V2.c_size_mid << 8)
        | (CSD.V2.c_size_low + 1)) * length;
        Serial.print("CapacityRaw: "); Serial.println((float)((CSD.V2.c_size_mid << 8) | (CSD.V2.c_size_low + 1)) * 512.0);
        //Error: Capacity incorrectly reports as 0
        capacity = (size_t)(((float)((CSD.V2.c_size_mid << 8) | (CSD.V2.c_size_low + 1)) * 512.0) / 1024.0 / 1024.0);
    }
    else if (type == TYPE_1)
    {
        SDCARD_ASSERT(!CSD.V1.always1, STATUS_ERR_PROTOCOL);

        length = 2 << (CSD.V1.read_bl_len - 1);
        uint16_t c_size = (CSD.V1.c_size_high << 10)
        | (CSD.V1.c_size_mid << 2)
        | (CSD.V1.c_size_low + 1);
        uint8_t c_size_mult = 2 << (CSD.V1.c_size_mult_high << 1)
        | (CSD.V1.c_size_mult_low + 1);
        capacity = c_size * c_size_mult;
    }
    else { status = STATUS_ERR_UNSUPPORTED_DEV; return status; }

    return status;
}

enum SDcard::status_t SDcard::_read_CID()
{
    status = STATUS_OK;
    union Response1_t response_type1;

    //Ask card to send CID Register
    status = _command(CMD10);
    SDCARD_ASSERT_OK(status);
    status = _response(response_type1.bytes, SD_RESPONSE_R1_SIZE, true);
    SDCARD_ASSERT_OK(status);

    SDCARD_ASSERT(response_type1.R1.in_idle_state, STATUS_ERR_PROTOCOL);

    //Read the CID Register
    status = _response(CID.bytes, SD_REGISTER_CID_SIZE, true);
    SDCARD_ASSERT_OK(status);

    SDCARD_ASSERT(!CID.CID.always1, STATUS_ERR_PROTOCOL);

    //TODO: Check CRC

    Serial.println("Checking CID Registers");
    Serial.print(F("manufacturer_id: ")); Serial.println(CID.CID.manufacturer_id);
    Serial.print(F("application_id_high: ")); Serial.println(CID.CID.application_id_high);
    Serial.print(F("application_id_low: ")); Serial.println(CID.CID.application_id_low);
    Serial.print(F("product_name[0]: ")); Serial.println((char)CID.CID.product_name[0]);
    Serial.print(F("product_name[1]: ")); Serial.println((char)CID.CID.product_name[1]);
    Serial.print(F("product_name[2]: ")); Serial.println((char)CID.CID.product_name[2]);
    Serial.print(F("product_name[3]: ")); Serial.println((char)CID.CID.product_name[3]);
    Serial.print(F("product_name[4]: ")); Serial.println((char)CID.CID.product_name[4]);
    Serial.print(F("product_revision: ")); Serial.println(CID.CID.product_revision);
    Serial.print(F("product_serial_number[0]: ")); Serial.println(CID.CID.product_serial_number[0]);
    Serial.print(F("product_serial_number[1]: ")); Serial.println(CID.CID.product_serial_number[1]);
    Serial.print(F("product_serial_number[2]: ")); Serial.println(CID.CID.product_serial_number[2]);
    Serial.print(F("product_serial_number[3]: ")); Serial.println(CID.CID.product_serial_number[3]);
    Serial.print(F("manufacturing_date_high: ")); Serial.println(CID.CID.manufacturing_date_high);
    Serial.print(F("reserved1: ")); Serial.println(CID.CID.reserved1);
    Serial.print(F("manufacturing_date_low: ")); Serial.println(CID.CID.manufacturing_date_low);
    Serial.print(F("always1: ")); Serial.println(CID.CID.always1);
    Serial.print(F("crc7: ")); Serial.println(CID.CID.crc7);
    Serial.println();

    return status;
}

enum SDcard::status_t SDcard::_read_SCR()
{
    status = STATUS_OK;
    union Response1_t response_type1;

    //Enter ACMD Mode
    status = _command(ACMD);
    SDCARD_ASSERT_OK(status);
    status = _response(response_type1.bytes, SD_RESPONSE_R1_SIZE, true);
    SDCARD_ASSERT_OK(status);

    //Ask card to send SCR Register
    status = _command(ACMD51);
    SDCARD_ASSERT_OK(status);
    status = _response(response_type1.bytes, SD_RESPONSE_R1_SIZE, true);
    SDCARD_ASSERT_OK(status);

    SDCARD_ASSERT(response_type1.R1.in_idle_state, STATUS_ERR_PROTOCOL);

    //Read the SCR Register
    status = _response(SCR.bytes, SD_REGISTER_SCR_SIZE, true);
    SDCARD_ASSERT_OK(status);

    //TODO: Check CRC

    Serial.println("Checking SCR Registers");
    Serial.print(F("sd_spec: ")); Serial.println(SCR.SCR.sd_spec);
    Serial.print(F("scr_structure: ")); Serial.println(SCR.SCR.scr_structure);
    Serial.print(F("sd_bus_widths: ")); Serial.println(SCR.SCR.sd_bus_widths);
    Serial.print(F("sd_security: ")); Serial.println(SCR.SCR.sd_security);
    Serial.print(F("data_stat_after_erase: ")); Serial.println(SCR.SCR.data_stat_after_erase);
    Serial.print(F("sd_specx_high: ")); Serial.println(SCR.SCR.sd_specx_high);
    Serial.print(F("sd_spec4: ")); Serial.println(SCR.SCR.sd_spec4);
    Serial.print(F("ex_security: ")); Serial.println(SCR.SCR.ex_security);
    Serial.print(F("sd_spec3: ")); Serial.println(SCR.SCR.sd_spec3);
    Serial.print(F("cmd_support: ")); Serial.println(SCR.SCR.cmd_support);
    Serial.print(F("reserved1: ")); Serial.println(SCR.SCR.reserved1);
    Serial.print(F("sd_specx_low: ")); Serial.println(SCR.SCR.sd_specx_low);
    Serial.print(F("reserved2[0]: ")); Serial.println(SCR.SCR.reserved2[0]);
    Serial.print(F("reserved2[1]: ")); Serial.println(SCR.SCR.reserved2[1]);
    Serial.print(F("reserved2[2]: ")); Serial.println(SCR.SCR.reserved2[2]);
    Serial.print(F("reserved2[3]: ")); Serial.println(SCR.SCR.reserved2[3]);
    Serial.println();

    uint8_t spec = SCR.SCR.sd_spec;
    uint8_t spec3 = SCR.SCR.sd_spec3;
    uint8_t spec4 = SCR.SCR.sd_spec4;
    uint8_t specx = (SCR.SCR.sd_specx_high << 8) + SCR.SCR.sd_specx_low;

    if ((spec == 2) && (spec3 == 1) && ((spec4 == 0) || (spec4 == 1)) && (specx == 2))
    {
        version = VERSION_6_XX;
    }
    else if ((spec == 2) && (spec3 == 1) && ((spec4 == 0) || (spec4 == 1)) && (specx == 1))
    {
        version = VERSION_5_XX;
    }
    else if ((spec == 2) && (spec3 == 1) && (spec4 == 1) && (specx == 0))
    {
        version = VERSION_4_XX;
    }
    else if ((spec == 2) && (spec3 == 1) && (spec4 == 0) && (specx == 0))
    {
        version = VERSION_3_0X;
    }
    else if ((spec == 2) && (spec3 == 0) && (spec4 == 0) && (specx == 0))
    {
        version = VERSION_2_00;
    }
    else if ((spec == 1) && (spec3 == 0) && (spec4 == 0) && (specx == 0))
    {
        version = VERSION_1_10;
    }
    else if ((spec == 0) && (spec3 == 0) && (spec4 == 0) && (specx == 0))
    {
        version = VERSION_1_0X;
    }
    else { version = VERSION_UNKNOWN; }

    return status;
}

#pragma endregion
//----------------------------------------------------------------------------------

//TODO: FAT32 Volume stuff, separate library on top of Arduino SD Volume
