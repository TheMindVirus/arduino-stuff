void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(7, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(7, LOW);
    Serial.println("[BOOT]: Done!");
}

void loop()
{
    tone(9, 1000);
    delay(100);
    tone(9, -1);
    delay(900);
}