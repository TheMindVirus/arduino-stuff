#include <SPI.h>

//MAXIM1513 Quad 8x8 Dot Matrix Driver
//(or potentially MAX7219CNG incorrectly labelled FC-16)
//Address Format: ((address << 8) & 0x0F) + (data & 0xFF)
//Then Data Shifts from each DOUT to each DIN
//and is Latched when the CS/SS Pin is brought HIGH

#define ROWS         1
#define COLUMNS      4
#define HEIGHT       8
#define WIDTH        8

//For Arduino Uno Rev.3
//SCK on LED_BUILTIN
//MOSI on Pin 11
//SS on Pin 10

int matrix_buffer[COLUMNS * WIDTH] = 
{
    0b10000001,
    0b01000010,
    0b00100100,
    0b00011000,
    0b00011000,
    0b00100100,
    0b01000010,
    0b10000001,

    0b10000001,
    0b11000011,
    0b10100101,
    0b10011001,
    0b10000001,
    0b10000001,
    0b10000001,
    0b10000001,

    0b00011000,
    0b00100100,
    0b01000010,
    0b10000001,
    0b11111111,
    0b10000001,
    0b10000001,
    0b10000001,

    0b01111110,
    0b10000001,
    0b10000000,
    0b10000000,
    0b01111110,
    0b00000001,
    0b10000001,
    0b01111110,
};

void matrix_flush(int A, int B, bool C = true, int D = COLUMNS - 1)
{
    digitalWrite(SS, LOW);
    //delayMicroseconds(10);
    for (int d = COLUMNS - 1; d >= 0; --d)
    {
        SPI.transfer((C == true) ? ((d == D) ? A : 0x00) : A); //delayMicroseconds(10);
        SPI.transfer((C == true) ? ((d == D) ? B : 0x00) : B); //delayMicroseconds(10);
    }
    digitalWrite(SS, HIGH);
    //delayMicroseconds(10);
}

void matrix_blit(int lamp = 0x0F)
{
    lamp = max(lamp, 0x0F);
    for (int d = 0; d < COLUMNS; ++d)
    {
        matrix_flush(0x0C, 0x00, true, d); //Shutdown Mode
        matrix_flush(0x0C, 0x01, true, d); //Normal Operation
        matrix_flush(0x0F, 0x01, true, d); //Test Mode On
        matrix_flush(0x0F, 0x00, true, d); //Test Mode Off
        matrix_flush(0x09, 0x00, true, d); //No Decode
        matrix_flush(0x0A, lamp, true, d); //Intensity
        matrix_flush(0x0B, 0x07, true, d); //Limit None
    }
    matrix_flush(0x00, 0x00, false);
    for (int x = 0; x < COLUMNS; ++x)
    { 
        for (int y = 0; y < HEIGHT; ++y)
        {
            int d = COLUMNS - x - 1;
            int i = (x * WIDTH) + y;
            int j = matrix_buffer[i];
            matrix_flush(y + 1, j, true, d);
            //delay(100);
        }
    }
}

void setup()
{
    pinMode(SS, OUTPUT);
    pinMode(MOSI, OUTPUT);
    pinMode(SCK, OUTPUT);
    digitalWrite(SS, HIGH);
    SPI.begin();
    Serial.begin(115200);
    Serial.println("BOOT");
    matrix_blit();
}

void loop()
{
    
}
