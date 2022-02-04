#include "SDcard.h"

#define SD_CS_PIN    4
#define NET_CS_PIN   10

#define HIGH_N LOW //Disabled Active-Low
#define LOW_N HIGH //Enabled Active-Low

SDcard card;

static inline void abort_testing()
{
    Serial.println("Aborting Testing");
    while (true);
}

static inline void query_testing()
{
    Serial.println("WARNING: THE FOLLOWING PROCEDURE WILL CAUSE DATA LOSS!");
    Serial.println("Enter \"Y\" to continue");
    while (!Serial.available()) {}
    char c = Serial.read();
    if (c != 'Y') { abort_testing(); }
    while (Serial.available() > 0) { Serial.read(); }
}

static inline void delay_testing(size_t seconds)
{
    while (Serial.available() > 0) { Serial.read(); }
    Serial.println("Send anything to abort countdown");
    Serial.print("Commencing Testing in ");
    for (size_t i = seconds; i > 0; --i)
    {
        Serial.print(i);
        Serial.print(" ");
        delay(1000);
        if (Serial.available() > 2) { abort_testing(); } //Why is /r/n there?
    }
    Serial.println();
}

static inline void dump_block(SDcard& crd, uint8_t* buffer)
{
    size_t columns = 16;
    char tmp[4] = "00 ";
    for (size_t i = 0; i < card.length; ++i)
    {
        sprintf(tmp, "%02X ", buffer[i]); Serial.print(tmp);
        if ((i % columns) == (columns - 1)) { Serial.print(" | 0x"); Serial.println((i + 1) - columns, HEX); }
    }
    Serial.println();
}

void setup()
{
    pinMode(SD_CS_PIN, OUTPUT);
    pinMode(NET_CS_PIN, OUTPUT);
    digitalWrite(SD_CS_PIN, HIGH_N); //Enabled
    digitalWrite(NET_CS_PIN, LOW_N); //Disabled
    
    Serial.begin(9600);
    Serial.println();
    Serial.println("__Raw_SDcard_Test__");
    SPI.begin();
    card.begin(SPI);
    
    if (card.status != card.STATUS_OK)
    {
        Serial.print("SD Card Error. Check Wiring, Re-Insert the Card and Press Reset. Status: 0x");
        Serial.println(card.status, HEX);
        while (true);
    }
    
    //Print information about the card
    Serial.print("Type: 0x");
    Serial.println(card.type, HEX);
    Serial.print("Version: 0x");
    Serial.println(card.version, HEX);
    Serial.print("Length: 0x");
    Serial.println(card.length, HEX);
    Serial.print("Capacity: 0x");
    Serial.println(card.capacity, HEX);
      
    if (card.length != 512)
    {
        Serial.print("Invalid Block Size ");
        Serial.print(card.length);
        Serial.print(". Check Wiring and Re-Insert the Card. Status: 0x");
        Serial.println(card.status, HEX);
        while (true);
    }

    query_testing();
    delay_testing(5);

    Serial.println("SOMETHING");
        
    //uint8_t read_buffer[card.length] = "";
    //uint8_t write_buffer[card.length] = ""; //"Something"; //Arduino doesn't like this...
    //uint8_t temp_buffer[card.length] = "";

    uint8_t buffer1[card.length + 1];
    uint8_t buffer2[card.length + 1];
    for (size_t i = 0; i < card.length; ++i) { buffer2[i] = 0xFF; }

    delay(1000); //Allow Allocation Time?
      
    //Attempt a block read and store it in temporary memory
    Serial.println("[TEST]: Read");
    card.read(0, buffer1);
    //strncpy(temp_buffer, read_buffer, card.length); //or this...
    //memcpy(temp_buffer, read_buffer, card.length); //or this???
    //for (size_t i = 0; i < card.length; ++i) { temp_buffer[i] = read_buffer[i]; }
    dump_block(card, buffer1);

    delay(1000);
    /*    
    //Attempt a temporary block write followed by a read
    Serial.println("[TEST]: Write");
    //card.write(0, buffer2);
    delay(1000); //Allow the card to settle
    card.read(0, buffer1);
    dump_block(card, buffer1);

    delay(1000);

    //Restore the block to its original contents and verify with a read
    Serial.println("[TEST]: Verify");
    //card.write(0, buffer1);
    card.read(0, buffer2);
    dump_block(card, buffer2);

    delay(1000);
    */
    Serial.println("[TEST]: Complete");
}

void loop(){}
