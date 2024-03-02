//Transformer Hysteresis Proximity Sensor

#define PIN_TRANSFORMER_IN_LOW    A0
#define PIN_TRANSFORMER_IN_AUX    A1
#define PIN_TRANSFORMER_IN_TOP    A2

#define PIN_TRANSFORMER_OUT_LOW   A3
#define PIN_TRANSFORMER_OUT_AUX   A4
#define PIN_TRANSFORMER_OUT_TOP   A5

double time = 0.0;
bool lock = false;
bool toggle = false;

const size_t size = 3;
double buffer[size] = { 0.0 };

double peak = 0.0;
double kaep = 0.0;

double proximity = 0.0;
double threshold = 200.0;

void TransformerToggle(int pin)
{
    time = millis();
    if ((!lock) && (fmod(time, 1000.0) > 500.0))
    {
        lock = true;
        toggle = !toggle;
        digitalWrite(pin, toggle);
    }
    else if ((lock) && (fmod(time, 1000.0) < 500.0))
    {
        lock = false;
    }
}

void TransformerBuffer(double data)
{
    peak = 0.0;
    kaep = 9999999.0;
    for (size_t i = size - 1; i > 0; --i)
    {
        buffer[i] = buffer[i - 1];
        if (buffer[i] > peak) { peak = buffer[i]; }
        if (buffer[i] < kaep) { kaep = buffer[i]; }
    }
    buffer[0] = data;
    proximity = peak - kaep;
}

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PIN_TRANSFORMER_IN_LOW, OUTPUT);
    pinMode(PIN_TRANSFORMER_IN_AUX, OUTPUT);
    pinMode(PIN_TRANSFORMER_IN_TOP, OUTPUT);
    pinMode(PIN_TRANSFORMER_OUT_LOW, INPUT);
    pinMode(PIN_TRANSFORMER_OUT_AUX, INPUT);
    pinMode(PIN_TRANSFORMER_OUT_TOP, INPUT);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(PIN_TRANSFORMER_IN_LOW, LOW);
    digitalWrite(PIN_TRANSFORMER_IN_AUX, LOW);
    digitalWrite(PIN_TRANSFORMER_IN_TOP, LOW);
    digitalWrite(PIN_TRANSFORMER_OUT_LOW, LOW);
    digitalWrite(PIN_TRANSFORMER_OUT_AUX, LOW);
    digitalWrite(PIN_TRANSFORMER_OUT_TOP, LOW);
}

void TransformerReadout(double wait = 1.0, double top = 1024.0, double low = -1024.0)
{
    Serial.print("PROX:"); Serial.print(proximity); Serial.print(",");
    Serial.print("THRESH:"); Serial.print(proximity > threshold ? top : low); Serial.print(",");
    Serial.print("TOP:"); Serial.print(top); Serial.print(",");
    Serial.print("LOW:"); Serial.print(low); Serial.print(",");

    Serial.print("OUT_LOW:");
    Serial.print(analogRead(PIN_TRANSFORMER_OUT_LOW));
    Serial.print(",");
    Serial.print("OUT_AUX:");
    Serial.print(analogRead(PIN_TRANSFORMER_OUT_AUX));
    Serial.print(",");
    Serial.print("OUT_TOP:");
    Serial.print(analogRead(PIN_TRANSFORMER_OUT_TOP));
    Serial.println();

    digitalWrite(LED_BUILTIN, proximity > threshold ? HIGH : LOW);
    delay(wait);
}

void loop()
{
    TransformerToggle(PIN_TRANSFORMER_IN_TOP);
    TransformerBuffer(analogRead(PIN_TRANSFORMER_OUT_TOP));
    TransformerReadout();
}
