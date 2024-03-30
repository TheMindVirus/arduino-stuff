#define PIN_AUDIO_IN_R    A0
#define PIN_AUDIO_IN_L    A1

#define PIN_AUDIO_OUT_R    5
#define PIN_AUDIO_OUT_L    6

#define PIN_ENCODER_OUT   A3
#define PIN_ENCODER_IN    A5

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PIN_AUDIO_IN_R, INPUT);
    pinMode(PIN_AUDIO_IN_L, INPUT);
    pinMode(PIN_AUDIO_OUT_R, OUTPUT);
    pinMode(PIN_AUDIO_OUT_L, OUTPUT);
    pinMode(PIN_ENCODER_OUT, OUTPUT);
    pinMode(PIN_ENCODER_IN, INPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    //PWM Clock Divider Correction
    TCCR0A = 0b10100011;
    TCCR0B = 0b00000001;
}
/*
void loop()
{
    ADMUX = 0b01000000;
    ADCSRA = 0b11000011;
    while (ADCSRA & 0b01000000);
    OCR0B = (double)(ADC * 0.1);
    ADMUX = 0b01000001;
    ADCSRA = 0b11000011;
    while (ADCSRA & 0b01000000);
    OCR0A = (double)(ADC * 0.1);
}
*/
///*
void loop()
{
    volatile uint8_t SC = 0;
    volatile uint8_t SQ = 0;
    volatile double SF = 0.1;
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
            "lds %[SC],0x79;" "\n"
            "muls %[SC],%[SF];" "\n"/*
        "skl0:" "\n"
            "cpi %[SC],127;" "\n"
            "brlt skl1;" "\n"
            "ldi %[SC],127;" "\n"
        "skl1:" "\n"
            "cpi %[SC],1;" "\n"
            "brge skl2;" "\n"
            "ldi %[SC],1;" "\n"
        "skl2:" "\n"*/
            "sts 0x48,%[SC];" "\n"
            "jmp lpr2;" "\n"
        "lpr2:" "\n"
            "sts 0x7C,%[IR];" "\n"
            "sts 0x7A,%[CC];" "\n"
        "cdr2:" "\n"
            "lds %[SQ],0x7A;" "\n"
            "bst %[SQ],6;" "\n"
            "brts cdr2;" "\n"
            "lds %[SC],0x79;" "\n"
            "muls %[SC],%[SF];" "\n"/*
        "skr0:" "\n"
            "cpi %[SC],127;" "\n"
            "brlt skr1;" "\n"
            "ldi %[SC],127;" "\n"
        "skr1:" "\n"
            "cpi %[SC],10;" "\n"
            "brge skr2;" "\n"
            "ldi %[SC],10;" "\n"
        "skr2:" "\n"*/
            "sts 0x47,%[SC];" "\n"
            "jmp lpl1;" "\n"
        "jmp lpl1;" "\n"
        :
        [SC] "=r" (SC),
        [SQ] "=r" (SQ),
        [SF] "=r" (SF)
        :
        [IL] "r" (0x60), //0x40
        [IR] "r" (0x61), //0x41
        [CC] "r" (0xC3)
    );
}
//*/
/*
void loop()
{
    volatile uint8_t SC = 0;
    volatile uint8_t SQ = 0;
    asm volatile
    (
        "jmp lpl1;" "\n"
        "lpl1:" "\n"
            "sts 0x7C,%[IL];" "\n"
            "sts 0x7A,%[CC];" "\n"
        "cdl1:" "\n"
            "lds %[SQ],0x7A;" "\n"
            "clt" "\n"
            "bst %[SQ],6;" "\n"
            "brts cdl1;" "\n"
            "lds %[SC],0x79;" "\n"
        "skl0:" "\n"
            "cpi %[SC],0;" "\n"
            "brlt skl1;" "\n"
            //"sbc %[SC],%[SC];" "\n"
            //"asr %[SC];" "\n"
            //"asr %[SC];" "\n"
            //"asr %[SC];" "\n"
        "skl1:" "\n"
            "cpi %[SC],0;" "\n"
            "brge skl2;" "\n"
            //"sbc %[SC],%[SC];" "\n"
            //"asr %[SC];" "\n"
            //"asr %[SC];" "\n"
            //"asr %[SC];" "\n"
        "skl2:" "\n"
            "sts 0x48,%[SC];" "\n"
            "jmp lpr2;" "\n"
        "lpr2:" "\n"
            "sts 0x7C,%[IR];" "\n"
            "sts 0x7A,%[CC];" "\n"
        "cdr2:" "\n"
            "lds %[SQ],0x7A;" "\n"
            "clt" "\n"
            "bst %[SQ],6;" "\n"
            "brts cdr2;" "\n"
            "lds %[SC],0x79;" "\n"
        "skr0:" "\n"
            "cpi %[SC],0;" "\n"
            "brlt skr1;" "\n"
            //"sbc %[SC],%[SC];" "\n"
            //"asr %[SC];" "\n"
            //"asr %[SC];" "\n"
            //"asr %[SC];" "\n"
        "skr1:" "\n"
            "cpi %[SC],0;" "\n"
            "brge skr2;" "\n"
            //"sbc %[SC],%[SC];" "\n"
            //"asr %[SC];" "\n"
            //"asr %[SC];" "\n"
            //"asr %[SC];" "\n"
        "skr2:" "\n"
            "sts 0x47,%[SC];" "\n"
            "jmp lpl1;" "\n"
        "jmp lpl1;" "\n"
        :
        [SC] "=r" (SC),
        [SQ] "=r" (SQ)
        :
        [IL] "r" (0x60), //0x40
        [IR] "r" (0x61), //0x41
        [CC] "r" (0xC3)
    );
}
*/
/*
void loop()
{
    while (1)
    {
        analogWrite(PIN_AUDIO_OUT_R, analogRead(PIN_AUDIO_IN_R) * 0.1240234375);
        analogWrite(PIN_AUDIO_OUT_L, analogRead(PIN_AUDIO_IN_L) * 0.1240234375);
    }
}
*/
/*
//double level = 0.0;

void loop()
{
    level = (analogRead(PIN_AUDIO_IN) / 1024.0) * 127.0;
    //if (level < 10) { level = 0; }
    //tone(PIN_AUDIO_OUT, analogRead(PIN_AUDIO_IN));
    analogWrite(PIN_AUDIO_OUT, level);
    //Serial.print("255,0,"); Serial.println(level);
    //delayMicroseconds(analogRead(PIN_ENCODER_IN));
}
*/
