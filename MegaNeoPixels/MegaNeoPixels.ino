//MegaNeoPixels.ino by Alastair Cota - 31/03/2021
//  Intended for use with an Arduino Mega2560 and Adafruit NeoPixel Shield
//  Serial Format: RRGGBB\r\n (e.g. FFFFFF + \r\n = { r: 255, g: 255, b: 255 }; )
//  The Serial plotter shows the active colour graphically in BRG format.
//  The Arduino makes an attempt to remember the last colour it was set to,
//  but it may take a while for it to boot initially.

#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

#define PIN_PIXELS     6
#define NUM_PIXELS    40
#define MAX_LENGTH     8

char data[MAX_LENGTH];
size_t ptr;
byte r, g, b;

Adafruit_NeoPixel pixels(NUM_PIXELS, PIN_PIXELS,
                         NEO_GRB + NEO_KHZ800);

byte hexmap(char data1, char data2);
void pixels_update();
void serial_parse();
void serial_plot();

void setup()
{
    r = EEPROM.read(0);
    g = EEPROM.read(1);
    b = EEPROM.read(2);
    for (size_t i = 0; i < MAX_LENGTH; ++i) { data[i] = '0'; }
    Serial.begin(115200);
    pixels.begin();
    pixels_update();
}

void loop()
{
    pixels_update();
    serial_parse();
    serial_plot();
    delay(10);
}

void pixels_update()
{
    pixels.clear();
    for (size_t i = 0; i < NUM_PIXELS; ++i)
    {
        pixels.setPixelColor(i, pixels.Color(r, g, b));
    }
    pixels.show();
}

void serial_parse()
{
    if (Serial.available() > 0)
    {
        data[ptr] = Serial.read();
        if (data[ptr] == '\n')
        {
            r = hexmap(data[0], data[1]);
            g = hexmap(data[2], data[3]);
            b = hexmap(data[4], data[5]);
            EEPROM.write(0, r);
            EEPROM.write(1, g);
            EEPROM.write(2, b);
            for (size_t i = 0; i < MAX_LENGTH; ++i) { data[i] = '0'; }
            ptr = 0;
        }
        else if (ptr < MAX_LENGTH) { ++ptr; }
    }
}

void serial_plot()
{
    Serial.print("b:");
    Serial.print(b);
    Serial.print(", r:");
    Serial.print(r);
    Serial.print(", g:");
    Serial.print(g);
    Serial.println();
}

byte hexmap(char data1, char data2)
{
    data1 -= (data1 < 58) ? 48 : 55;
    data2 -= (data2 < 58) ? 48 : 55;
    return (data1 << 4) | data2;
}
