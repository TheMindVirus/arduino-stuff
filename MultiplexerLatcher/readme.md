```c
//74HC4351 8-Channel Analog Latched Multiplexer
//Latch Mechanism on some units from 1990 might not work

#define PIN_MUX_LATCHER   3

#define PIN_MUX_ENABLE1   5
#define PIN_MUX_ENABLE2   6

#define PIN_MUX_SELECT0   9
#define PIN_MUX_SELECT1   10
#define PIN_MUX_SELECT2   11

#define PIN_MUX_DATA_IN   A0

const size_t size = 255;
char buffer[size] = "";
bool cmd = false;
size_t pos = 0;

int STATE_MUX_LATCHER = 1;

int STATE_MUX_ENABLE1 = 0;
int STATE_MUX_ENABLE2 = 1;

int STATE_MUX_SELECT0 = 0;
int STATE_MUX_SELECT1 = 0;
int STATE_MUX_SELECT2 = 0;

void HelpCommand()
{
    Serial.println("[HELP]: S0, S1, S2, IN, LE, E1, E2");
    Serial.println("[INFO]: LATCH: LE 1->0 (Faulty???)");
}

void ClearCommand()
{
    pos = 0;
    for (size_t i = 0; i < size; ++i)
    {
        buffer[i] = '\0';
    }
    cmd = false;
}

void EncodeCommand()
{
    for (size_t i = 0; i < Serial.available(); ++i)
    {
        char c = Serial.read();
        if ((c >= 32) && (c < 127)) { buffer[pos] = c; }
        if (c == '\n')
        {
            pos = 0;
            cmd = true;
            break; //return; //flag = true;
        }
        if (pos < size) { ++pos; }
    }
}

void DecodeCommand()
{
    if (!cmd) { return; }
    if (0 == strncmp(buffer, "LE", 2))
    {
        STATE_MUX_LATCHER = !STATE_MUX_LATCHER;
        digitalWrite(PIN_MUX_LATCHER, STATE_MUX_LATCHER);
        Serial.println(STATE_MUX_LATCHER);
    }
    else if (0 == strncmp(buffer, "E1", 2))
    {
        STATE_MUX_ENABLE1 = !STATE_MUX_ENABLE1;
        digitalWrite(PIN_MUX_ENABLE1, STATE_MUX_ENABLE1);
        Serial.println(STATE_MUX_ENABLE1);
    }
    else if (0 == strncmp(buffer, "E2", 2))
    {
        STATE_MUX_ENABLE2 = !STATE_MUX_ENABLE2;
        digitalWrite(PIN_MUX_ENABLE2, STATE_MUX_ENABLE2);
        Serial.println(STATE_MUX_ENABLE2);
    }
    else if (0 == strncmp(buffer, "S0", 2))
    {
        STATE_MUX_SELECT0 = !STATE_MUX_SELECT0;
        digitalWrite(PIN_MUX_SELECT0, STATE_MUX_SELECT0);
        Serial.println(STATE_MUX_SELECT0);
    }
    else if (0 == strncmp(buffer, "S1", 2))
    {
        STATE_MUX_SELECT1 = !STATE_MUX_SELECT1;
        digitalWrite(PIN_MUX_SELECT1, STATE_MUX_SELECT1);
        Serial.println(STATE_MUX_SELECT1);
    }
    else if (0 == strncmp(buffer, "S2", 2))
    {
        STATE_MUX_SELECT2 = !STATE_MUX_SELECT2;
        digitalWrite(PIN_MUX_SELECT2, STATE_MUX_SELECT2);
        Serial.println(STATE_MUX_SELECT2);
    }
    else if (0 == strncmp(buffer, "IN", 2))
    {
        Serial.println(analogRead(PIN_MUX_DATA_IN));
    }
    else if (0 == strncmp(buffer, "\0\0", 2))
    {
        Serial.println(analogRead(PIN_MUX_DATA_IN));
        //HelpCommand();
    }
    else { Serial.println("???"); }
    ClearCommand();
}

void setup()
{
    Serial.begin(115200);
    pinMode(PIN_MUX_LATCHER, OUTPUT);
    pinMode(PIN_MUX_ENABLE1, OUTPUT);
    pinMode(PIN_MUX_ENABLE2, OUTPUT);
    pinMode(PIN_MUX_SELECT0, OUTPUT);
    pinMode(PIN_MUX_SELECT1, OUTPUT);
    pinMode(PIN_MUX_SELECT2, OUTPUT);
    pinMode(PIN_MUX_DATA_IN, INPUT);
    digitalWrite(PIN_MUX_LATCHER, STATE_MUX_LATCHER);
    digitalWrite(PIN_MUX_ENABLE1, STATE_MUX_ENABLE1);
    digitalWrite(PIN_MUX_ENABLE2, STATE_MUX_ENABLE2);
    digitalWrite(PIN_MUX_SELECT0, STATE_MUX_SELECT0);
    digitalWrite(PIN_MUX_SELECT1, STATE_MUX_SELECT1);
    digitalWrite(PIN_MUX_SELECT2, STATE_MUX_SELECT2);
    ClearCommand();
    HelpCommand();
}

void loop()
{
    EncodeCommand();
    DecodeCommand();
}
```
