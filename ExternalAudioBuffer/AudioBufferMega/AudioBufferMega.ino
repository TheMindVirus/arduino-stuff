#define PIN_AUDIO_IN_L    A1
#define PIN_AUDIO_IN_R    A0

#define PIN_AUDIO_OUT_L    6
#define PIN_AUDIO_OUT_R    5

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PIN_AUDIO_IN_L, INPUT);
    pinMode(PIN_AUDIO_IN_R, INPUT);
    pinMode(PIN_AUDIO_OUT_L, OUTPUT);
    pinMode(PIN_AUDIO_OUT_R, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    TCCR3A = 0b10101010;
    TCCR3B = 0b00001001;
    TCCR4A = 0b10101010;
    TCCR4B = 0b00001001;
}

void loop()
{
    volatile uint8_t SQ = 0;
    asm volatile
    (
        "jmp lpl1;" "\n"
        "lpl1:" "\n"
            "sts 0x7C,%[IL];" "\n"
            "sts 0x7A,%[CC];" "\n"
        "cdl1:" "\n"
            "lds %[SQ],0x7A;" "\n"
            "bst %[SQ],6;" "\n"
            "brts cdl1;" "\n"
            "lds %[SQ],0x79;" "\n"
            "sts 0xA8,%[SQ];" "\n"
            "jmp lpr2;" "\n"
        "lpr2:" "\n"
            "sts 0x7C,%[IR];" "\n"
            "sts 0x7A,%[CC];" "\n"
        "cdr2:" "\n"
            "lds %[SQ],0x7A;" "\n"
            "bst %[SQ],6;" "\n"
            "brts cdr2;" "\n"
            "lds %[SQ],0x79;" "\n"
            "sts 0x98,%[SQ];" "\n"
            "jmp lpl1;" "\n"
        "jmp lpl1;" "\n"
        :
        [SQ] "=r" (SQ)
        :
        [IL] "r" (0x60), //0x40
        [IR] "r" (0x61), //0x41
        [CC] "r" (0xC3)
    );
}
