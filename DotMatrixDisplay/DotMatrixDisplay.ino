#include <SPI.h>

//MAXIM1513 Quad 8x8 Dot Matrix Driver
//(or potentially MAX7219CNG incorrectly labelled FC-16)
//Address Format: ((address << 8) & 0x0F) + (data & 0xFF)
//Then Data Shifts from each DOUT to each DIN

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

    0b00011000,
    0b00100100,
    0b01000010,
    0b10000001,
    0b11111111,
    0b10000001,
    0b10000001,
    0b10000001,

    0b10000001,
    0b11000011,
    0b10100101,
    0b10011001,
    0b10000001,
    0b10000001,
    0b10000001,
    0b10000001,

    0b11111111,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b11111111
};

void matrix_write(int A, int B, int C = false, int D = COLUMNS)
{
    for (int i = 0; i <= D; ++i)
    {
        digitalWrite(SS, LOW);
        SPI.transfer(A); //DIG
        SPI.transfer(B); //SEG
        digitalWrite(SS, HIGH);
        delayMicroseconds(1);
        if (C) { B = 0; }
    }
}

void matrix_reset(uint8_t intensity = 0xF)
{
    matrix_write(0x0C, 0x00); //Shutdown Mode
    matrix_write(0x0C, 0x01); //Normal Operation
    matrix_write(0x09, 0x00); //No Decode
    matrix_write(0x0A, max(intensity, 0x0F)); //Intensity
    matrix_write(0x0B, 0x07); //Limit
}

void matrix_clear()
{
    for (int i = 0; i < HEIGHT; ++i)
    {
        matrix_write(i + 1, 0x00);
    }
}

int matrix_point(int segment)
{
    segment = pow(2, segment);
    if (segment == 1) { segment = 0; }
    else if (segment == 2) { segment = 1; }
    return segment;
}

void matrix_shift()
{
    for (int x = 0; x < COLUMNS; ++x)
    { 
        for (int y = 0; y < HEIGHT; ++y)
        {
            matrix_clear();
            int k = (x * WIDTH) + y;
            int z = matrix_buffer[k];
            matrix_write(y + 1, z, true, x);
            //delayMicroseconds(1);
            delay(10);
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
    matrix_reset();
    matrix_clear();
}

void loop()
{
    matrix_shift();
}
