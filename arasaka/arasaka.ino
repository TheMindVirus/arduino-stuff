#include <Adafruit_ST7735.h>
#include "arasaka.h"

#define PIN_GND   0
#define PIN_VCC   1
#define PIN_CLK   2
#define PIN_DAT   3
#define PIN_RST   4
#define PIN_DC    5
#define PIN_CS    6
#define PIN_BL    7

Adafruit_ST7735 display = Adafruit_ST7735(PIN_CS, PIN_DC, PIN_DAT, PIN_CLK, PIN_RST);

void setup()
{   
    Serial.begin(115200);
    Serial.println("ST7735_SPI");

    pinMode(PIN_GND, OUTPUT);
    pinMode(PIN_VCC, OUTPUT);
    pinMode(PIN_BL, OUTPUT);
    digitalWrite(PIN_GND, LOW);
    digitalWrite(PIN_VCC, HIGH);
    digitalWrite(PIN_BL, HIGH);
    
    //display.begin();
    display.initR(INITR_GREENTAB);
    display.setRotation(1);
    display.fillScreen(ST77XX_BLUE); //Turns out Red
    display.setCursor(10, 10);
    display.setTextSize(5);
    display.setTextColor(ST77XX_BLACK);
    display.println("HelloWorld(0.0)");
    //display.end();

    delay(1000);

    display.fillScreen(ST77XX_BLACK);
    display.drawBitmap(0, 0, arasaka, 160, 128, ST77XX_BLUE, ST77XX_BLACK); //Turns out Red
    
    digitalWrite(PIN_CS, LOW);
    digitalWrite(PIN_DC, LOW);
    digitalWrite(PIN_DAT, LOW);
    digitalWrite(PIN_CLK, LOW);
    digitalWrite(PIN_RST, HIGH);
}

void loop(){ delay(1000); }
