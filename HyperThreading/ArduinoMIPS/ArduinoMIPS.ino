#define BAUD_RATE   115200
#define BAUD_PROC   BAUD_RATE
#define BAUD_IDLE   96000
#define BAUD_NULL   0

#define NUM_THREADS   4
#define NUM_QUEUES    NUM_THREADS
#define NUM_STEPS     NUM_QUEUES
#define NUM_TOTAL     NUM_THREADS * NUM_QUEUES * NUM_STEPS

#define PHASE_INTERVAL   1000
#define PHASE_CPUID      0
#define PHASE_PRE        1
#define PHASE_POST       2

bool first __attribute__((section(".noinit"))); // != 0

short isr_counter = 0;
unsigned null = 0; //const unsigned nullptr = null;

bool egret = false;
void (*ploop)() = null;

int thrid __attribute__((section(".noinit")));
int squid __attribute__((section(".noinit")));

int cpuid = 0;
const int posid = NUM_STEPS / 2;

long baud[NUM_THREADS] = {};
void (*queue[NUM_THREADS][NUM_QUEUES][NUM_STEPS])(int cpuid, int phase);

void alerts(bool enable)
{
    Serial.print("[ALRT]: ");
    Serial.print("FROM: ");
    Serial.print(TCNT1);
    Serial.print(", ");
    Serial.print(TCCR1A);
    Serial.print(", ");
    Serial.print(TCCR1B);
    Serial.print(", ");
    Serial.print(TCCR1C);
    Serial.print(", ");
    Serial.print(TIMSK1);
    Serial.print(", ");
    Serial.print(TIFR1);
    Serial.print(", ");
    Serial.print(OCR1A);
    Serial.println();
    Serial.flush();
    if (enable)
    {
        isr_counter = 0;
        TCNT1 = 0; //0xFFFF;
        TCCR1A = 0;
        TCCR1B = bit(CS12);
        TCCR1C = 0;
        TIMSK1 = bit(OCIE1A);
        TIFR1 = 0;
        OCR1A = 0x7FFF; //0;
        OCR1B = 0;
        ICR1 = 0;
    }
    else
    {
        isr_counter = 0;
        TCNT1 = 0;
        TCCR1A = bit(WGM10);
        TCCR1B = bit(CS11) | bit(CS10);
        TCCR1C = 0;
        TIMSK1 = 0;
        TIFR1 = bit(TOV1);
        OCR1A = 0;
        OCR1B = 0;
        ICR1 = 0;
    }
    Serial.print("[ALRT]: ");
    Serial.print("TO: ");
    Serial.print(TCNT1);
    Serial.print(", ");
    Serial.print(TCCR1A);
    Serial.print(", ");
    Serial.print(TCCR1B);
    Serial.print(", ");
    Serial.print(TCCR1C);
    Serial.print(", ");
    Serial.print(TIMSK1);
    Serial.print(", ");
    Serial.print(TIFR1);
    Serial.print(", ");
    Serial.print(OCR1A);
    Serial.println();
    Serial.flush();
}

ISR(TIMER1_COMPA_vect) //governor
{
    isr_counter += 1;
    if (isr_counter == 1) { return; }
    digitalWrite(LED_BUILTIN, HIGH);
    alerts(false);
    first = false;
    egret = true;
    //Serial.end();
    Serial.begin(BAUD_RATE);
    Serial.print("[INFO]: EGRET: ");
    Serial.println(egret);
    Serial.println("[WARN]: ISR: flip");
    Serial.flush();
    digitalWrite(LED_BUILTIN, LOW);
    //set link register or return address back to loop
    loop(); //resolve deadlock condition in iteration
    asm volatile("jmp %0" :: "m" (ploop)); //cancel op
    //asm volatile("jmp %[addr]" :: [addr] "r" (ploop));
    return; //may need different instruction
    //asm volatile("pop r24; reti;");
}

void proc(int cpuid, int phase) //performance
{
    Serial.print("[PROC]: ");
    Serial.print("CPUID#");
    Serial.print(cpuid);
    Serial.print(".");
    Serial.print(phase);
    Serial.print(": ");
    Serial.print("Hello");
    Serial.println();
    Serial.flush();
}

void idle(int cpuid, int phase) //efficiency
{
    Serial.print("[IDLE]: ");
    Serial.print("CPUID#");
    Serial.print(cpuid);
    Serial.print(".");
    Serial.print(phase);
    Serial.print(": ");
    Serial.print("...");
    Serial.println();
    Serial.flush();
    while (true);
}

void global(int cpuid, int phase) //kernel
{
    queue[0][0][posid] = proc;
    queue[2][2][posid] = proc;
}

void bootloader_commence_load_operation() //loader
{
    int t = 0, q = 0, s = 0;
    alerts(false); ploop = loop;
    if (first) { thrid = 0; squid = 0; }
    for (int i = 0; i < NUM_TOTAL; ++i)
    {
        queue[t][q][s] = idle; ++t;
        if (t >= NUM_THREADS) { t = 0; ++q;
        if (q >= NUM_QUEUES) { q = 0; ++s;
        if (s >= NUM_STEPS) { s = 0; } } }
    }
    for (int thrid = 0; thrid < NUM_THREADS; ++thrid)
    {
        baud[thrid] = BAUD_IDLE;
    }
    baud[0] = BAUD_PROC;
}

void setup() //boot
{
    //cli(); //sei(); //Ignore Signals
    Serial.begin(BAUD_RATE);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    bootloader_commence_load_operation();
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("[BOOT]: MIPS: Quad-Core");
    Serial.flush();
    //sei(); //cli(); //Accept Signals
}

void loop() //chipset
{
    //Serial.print("[INFO]: EGRET: ");
    //Serial.println(egret);
    //Serial.flush();
    //alerts(true);
    //delay(1000);
    //alerts(false);
    //alerts(true);
    //while(true);
    if (egret)
    {
        egret = false;
        Serial.println("[WARN]: ISR: resume");
        Serial.print("[INFO]: EGRET: ");
        Serial.println(egret);
        Serial.flush();
        ++squid; if (squid >= NUM_QUEUES) { squid = 0;
        ++thrid; if (thrid >= NUM_THREADS) { thrid = 0; } }
        //goto resume;
        return;
    }
    //Serial.end();
    Serial.begin(BAUD_RATE);
    global(PHASE_CPUID, PHASE_PRE);
    for (;;) //thrid = 0; thrid < NUM_THREADS; ++thrid)
    {
        for (;;) //squid = 0; squid < NUM_QUEUES; ++squid)
        {
            cpuid = thrid + 1;
            //Serial.end();
            //Serial.begin(baud[cpuid]);
            //sei(); //cli();
            Serial.print("[INFO]: THRID: ");
            Serial.println(thrid);
            Serial.print("[INFO]: SQUID: ");
            Serial.println(squid);
            Serial.print("[ADDR]: POSID: 0x");
            Serial.println((int)&(queue[thrid][squid][posid]), HEX);
            Serial.flush();
            alerts(true); //alerts(false);
            //if ((thrid == 0) && (squid == 0)) { queue[0][0][posid](0, 0); }
            queue[thrid][squid][posid](cpuid, squid + 1);
            /*alerts(false); //alerts(true);
            goto finish;
            resume:
            Serial.println("[GOTO]: TAG: resume");
            Serial.flush();
            return;
            //goto finish;
            finish:
            Serial.println("[GOTO]: TAG: finish");
            Serial.flush();*/
            ++squid; if (squid >= NUM_QUEUES) { squid = 0; break; }
            //Serial.end();
            //cli(); sei();
            ;
        }
        ++thrid; if (thrid >= NUM_THREADS) { thrid = 0; break; }
    }
    //Serial.end();
    Serial.begin(BAUD_RATE);
    global(PHASE_CPUID, PHASE_POST);
    delay(PHASE_INTERVAL);
}
/*
bool spread = true;
void loop() //legacy
{
    for (int cpuid = 1; cpuid <= NUM_THREADS; ++cpuid)
    {
        global(cpuid, 1);
        if (cpuid == 1) { core1(); }
        if (spread) { delay(1); }
        if (cpuid == 2) { core2(); }
        if (spread) { delay(1); }
        if (cpuid == 3) { core3(); }
        if (spread) { delay(1); }
        if (cpuid == 4) { core4(); }
        if (spread) { delay(1); }
        global(cpuid, 2);
        delay(100);
    }
}
*/
