size_t n = 0;
size_t pos = 0;
char c = '\0';
uint8_t level = 0x00;
const size_t sz_buffer = 255;
char buffer[sz_buffer] = {'\0'};
char hexmap[] = "0123456789ABCDEF";
const size_t sz_hexmap = strlen(hexmap);

#define PIN_ANALOG_IN    A2
#define PIN_ANALOG_OUT    3
#define DELAY_BLINK     100

#define MACRO_CHECK(C)            \
    (((C >= '0') && (C <= '9')) || \
     ((C >= 'A') && (C <= 'F')))

inline void buffer_clear()
{
    for (size_t i = 0; i < sz_buffer; ++i) { buffer[i] = '\0'; }
    pos = 0;
}

inline int inline_hexmap(char c)
{
    for (size_t i = 0; i < sz_hexmap; ++i)
    {
        if (c == hexmap[i]) { return i; }
    }
    return -1;
}

size_t process(char command[], size_t length, bool verbose = false)
{
    goto start;
resume:
    if (verbose)
    {
        Serial.print(command[0]);
        Serial.print(command[1]);
        Serial.print(" (");
        Serial.print(length);
        Serial.println(")");
    }
    if ((MACRO_CHECK(command[0]))
    &&  (MACRO_CHECK(command[1])))
    {
        uint8_t hi = inline_hexmap(command[0]) & 0xF;
        uint8_t lo = inline_hexmap(command[1]) & 0xF;
        level = (hi << 4) + lo;
        if ((level >= 0x00) && (level <= 0xFF))
        {
            analogWrite(PIN_ANALOG_OUT, level);
            if (verbose) { Serial.println(level); }
            goto end;
        }
    }
    else { if (verbose) { Serial.println("?"); } }
    goto end;
start:
    digitalWrite(LED_BUILTIN, LOW);
    delay(DELAY_BLINK);
    goto resume;
end:
    digitalWrite(LED_BUILTIN, HIGH);
    delay(DELAY_BLINK);
    return length;
}

void setup()
{
    Serial.begin(115200);
    Serial.println("[BOOT]: Avalanche Diode");
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PIN_ANALOG_IN, INPUT);
    pinMode(PIN_ANALOG_OUT, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(PIN_ANALOG_OUT, level);
    buffer_clear();
}

void loop()
{
    n = Serial.available();
    for (size_t i = 0; i < n; ++i)
    {
        c = Serial.read();
        if ((c >= 32) && (c < 127))
        {
            buffer[pos] = c;
            ++pos; if (pos > 255) { pos = 255; }
        }
        else if (c == '\n')
        {
            process(buffer, pos, true);
            buffer_clear();
        }
    }
    Serial.print("1024,0,");
    Serial.println(analogRead(PIN_ANALOG_IN));
}
