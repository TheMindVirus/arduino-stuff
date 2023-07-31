double a = 0.0;
int v = 0;

void setup()
{
    pinMode(3, OUTPUT);
    analogWrite(3, 0);
    Serial.begin(115200);
}

void loop()
{
    a = sin(((double)(millis() % 1000) / 1000.0) * 2.0 * PI);
    v = int(((a + 1.0) / 2.0) * 0xFF);
    //Serial.println(a);
    Serial.println(v);
    analogWrite(3, v);
    delay(10);
}
