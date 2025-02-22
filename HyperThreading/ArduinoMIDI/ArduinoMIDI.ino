#define signal ISR
#define signals interrupts
#define noSignals noInterrupts
#define midi USART_RX_vect

#define TX_MODE
//#define RX_MODE

int state = 0;
bool lock = false;
size_t nBytes = 0;

//char* noteOn = "\x90\x30\x7F";
//char* noteOff = "\x80\x30\x00";
//char* noteHush = "\x90\x30\x00";

char* noteOn = "\x91\x30\x7F";
char* noteOff = "\x81\x30\x00";
char* noteHush = "\x91\x30\x00";

//void midi_msg(byte conch, byte param, byte value)
//void midi_msg(uint8_t conch, uint8_t param, uint8_t value)
void midi_msg(char conch, char param, char value)
{
    Serial.write(conch); Serial.flush();
    Serial.write(param); Serial.flush();
    Serial.write(value); Serial.flush();
    //Serial.print(conch); Serial.flush();
    //Serial.print(param); Serial.flush();
    //Serial.print(value); Serial.flush();
}

void note_on() { midi_msg(0x90, 0x30, 0x7F); }
void note_off() { midi_msg(0x80, 0x30, 0x00); }
void note_hush() { midi_msg(0x90, 0x30, 0x00); }

void setup()
{
    //noSignals(); //signals();
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.begin(31250, SERIAL_8N1); //115200);
    //signals(); //noSignals();
    //Serial.onReceive = receive;
}

//signal(midi) { onReceive(Serial.available(); }
void onReceive(size_t nBytes)
{
    digitalWrite(LED_BUILTIN, HIGH);
#ifdef TX_MODE
#ifndef RX_MODE
    for (size_t i = 0; i < nBytes; ++i) { Serial.read(); }
#endif
#endif
#ifdef RX_MODE
    for (size_t i = 0; i < nBytes; ++i) { Serial.print(Serial.read(), HEX); Serial.println(); }
#endif
}

void loop()
{
    nBytes = Serial.available();
    if (nBytes > 0) { onReceive(nBytes); }
#ifdef TX_MODE
    if ((!lock) && ((millis() % 1000) < 500))
    {
        lock = true;
        switch (state)
        {
            case (0):
            case (2): { note_on(); }
            //case (2): { Serial.print(noteOn); Serial.flush(); }
            break;
            case (1): { note_off(); }
            //case (1): { Serial.print(noteOff); Serial.flush(); }
            break;
            case (3): { note_hush(); }
            //case (3): { Serial.print(noteHush); Serial.flush(); }
            break;
            default:
            break;
        }
    }
    else if ((lock) && ((millis() % 1000) > 500))
    {
        state += 1;
        state %= 4;
        lock = false;
        digitalWrite(LED_BUILTIN, LOW);
    }
#endif
}
