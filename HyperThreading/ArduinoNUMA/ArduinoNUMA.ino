#define signal     ISR
#define watchdog   WDT_vect
#define counter    WDTCSR
#define value      bit(WDIE)
#define signals    interrupts
#define noSignals  noInterrupts
#define persist    __attribute__((section(".noinit")))
#define jump(addr) asm volatile("jmp (%0);" :: "p" (&(addr)));

void (*reset)() = 0;
int cpuid persist; // = 1;
bool egret persist; // = false;

void core1()
{
    Serial.println("[PID1]: Boot.");
    Serial.flush();
}

void core2()
{
    Serial.println("[PID2]: Halt.");
    Serial.flush(); while (true);
}

void core3()
{
    Serial.println("[PID3]: Halt.");
    Serial.flush(); while (true);
}

void core4()
{
    Serial.println("[PID4]: Halt.");
    Serial.flush(); while (true);
}

void setup()
{
    //noSignals(); //noInterrupts();
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.begin(115200);
    Serial.flush();
    if (!egret)
    {
        egret = true;
        Serial.println("[NUMA]: Egret.");
        Serial.flush();
        return;
    }
    else { cpuid = 1; }
    Serial.println("[NUMA]: Boot.");
    Serial.flush();
    //signals(); //interrupts();
}

void nq()
{
    counter = value;
}

void dq()
{
    ++cpuid; if (cpuid > 4) { cpuid = 1; }
}

signal(watchdog)
{
    Serial.println("[ALRT]: Warn."); Serial.flush();
    counter = 0; dq(); egret = false; reset();
}

void loop()
{
    if (cpuid == 1) { nq(); core1(); dq(); }
    if (cpuid == 2) { nq(); core2(); dq(); }
    if (cpuid == 3) { nq(); core3(); dq(); }
    if (cpuid == 4) { nq(); core4(); dq(); }
}
