int PIN_ENCODER_A = A0;
int PIN_ENCODER_B = A2;
int PIN_ENCODER_C = A4;

double intensity = 0.0;
double min_analog = 0.0;
double max_analog = 1024.0;
double brightness = 2048.0;

const size_t max_buffer = 10;
double buffer[max_buffer] = { 0.0 };
double average = 0.0;

inline double smoothRead(int pin)
{
    average = 0.0;
    for (size_t i = max_buffer - 1; i > 0; --i)
    {
        buffer[i] = buffer[i - 1];
        average += buffer[i];
    }
    buffer[0] = analogRead(pin) / max_analog;
    average += buffer[0];
    average /= max_buffer;
    return average;
}

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PIN_ENCODER_A, OUTPUT);
    pinMode(PIN_ENCODER_B, INPUT);
    pinMode(PIN_ENCODER_C, OUTPUT);
    digitalWrite(PIN_ENCODER_A, LOW);
    digitalWrite(PIN_ENCODER_C, HIGH);
    for (size_t i = 0; i < max_buffer; ++i) { buffer[i] = 0.0; }
}

void loop()
{
    //tone(LED_BUILTIN, analogRead(PIN_ENCODER_B));
    
    Serial.print("A:"); Serial.print(intensity); Serial.print(",");
    Serial.print("B:"); Serial.print(brightness - intensity); Serial.print(",");
    Serial.print("C:"); Serial.print(min_analog); Serial.print(",");
    Serial.print("D:"); Serial.print(max_analog); Serial.println();
    
    intensity = smoothRead(PIN_ENCODER_B) * brightness;
    digitalWrite(LED_BUILTIN, HIGH);
    delayMicroseconds(intensity);
    digitalWrite(LED_BUILTIN, LOW);
    delayMicroseconds(brightness - intensity);
}
