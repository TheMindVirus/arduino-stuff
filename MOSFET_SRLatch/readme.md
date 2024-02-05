# MOSFET SR-Latch (using 2x IRF-123-4G)

![MOSFET_SR-Latch](/MOSFET_SRLatch/screenshot.png)

```c++
//IRF-123 MOSFET x2 in back-to-back configuration (not push-pull)

#define MOSFET1_GATE    A0
#define MOSFET1_DRAIN   A1
#define MOSFET1_SOURCE  A2

#define MOSFET2_GATE    A3
#define MOSFET2_DRAIN   A4
#define MOSFET2_SOURCE  A5

#define BLINK_RATE     500
#define BLINK_RATE_X2 1000

#define MAX_INPUT   1024.0
#define THRESHOLD      0.1

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    pinMode(MOSFET1_GATE, OUTPUT);
    pinMode(MOSFET1_DRAIN, OUTPUT);
    pinMode(MOSFET1_SOURCE, INPUT);

    pinMode(MOSFET2_GATE, OUTPUT);
    pinMode(MOSFET2_DRAIN, OUTPUT);
    pinMode(MOSFET2_SOURCE, INPUT);

    digitalWrite(MOSFET1_GATE, LOW);
    digitalWrite(MOSFET1_DRAIN, HIGH);
    //analogRead(MOSFET1_SOURCE);

    digitalWrite(MOSFET2_GATE, LOW);
    digitalWrite(MOSFET2_DRAIN, HIGH);
    //analogRead(MOSFET2_SOURCE);
}

unsigned int T = 0;
unsigned int M = 0;
unsigned int V = 0;

double G1 = 0.0; //signed double G1 = 0.0f;
double D1 = 1.0;
double S1 = 0.0;

double G2 = 0.0;
double D2 = 1.0;
double S2 = 0.0;

void loop()
{
    T = millis();
    if ((!M) && ((T % (BLINK_RATE_X2)) < BLINK_RATE))
    {
        M = true;
        V = (V + 1) % 4;
        G1 = V == 0b01;
        G2 = V == 0b11;
    }
    else if ((M) && ((T % (BLINK_RATE_X2)) >= BLINK_RATE))
    {
        M = false;
    }
    digitalWrite(LED_BUILTIN, V % 2);
    if (V % 2)
    {
        digitalWrite(MOSFET1_GATE, (G1 > THRESHOLD) ? HIGH : LOW);
        digitalWrite(MOSFET1_DRAIN, (D1 > THRESHOLD) ? HIGH : LOW);
        S1 = analogRead(MOSFET1_SOURCE) / MAX_INPUT;
        D2 = (S1 > THRESHOLD) ? 1.0 : 0.0;
    }
    else
    {
        digitalWrite(MOSFET2_GATE, (G2 > THRESHOLD) ? HIGH : LOW);
        digitalWrite(MOSFET2_DRAIN, (D2 > THRESHOLD) ? HIGH : LOW);
        S2 = analogRead(MOSFET2_SOURCE) / MAX_INPUT;
        D1 = (S2 > THRESHOLD) ? 1.0 : 0.0;
    }
    Serial.print("G1:"); Serial.print(G1 + 0x2); Serial.print(",");
    Serial.print("D1:"); Serial.print(D1 + 0x4); Serial.print(",");
    Serial.print("S1:"); Serial.print(S1 + 0x6); Serial.print(",");
    Serial.print("G2:"); Serial.print(G2 + 0x8); Serial.print(",");
    Serial.print("D2:"); Serial.print(D2 + 0xA); Serial.print(",");
    Serial.print("S2:"); Serial.print(S2 + 0xC); Serial.println();
    delay(10);
}
```