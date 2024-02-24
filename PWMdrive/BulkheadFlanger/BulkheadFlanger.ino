int PIN_ENCODER_A = A0; //A1;
int PIN_ENCODER_B = A2; //A3;
int PIN_ENCODER_C = A4; //A5;

double mean = 0.0;
double time = 0.0;

const size_t MAX_BUFFER = 10;
double buffer[MAX_BUFFER] = { 0.0 };

bool BulkheadMode = false;
double BulkheadLevel = 0.0;

bool BulkheadInvert = false;
double BulkheadFlange = 0.0;

bool BulkheadLock = false;
double BulkheadPhase = 0.0;

bool BulkheadEnable = false;
double BulkheadWindow = 0.0;

bool BulkheadPulse = false;
double BulkheadDuty = 0.0;

double MAX_LEVEL = 1024.0;
double MIN_LEVEL =    0.0;

double MAX_SCOPE = 1536.0;
double MIN_SCOPE = -512.0;

int BUILTIN_LED = LED_BUILTIN;

int* DEFAULT_INPUT = &PIN_ENCODER_B;
int* DEFAULT_OUTPUT = &BUILTIN_LED;

bool DEFAULT_INVERT = false;
double DEFAULT_FLANGE = 0.0;
bool DEFAULT_SHIFT = false;
double DEFAULT_LEVEL = 0.0;
bool DEFAULT_ENABLE = true;
double DEFAULT_WINDOW = 1000000.0;
bool DEFAULT_PULSE = false;
double DEFAULT_DUTY = 0.5;

int FLANGE_CARRIER = 6; //64;
inline double FLANGE_LVL() { return (MACRO_FMOD() + MACRO_FLAN() - 0.5); }

bool MACRO_TEST = true; //false;

inline double MACRO_FLAN() { return -cos((fmod(time, BulkheadWindow) / BulkheadWindow) * 2.0 * PI * ((int)max(1.0, FLANGE_CARRIER))) * (BulkheadFlange * 0.5) + 0.5; }
inline double MACRO_FMOD() { return (fmod(time, max(0.000001, BulkheadPhase)) / max(0.000001, BulkheadPhase)); }
inline bool MACRO_SQUARE() { return (MACRO_FMOD() < BulkheadDuty); }
inline double MACRO_READ()
{
    mean = 0.0;
    for (size_t i = MAX_BUFFER - 1; i > 0; --i)
    {
        buffer[i] = buffer[i - 1];
        mean += buffer[i];
    }
    buffer[0] = analogRead(*DEFAULT_INPUT) / MAX_LEVEL;
    mean += buffer[0];
    mean /= MAX_BUFFER;
    return mean;
}

void BulkheadShift(bool Shift, bool Invert = false)
{
    if (Shift)
    {
        PIN_ENCODER_A = (Invert) ? (A5) : (A1);
        PIN_ENCODER_B = A3;
        PIN_ENCODER_C = (Invert) ? (A1) : (A5);
    }
    else
    {
        PIN_ENCODER_A = (Invert) ? (A4) : (A0);
        PIN_ENCODER_B = A2;
        PIN_ENCODER_C = (Invert) ? (A0) : (A4);
    }
    BulkheadMode = Shift;
    BulkheadInvert = Invert;
}

void BulkheadEngine()
{
    time = micros();
    if (!BulkheadEnable) { return; }
    if ((!BulkheadLock) && (MACRO_SQUARE()))
    {   BulkheadLock = true;
        digitalWrite(*DEFAULT_OUTPUT, HIGH);
    }
    else if ((BulkheadLock) && (!MACRO_SQUARE()))
    {   BulkheadLock = false;
        digitalWrite(*DEFAULT_OUTPUT, LOW);
    }
}

double readout_time = 0.0;
double readout_full = 10.0;
double readout_half = readout_full / 2.0;
bool readout_lock = false;
void BulkheadReadout()
{
    readout_time = millis();
    if ((!readout_lock) && (fmod(readout_time, readout_full) < readout_half))
    {
        readout_lock = true;
        if (MACRO_TEST)
        {
            Serial.print("MACRO_FMOD:");
            Serial.print(MACRO_FMOD() * MAX_LEVEL);
            Serial.print(",");
            Serial.print("MACRO_SQUARE:");
            Serial.print(MACRO_SQUARE() * MAX_LEVEL);
            Serial.print(",");
            Serial.print("MACRO_FLAN:");
            Serial.print(MACRO_FLAN() * MAX_LEVEL);
            Serial.print(",");
        }
        Serial.print("BULKHEAD:");
        Serial.print(BulkheadLevel * MAX_LEVEL);
        Serial.print(",");
        Serial.print("FLANGER:");
        Serial.print(FLANGE_LVL() * MAX_LEVEL);
        Serial.print(",");
        Serial.print("MAX_LEVEL:");
        Serial.print(MAX_LEVEL);
        Serial.print(",");
        Serial.print("MIN_LEVEL:");
        Serial.print(MIN_LEVEL);
        Serial.print(",");
        Serial.print("MAX_SCOPE:");
        Serial.print(MAX_SCOPE);
        Serial.print(",");
        Serial.print("MIN_SCOPE:");
        Serial.print(MIN_SCOPE);
        Serial.println();
    } else if ((readout_lock) && (!(fmod(readout_time, readout_full) < readout_half))) { readout_lock = false; }
    //delay(10);
}

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    BulkheadShift(DEFAULT_SHIFT, DEFAULT_INVERT);
    BulkheadLevel = DEFAULT_LEVEL;
    BulkheadEnable = DEFAULT_ENABLE;
    BulkheadFlange = DEFAULT_FLANGE;
    BulkheadWindow = DEFAULT_WINDOW;
    BulkheadPulse = DEFAULT_PULSE;
    BulkheadDuty = DEFAULT_DUTY;
    pinMode(PIN_ENCODER_A, OUTPUT);
    pinMode(PIN_ENCODER_B, INPUT);
    pinMode(PIN_ENCODER_C, OUTPUT);
    digitalWrite(PIN_ENCODER_A, LOW);
    digitalWrite(PIN_ENCODER_C, HIGH);
}

void BulkheadPatch()
{
    BulkheadLevel = MACRO_READ();
    if (BulkheadPulse) { BulkheadPhase = BulkheadWindow; BulkheadDuty = BulkheadLevel; }
    else { BulkheadPhase = BulkheadWindow; BulkheadFlange = BulkheadLevel; BulkheadDuty = FLANGE_LVL(); }
}

void loop()
{
    BulkheadPatch();
    BulkheadEngine();
    BulkheadReadout();
}
