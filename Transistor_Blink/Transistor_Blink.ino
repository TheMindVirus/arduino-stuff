//CNY17 Opto-Isolator + Reed Relay

#define PIN_COLLECTOR    9
#define PIN_BASE        10
#define PIN_EMITTER     A5

#define BLINK_RATE     500
#define BLINK_RATE_X2 1000

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);

    pinMode(PIN_COLLECTOR, OUTPUT);
    pinMode(PIN_BASE, OUTPUT);
    pinMode(PIN_EMITTER, INPUT_PULLUP);

    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(PIN_COLLECTOR, HIGH);
    analogWrite(PIN_BASE, 0);
    //analogRead(PIN_EMITTER);
}

unsigned int T = 0; //!!! To Prevent 50/50 Timer Failure (32s)
//int = T = 0;
int M = 0;
int V = 0;

//unsigned int C = 0;
int C = 0; //!!! For Saw Wave Diagnostics in Serial Plotter
int B = 0;
int E = 0;

void loop()
{
    T = millis(); //if (T < 0) { T += 65,535 or MAX_INT; }
    if ((!M) && ((T % (BLINK_RATE_X2)) < BLINK_RATE))
    {
        M = true;
        V = !V;
        analogWrite(PIN_BASE, V * 127);
    }
    else if ((M) && ((T % (BLINK_RATE_X2)) >= BLINK_RATE))
    {
        M = false;
    }

    C = T;
    B = V * 255;
    E = analogRead(PIN_EMITTER);
    Serial.print("C:"); Serial.print(C); Serial.print(",");
    Serial.print("B:"); Serial.print(B); Serial.print(",");
    Serial.print("E:"); Serial.print(E); Serial.println();
    delay(10);
}
