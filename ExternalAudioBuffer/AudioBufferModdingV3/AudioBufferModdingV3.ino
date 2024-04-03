#define PIN_AUDIO_IN_L    A0
#define PIN_AUDIO_IN_R    A1
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
    TCCR0A = 0b10100011;
    TCCR0B = 0b00000001;
    DIDR0  = 0b00111111;
}

void loop()
{
    //for(;;) { analogWrite(PIN_AUDIO_OUT_L, analogRead(PIN_AUDIO_IN_L)); }
    asm volatile
    (
        "ldi r17,0x60\n"
        "ldi r18,0x61\n"
        "ldi r19,0xC3\n"
        "ldi r20,0x00\n"
        "ldi r21,0x00\n"
        "ldi r22,0x00\n"
        "ldi r23,0x00\n"
        "brid lpl1\n"
        "lpl1:\n"
            "sts 0x7C,r17\n"
            "sts 0x7A,r19\n"
        "cdl1:\n"
            "lds r20,0x7A\n"
            "bst r20,6\n"
            "brts cdl1\n"
            "lds r21,0x79\n"
            "sts 0x47,r21\n"
            "brid lpr2\n"
        "lpr2:\n"
            "sts 0x7C,r18\n"
            "sts 0x7A,r19\n"
        "cdr2:\n"
            "lds r22,0x7A\n"
            "bst r22,6\n"
            "brts cdr2\n"
            "lds r23,0x79\n"
            "sts 0x48,r23\n"
            "brid lpl1\n"
        "brid lpl1\n"
    );
    /*
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
            "sts 0x47,%[SQ];" "\n"
            "jmp lpl1;" "\n"
        "jmp lpl1;" "\n"
        :
        [SQ] "=r" (SQ)
        :
        [IL] "r" (0b01100000),
        [IR] "r" (0b01100001),
        [CC] "r" (0b11000011)
    );
    */
    /*
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
            "sts 0x48,%[SQ];" "\n"
            "jmp lpr2;" "\n"
        "lpr2:" "\n"
            "sts 0x7C,%[IR];" "\n"
            "sts 0x7A,%[CC];" "\n"
        "cdr2:" "\n"
            "lds %[SQ],0x7A;" "\n"
            "bst %[SQ],6;" "\n"
            "brts cdr2;" "\n"
            "lds %[SQ],0x79;" "\n"
            "sts 0x47,%[SQ];" "\n"
            "jmp lpl1;" "\n"
        "jmp lpl1;" "\n"
        :
        [SQ] "=r" (SQ)
        :
        [IL] "r" (0b01100000),
        [IR] "r" (0b01100001),
        [CC] "r" (0b11000011)
    );
    */
}
