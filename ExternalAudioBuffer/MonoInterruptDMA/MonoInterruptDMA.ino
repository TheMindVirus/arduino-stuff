#define PIN_AUDIO_INP   A0
#define PIN_AUDIO_AUX   A1
#define PIN_AUDIO_OUT    9
#define PIN_AUDIO_EXT   10

#include <avr/interrupt.h>
ISR(ADC_vect) { OCR1A = OCR1B = ADCH; }

void setZ(uint16_t cb)
{
    volatile uint8_t hi = (cb >> 8) & 0xFF;
    volatile uint8_t lo =  cb       & 0xFF;
    asm volatile("mov r31,%[HI];\nnop;\nmov r30,%[LO];\nnop;\n"::[HI]"r"(hi),[LO]"r"(lo));
}

uint16_t readZ()
{
    volatile uint8_t hi = 0;
    volatile uint8_t lo = 0;
    asm volatile("mov %[HI],r31;\nnop;\nmov %[LO],r30;\nnop;\n":[HI]"=r"(hi),[LO]"=r"(lo));
    return (hi << 8) + lo;
}

void callZ(uint16_t cb)
{
    volatile uint8_t hi = (cb >> 8) & 0xFF;
    volatile uint8_t lo =  cb       & 0xFF;
    asm volatile("mov r31,%[HI];\nnop;\nmov r30,%[LO];\nnop;\nicall;\n"::[HI]"r"(hi),[LO]"r"(lo));
}

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    //while (!Serial);
    //callZ(loop);
    //setZ(loop);
    //Serial.println(readZ(), HEX);
    //asm volatile("icall");
    //while (1);
    pinMode(PIN_AUDIO_INP, INPUT);
    pinMode(PIN_AUDIO_AUX, INPUT);
    pinMode(PIN_AUDIO_OUT, OUTPUT);
    pinMode(PIN_AUDIO_EXT, OUTPUT);
    TCCR1A = 0b10100010;
    TCCR1B = 0b00001001;
    TCCR1C = 0b10000000;
    sei(); //Mono Interrupt DMA :(
    ADMUX  = 0b01100000; // 0b01100001
    ADCSRA = 0b11101011;
    DIDR1  = 0b00000011;
}

void loop()
{
    //volatile uint8_t SQ = 0;
    /*
    asm volatile
    (
        "jmp lpl1;" "\n" "nop;" "\n" "nop;" "\n"
        "lpl1:" "\n"
            "sts 0x7C,%[IL];" "\n" "nop;" "\n"
            "sts 0x7A,%[CC];" "\n" "nop;" "\n"
            "sts 0x7B,%[BB];" "\n" "nop;" "\n"
        "cdl1:" "\n"
            "lds %[SQ],0x7A;" "\n" "nop;" "\n"
            "bst %[SQ],4;" "\n"
            "brts cdl1;" "\n" // "nop;" "\n"
            //"ldi %[SQ],0x7F;" "\n" "nop;" "\n"
            "lds %[SQ],0x79;" "\n" "nop;" "\n"
            "sts 0x48,%[SQ];" "\n" "nop;" "\n"
            "jmp lpr2;" "\n" "nop;" "\n" "nop;" "\n"
        "lpr2:" "\n"
            "sts 0x7C,%[IR];" "\n" "nop;" "\n"
            "sts 0x7A,%[CC];" "\n" "nop;" "\n"
            "sts 0x7B,%[BB];" "\n" "nop;" "\n"
        "cdr2:" "\n"
            "lds %[SQ],0x7A;" "\n" "nop;" "\n"
            "bst %[SQ],4;" "\n"
            "brts cdr2;" "\n" // "nop;" "\n"
            //"ldi %[SQ],0x7F;" "\n" "nop;" "\n"
            "lds %[SQ],0x79;" "\n" "nop;" "\n"
            "sts 0x47,%[SQ];" "\n" "nop;" "\n"
            "jmp lpl1;" "\n" "nop;" "\n" "nop;" "\n"
        "jmp lpl1;" "\n" "nop;" "\n" "nop;" "\n"
        :
        [SQ] "=r" (SQ)
        :
        [IL] "r" (0b01100000),
        [IR] "r" (0b01100001),
        [BB] "r" (0b00000001),
        [CC] "r" (0b11101011)
    );*/
}
