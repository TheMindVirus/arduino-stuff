#include <SPI.h>

//[SPI Pinout]

//4 - RES
//5 - DC
//6 - CS / SS
//7 - BL

//8 - VGND
//9 - VVCC
//10 - (SS n/c)
//11 - MOSI / "SDA"
//12 - (MISO n/c)
//13 - SCK / "SCL"

//!!! Display has markings for I2C but actually initialises using Software SPI, then switches to Hardware SPI
//!!! Try using GPIO pin for filtered ground instead of using unfiltered GND pins if there are black bars
//!!! In which case, the display acts as a sort of USB Line Noise Visualiser

const uint8_t Rcmd[] PROGMEM =
{
    0x18,
    0x11, 0x80, 0x96,
    0x11, 0x80, 0xFF,
    0xB1, 0x03, 0x01, 0x01, 0x01,
    0xB2, 0x03, 0x01, 0x01, 0x01,
    0xB3, 0x06, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0xB4, 0x01, 0x07,
    0xC0, 0x03, 0xA2, 0x02, 0x84,
    0xC1, 0x01, 0xC5,
    0xC2, 0x02, 0x0A, 0x00,
    0xC3, 0x02, 0x8A, 0x2A,
    0xC4, 0x02, 0x8A, 0xEE,
    0xC5, 0x01, 0x0E,
    0x20, 0x00,
    0x36, 0x01, 0xC8,
    0x3A, 0x01, 0x05,
    0x2A, 0x04, 0x00, 0x01, 0x00, 0xA0,
    0x2B, 0x04, 0x00, 0x02, 0x00, 0x81,
    0xE0, 0x10, 0x02, 0x1C, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2D, 0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10,
    0xE1, 0x10, 0x03, 0x1D, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D, 0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10,
    0x13, 0x80, 0x0A,
    0x29, 0x80, 0x64,
    0x36, 0x01, 0xC0,
    0x36, 0x01, 0xA0,
    0x2C, 0x00
};

void spi_write(uint8_t b)
{
    asm volatile
    (
        "sbrc %0, 7" "\n" "sbi %1, %2" "\n"
        "sbrs %0, 7" "\n" "cbi %1, %2" "\n"
        "sbi %3, %4" "\n" "cbi %3, %4" "\n"

        "sbrc %0, 6" "\n" "sbi %1, %2" "\n"
        "sbrs %0, 6" "\n" "cbi %1, %2" "\n"
        "sbi %3, %4" "\n" "cbi %3, %4" "\n"

        "sbrc %0, 5" "\n" "sbi %1, %2" "\n"
        "sbrs %0, 5" "\n" "cbi %1, %2" "\n"
        "sbi %3, %4" "\n" "cbi %3, %4" "\n"

        "sbrc %0, 4" "\n" "sbi %1, %2" "\n"
        "sbrs %0, 4" "\n" "cbi %1, %2" "\n"
        "sbi %3, %4" "\n" "cbi %3, %4" "\n"

        "sbrc %0, 3" "\n" "sbi %1, %2" "\n"
        "sbrs %0, 3" "\n" "cbi %1, %2" "\n"
        "sbi %3, %4" "\n" "cbi %3, %4" "\n"

        "sbrc %0, 2" "\n" "sbi %1, %2" "\n"
        "sbrs %0, 2" "\n" "cbi %1, %2" "\n"
        "sbi %3, %4" "\n" "cbi %3, %4" "\n"

        "sbrc %0, 1" "\n" "sbi %1, %2" "\n"
        "sbrs %0, 1" "\n" "cbi %1, %2" "\n"
        "sbi %3, %4" "\n" "cbi %3, %4" "\n"

        "sbrc %0, 0" "\n" "sbi %1, %2" "\n"
        "sbrs %0, 0" "\n" "cbi %1, %2" "\n"
        "sbi %3, %4" "\n" "cbi %3, %4" "\n"
        
        : "+r" (b) : "i" (0x05), "i" (3), "i" (0x05), "i" (5) :
    );
}

void send_command(uint8_t cmd, uint8_t* addr = 0, size_t na = 0)
{
     digitalWrite(6, LOW);
     digitalWrite(5, LOW);
     //SPI.transfer(cmd);
     spi_write(cmd);
     digitalWrite(5, HIGH);
     //for (size_t i = 0; i < na; ++i) { SPI.transfer(pgm_read_byte(addr + i)); }
     for (size_t i = 0; i < na; ++i) { spi_write(pgm_read_byte(addr + i)); }
     digitalWrite(6, HIGH);
}

void start_display(uint8_t* commands)
{
    size_t idx = 0;
    size_t nc = pgm_read_byte(commands + idx++);
    size_t na = 0;
    size_t ms = 0;
    uint8_t cmd = 0;
    for (size_t i = 0; i < nc; ++i)
    {
        cmd = pgm_read_byte(commands + idx++);
        na = pgm_read_byte(commands + idx++);
        ms = na & 0x80;
        na &= 0x7F;
        send_command(cmd, commands + idx, na);
        idx += na;
        if (ms)
        {
            ms = pgm_read_byte(commands + idx++);
            if (ms == 0xFF) { ms = 500; }
            delay(ms);
        }
    }
}

void setup()
{
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);

    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, INPUT);
    pinMode(13, OUTPUT);

    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);

    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(13, LOW);

    digitalWrite(1, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(7, HIGH);
    delay(100);
    digitalWrite(4, LOW);
    delay(100);
    digitalWrite(4, HIGH);
    delay(200);
    digitalWrite(6, HIGH);
    
    //Serial.begin(115200);

    start_display(Rcmd);
    
    digitalWrite(6, LOW);
    SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));
    for (int i = 0; i < 20480; ++i)
    {  
        SPI.transfer(0xF8);
        SPI.transfer(0x00);
    }
    SPI.endTransaction();
    digitalWrite(6, HIGH);

    SPI.end();
    
    digitalWrite(5, LOW);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);

    digitalWrite(4, HIGH);
    
}

void loop()
{

}
