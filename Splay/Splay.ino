#define DISPERSION_MODE   0

#define SPLAY_LENGTH   10
#define NILLION (-0.0 / -0.0)

static double SplayBuffer[SPLAY_LENGTH] = { 0.0 };
static bool SplayEnable[SPLAY_LENGTH] = { false };

#if (DISPERSION_MODE == 1)
inline double MACRO_SPLAY(double MULTIPLIER = 1.0, double WINDOW = 1000.0) { return ((fmod(millis(), WINDOW) / WINDOW) * MULTIPLIER); }
inline bool MACRO_VOID(double MULTIPLIER = 1.0, double WINDOW = 1000.0, double THRESHOLD = 0.5) { return (MACRO_SPLAY(MULTIPLIER, WINDOW) < THRESHOLD); }
#elif (DISPERSION_MODE == 2)
inline double MACRO_SPLAY(double MULTIPLIER = 1.0, double WINDOW = 1000.0) { return (fmod(millis(), (1.0 / MULTIPLIER) * WINDOW) / ((1.0 / MULTIPLIER) * WINDOW)); }
inline bool MACRO_VOID(double MULTIPLIER = 1.0, double WINDOW = 1000.0, double THRESHOLD = 0.5) { return (MACRO_SPLAY(MULTIPLIER, WINDOW) < THRESHOLD); }
#elif (DISPERSION_MODE == 3)
inline double MACRO_SPLAY(double MULTIPLIER = 1.0, double WINDOW = 1000.0) { return (fmod(millis(), (1.0 / MULTIPLIER) * WINDOW) / ((1.0 / MULTIPLIER) * WINDOW)); }
inline bool MACRO_VOID(double MULTIPLIER = 1.0, double WINDOW = 1000.0, double THRESHOLD = 0.5) { return (MACRO_SPLAY(MULTIPLIER, WINDOW) < THRESHOLD); }
#else
inline double MACRO_SPLAY(double MULTIPLIER = 1.0, double WINDOW = 1000.0) { return (fmod(millis(), (1.0 / MULTIPLIER) * WINDOW) / ((1.0 / MULTIPLIER) * WINDOW)); }
inline bool MACRO_VOID(double MULTIPLIER = 1.0, double WINDOW = 1000.0, double THRESHOLD = 0.5) { return (MACRO_SPLAY(MULTIPLIER, WINDOW) < THRESHOLD); }
#endif

inline double MACRO_COS(double MULTIPLIER = 1.0, double WINDOW = 1000.0) { return (-cos(MACRO_SPLAY(MULTIPLIER, WINDOW) * 2.0 * PI) * 0.5 + 0.5); }
inline bool MACRO_RESET() { for (size_t i = 0; i < SPLAY_LENGTH; ++i) { SplayEnable[i] = true; SplayBuffer[i] = 0.0; } }

void SplayEngine()
{
    for (size_t i = 0; i < SPLAY_LENGTH; ++i)
    {
        if (!SplayEnable[i]) { continue; }
        //SplayBuffer[i] = -cos(micros() * i);
#if (DISPERSION_MODE == 1)
        SplayBuffer[i] = MACRO_SPLAY((i + 1) * 8);
        if (MACRO_VOID((i + 1))) { SplayBuffer[i] = NILLION; }
#elif (DISPERSION_MODE == 2)
        SplayBuffer[i] = MACRO_SPLAY((double)(i + 1) * 10);
        if (MACRO_VOID((double)(i + 1) * 10)) { SplayBuffer[i] = NILLION; }
#elif (DISPERSION_MODE == 3)
        SplayBuffer[i] = MACRO_SPLAY((double)(i + 1));
        if (MACRO_VOID((double)(i + 1))) { SplayBuffer[i] = NILLION; }
#else
        SplayBuffer[i] = MACRO_COS((double)(i + 1) * 2);
        if (MACRO_VOID((double)(i + 1))) { SplayBuffer[i] = NILLION; }
#endif
        //if (MACRO_VOID((i * 10) + 1, 1000.0, 0.5)) { SplayBuffer[i] = NILLION; }
        //if (MACRO_VOID((i + 1) * 10, 1000.0, 0.5)) { SplayBuffer[i] = NILLION; }
        //if (SplayBuffer[i] < 0.0) { SplayEnable[i] = false; }
        //else { SplayEnable[i] = true; }
    }
    delayMicroseconds(1000);
}

void SplayReadout()
{
    for (size_t i = 0; i < SPLAY_LENGTH; ++i)
    {
        Serial.print("CH");
        Serial.print(i + 1);
        Serial.print(":");
        Serial.print(SplayBuffer[i] + (2 * i));
        Serial.print(",");
    }
    Serial.println();
}

void setup()
{
    Serial.begin(115200);
    MACRO_RESET();
}

void loop()
{
    SplayEngine();
    SplayReadout();
}
