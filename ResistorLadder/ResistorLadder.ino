//#include <Wire.h>
#include <Adafruit_DS3502.h>

#define PIN_DS3502_RL   A0
#define PIN_DS3502_RW   A1

//byte b = '\xFF';
unsigned int T = 0;
bool V = false;
bool lock = false;

Adafruit_DS3502 DS3502 = Adafruit_DS3502();

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PIN_DS3502_RL, OUTPUT);
    pinMode(PIN_DS3502_RW, INPUT);
    Serial.begin(115200);
    //Wire.begin();
    if (!DS3502.begin()) { Serial.println("Missing DS3502"); }
    digitalWrite(PIN_DS3502_RL, HIGH);
}

void loop()
{
    /*for (byte i = 1; i < 127; ++i)
    {
        Wire.beginTransmission(i);
        b = Wire.endTransmission();
        //Serial.print(b, HEX); Serial.print(" ");
        if (b == 0) { Serial.print("0x"); Serial.println(i, HEX); }
    }
    Serial.println();*/
    
    Serial.println(analogRead(PIN_DS3502_RW));
    T = millis() % 1000;
    if ((!lock) && (T > 500))
    {
        V = !V;
        digitalWrite(LED_BUILTIN, V);
        DS3502.setWiper(V ? 127 : 63);
        lock = true;
    }
    else if ((lock) && (T < 500)) { lock = false; }
    delay(10);
}
