void setup()
{
    Serial.begin(31250, SERIAL_8N1);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    Serial.print("\x90\x30\x7F");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    Serial.print("\x80\x30\x7F");
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}
