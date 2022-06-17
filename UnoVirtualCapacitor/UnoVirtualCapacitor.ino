#define PIN_POWER    4
#define PIN_DETECT   5
#define PIN_ECHO     6
#define PIN_GROUND   7

#define CAPACITOR_SAMPLES     100

class capacitor
{
public:
    int value = 0;
    int samples[CAPACITOR_SAMPLES] = {0};
    int average = 0;

    void enqueue(int data)
    {
        value = data;
        int sum = 0;
        for (int i = CAPACITOR_SAMPLES - 1; i > 0; --i)
        {
            samples[i] = samples[i - 1];
            sum += samples[i];
        }
        samples[0] = value;
        average = sum / CAPACITOR_SAMPLES;
    }
};

capacitor detect;
capacitor echo;
capacitor diff;
capacitor threshold;

void setup()
{
    pinMode(PIN_POWER, OUTPUT);
    pinMode(PIN_DETECT, INPUT);
    pinMode(PIN_ECHO, INPUT);
    pinMode(PIN_GROUND, OUTPUT);
    digitalWrite(PIN_GROUND, LOW);
    digitalWrite(PIN_POWER, HIGH);
    Serial.begin(115200);
}

void loop()
{
    detect.enqueue(analogRead(PIN_DETECT));
    echo.enqueue(analogRead(PIN_ECHO));
    diff.enqueue(detect.value - echo.value);
    threshold.enqueue((diff.value > diff.average) ? 20 : 0);
    Serial.print("detect:");
    Serial.print(detect.average);
    Serial.print(",");
    Serial.print("echo:");
    Serial.print(echo.average);
    Serial.print(",");
    Serial.print("diff:");
    Serial.print(diff.average);
    Serial.print(",");
    Serial.print("threshold:");
    Serial.print(threshold.average);
    Serial.println();
}
