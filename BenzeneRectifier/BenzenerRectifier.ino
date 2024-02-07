#define BENZENER_AI   A0
#define BENZENER_AO   A1
#define BENZENER_BI   A2
#define BENZENER_BO   A3
#define BENZENER_CI   A4
#define BENZENER_CO   A5

#define PHASES        3
#define PHASES_X2     6

#define BLINK       250
#define BLINK_X2    500

unsigned int phase = PHASES_X2;
unsigned int timer = 0;
unsigned int mlock = 1;
unsigned int value = 0;

unsigned int AI = 0;
unsigned int AO = 0;
unsigned int BI = 0;
unsigned int BO = 0;
unsigned int CI = 0;
unsigned int CO = 0;

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    pinMode(BENZENER_AI, OUTPUT);
    pinMode(BENZENER_AO, INPUT_PULLUP);
    pinMode(BENZENER_BI, OUTPUT);
    pinMode(BENZENER_BO, INPUT_PULLUP);
    pinMode(BENZENER_CI, OUTPUT);
    pinMode(BENZENER_CO, INPUT_PULLUP);

    digitalWrite(BENZENER_AI, LOW);
    digitalWrite(BENZENER_BI, LOW);
    digitalWrite(BENZENER_CI, LOW);
}

int phaseShift(int next)
{
    int tmp = phase;
    phase = next;
    switch (phase)
    {
        default:
        case (0): { AI = 1; BI = 0; CI = 0; } break;
        case (1): { AI = 1; BI = 1; CI = 0; } break;
        case (2): { AI = 0; BI = 1; CI = 0; } break;
        case (3): { AI = 0; BI = 1; CI = 1; } break;
        case (4): { AI = 0; BI = 0; CI = 1; } break;
        case (5): { AI = 1; BI = 0; CI = 1; } break;
    }
    return tmp;
}

void loop()
{
    timer = millis();
    if ((!mlock) && ((timer % (BLINK_X2)) < BLINK))
    {
        mlock = 1;
        value = !value;
        phaseShift((phase + 1) % PHASES_X2);
    }
    else if ((mlock) && ((timer % (BLINK_X2)) >= BLINK))
    {
        mlock = 0;
    }
    digitalWrite(BENZENER_AI, AI);
    digitalWrite(BENZENER_BI, BI);
    digitalWrite(BENZENER_CI, CI);
    AO = digitalRead(BENZENER_AO);
    BO = digitalRead(BENZENER_BO);
    CO = digitalRead(BENZENER_CO);
    Serial.print("Phase:"); Serial.print(phase); Serial.print(",");
    Serial.print("AI:"); Serial.print(AI + 0x2); Serial.print(",");
    Serial.print("AO:"); Serial.print(AO + 0x4); Serial.print(",");
    Serial.print("BI:"); Serial.print(BI + 0x6); Serial.print(",");
    Serial.print("BO:"); Serial.print(BO + 0x8); Serial.print(",");
    Serial.print("CI:"); Serial.print(CI + 0xA); Serial.print(",");
    Serial.print("CO:"); Serial.print(CO + 0xC); Serial.println();
    delay(10);
}