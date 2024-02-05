//COTO9007-50-00 Reed Relay

#define REED_CAP_POS   A1 //
#define REED_IND_POS   A2 //Base
#define REED_IND_NEG   A3
#define REED_CAP_NEG   A4

void setup() 
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    pinMode(REED_CAP_POS, OUTPUT);
    pinMode(REED_IND_POS, OUTPUT);
    pinMode(REED_IND_NEG, OUTPUT);
    pinMode(REED_CAP_NEG, INPUT_PULLUP);

    digitalWrite(REED_CAP_POS, HIGH);
    digitalWrite(REED_IND_POS, LOW);
    digitalWrite(REED_IND_NEG, LOW);
    //digitalReed(READ_CAP_NEG);
}

void loop() 
{
    Serial.println("Charging Reed...");
    digitalWrite(REED_IND_POS, HIGH);
    delay(1000);
    Serial.println("Reading Reed...");
    Serial.println(analogRead(REED_CAP_NEG));
    delay(1000);
    Serial.println("Discharging Reed...");
    digitalWrite(REED_IND_POS, LOW);
    delay(1000);
    Serial.println("Reading Reed...");
    Serial.println(analogRead(REED_CAP_NEG));
    delay(1000);
}
