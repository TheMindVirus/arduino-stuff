#include <SPI.h>

//MAXIM1513 Quad 8x8 Dot Matrix Driver
//(or potentially MAX7219CNG incorrectly labelled FC-16)
//Address Format: ((address << 8) & 0x0F) + (data & 0xFF)
//Then Data Shifts from each DOUT to each DIN
//and is Latched when the CS/SS Pin is brought HIGH
//...and also has a latched Intensity Channel...

#define LENGTH       4
#define HEIGHT       8
#define WIDTH        8

//For Arduino Uno Rev.3
//SCK on LED_BUILTIN
//MOSI on Pin 11
//SS on Pin 10

const size_t max_len = 100;
char buffer[max_len] = {0};
char c = '\0';
size_t n = 0;
size_t pos = 0;
size_t interval = 10000;

const size_t matrix_size = LENGTH * HEIGHT * WIDTH;

uint8_t matrix_buffer[matrix_size] =
{
    0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F,
    0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
    0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x17, 0x17, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x17, 0x17, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
    0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F,

    0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F,
    0x00, 0x19, 0x00, 0x00, 0x00, 0x00, 0x19, 0x00,
    0x00, 0x00, 0x16, 0x00, 0x00, 0x16, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x13, 0x13, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x14, 0x14, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x19, 0x19, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x00,

    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F,

    0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F,
    0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F,
    0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F,
    0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F,
    0x1F, 0x00, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x1F,
    0x1F, 0x00, 0x17, 0x00, 0x00, 0x17, 0x00, 0x1F,
    0x1F, 0x17, 0x00, 0x00, 0x00, 0x00, 0x17, 0x1F,
    0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F
};

void matrix_write(uint8_t digit, uint8_t segment, size_t device = LENGTH - 1)
{
    digitalWrite(SS, LOW);
    delayMicroseconds(10);
    for (size_t d = LENGTH; d > 0; --d)
    {
        SPI.transfer((device == (d - 1)) ?   digit : 0x00); //delayMicroseconds(10);
        SPI.transfer((device == (d - 1)) ? segment : 0x00); delayMicroseconds(10);
    }
    digitalWrite(SS, HIGH);
    delayMicroseconds(10);
}

void matrix_flush(uint8_t command = 0x00, uint8_t data = 0x00)
{
    digitalWrite(SS, LOW);
    delayMicroseconds(10);
    for (size_t d = LENGTH; d > 0; --d)
    {
        SPI.transfer(command); delayMicroseconds(10);
        SPI.transfer(data); delayMicroseconds(10);
    }
    digitalWrite(SS, HIGH);
    delayMicroseconds(10);
}

void matrix_setup()
{
    for (size_t d = 0; d < LENGTH; ++d)
    {
        matrix_write(0x0C, 0x00, d); //Shutdown Mode
        matrix_write(0x0C, 0x01, d); //Normal Operation
        matrix_write(0x0F, 0x01, d); //Test Mode On
        matrix_write(0x0F, 0x00, d); //Test Mode Off
        matrix_write(0x09, 0x00, d); //No Decode
        matrix_write(0x0A, 0x0F, d); //Max Intensity
        matrix_write(0x0B, 0x07, d); //Limit None
    }
    matrix_flush();
}

uint8_t matrix_point(size_t x, size_t j)
{
    uint8_t y = pow(2, x);
    if (x == 0) { y = 0; }
    else if (x == 1) { y = 1; }
    if (((j >> 4) & 0x0F) > 0x00) { return y + 1; }
    else { return 0x00; }
}

size_t matrix_index(size_t x, size_t y, size_t z)
{
    return (z * HEIGHT * WIDTH) + (y * WIDTH) + (WIDTH - x - 1);
}

void matrix_loop()
{
    for (size_t z = 0; z < LENGTH; ++z)
    { 
        for (size_t y = 0; y < HEIGHT; ++y)
        {
            for (size_t x = 0; x < WIDTH; ++x)
            {
                size_t d = (LENGTH - z) - 1;
                size_t i = matrix_index(x, y, z);
                uint8_t j = matrix_buffer[i];
                uint8_t lamp = j & 0x0F;
                uint8_t bulb = matrix_point(x, j);
                matrix_write(0x0A, lamp, d);
                matrix_write(y +1, bulb, d);              
                delayMicroseconds(interval);
                matrix_write(y +1, 0x00, d); 
            }
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
    matrix_setup();
}

void loop()
{
    matrix_loop();
    n = Serial.available();
    for (size_t i = 0; i < n; ++i)
    {
        c = Serial.read();
        if ((c >= 32) && (c < 127))
        {
            buffer[pos] = c;
            ++pos;
        }
        if (c == '\n')
        {
            interval = atoi(buffer);
            Serial.println(interval);
            for (size_t j = 0; j < max_len; ++j)
            {
                buffer[j] = 0;
            }
            pos = 0;
        }
    }
}
