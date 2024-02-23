//2-Pin Axial Reed Relay (without inductor)
//3-Pin++ is also available (for control and latch)

//A visual graphing example, as it seems to read
//the same way with or without the reed present...

#define BAUD    115200
#define INTERVAL   500

#define REED_A       6
#define REED_B      12

int A = 0;
int B = 0;
int S = 0;

void SetState(int state = 0);
void LineFeed(size_t n = 20, int z = 2);

void ReadReed();
void LiftReed();
void DropReed();
void PushReed();
void PullReed();

void SetState(int state = 0)
{
    S = state;
    digitalWrite(LED_BUILTIN, S % 2);
}

void LineFeed(size_t n = 20, int z = 2)
{
    for (size_t i = 0; i < n; ++i)
    {
        Serial.print("A:"); Serial.print(A); Serial.print(",");
        Serial.print("B:"); Serial.print(B); Serial.print(",");
        Serial.print("S:"); Serial.print(S + z); Serial.println();
    }
}

void ReadReed()
{
    Serial.println("Reading Reed...");
    pinMode(REED_A, INPUT);
    pinMode(REED_B, INPUT);
    A = digitalRead(REED_A);
    B = digitalRead(REED_B);
    delay(INTERVAL);
    LineFeed();
}

void LiftReed()
{
    Serial.println("Powering Reed...");
    pinMode(REED_A, OUTPUT);
    pinMode(REED_B, OUTPUT);
    digitalWrite(REED_A, HIGH);
    digitalWrite(REED_B, HIGH);
    delay(INTERVAL);
    ReadReed();
}

void DropReed()
{ 
    Serial.println("Grounding Reed...");
    pinMode(REED_A, OUTPUT);
    pinMode(REED_B, OUTPUT);
    digitalWrite(REED_A, LOW);
    digitalWrite(REED_B, LOW);
    delay(INTERVAL);
    ReadReed();
}

void PushReed()
{ 
    Serial.println("Charging Reed...");
    pinMode(REED_A, OUTPUT);
    pinMode(REED_B, OUTPUT);
    digitalWrite(REED_A, HIGH);
    digitalWrite(REED_B, LOW);
    delay(INTERVAL);
    ReadReed();
}

void PullReed()
{
    Serial.println("Discharging Reed...");
    pinMode(REED_A, OUTPUT);
    pinMode(REED_B, OUTPUT);
    digitalWrite(REED_A, LOW);
    digitalWrite(REED_B, HIGH);
    delay(INTERVAL);
    ReadReed();
}

void setup() 
{
    Serial.begin(BAUD);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    pinMode(REED_A, OUTPUT);
    pinMode(REED_B, OUTPUT);
    digitalWrite(REED_A, LOW);
    digitalWrite(REED_B, LOW);

    SetState(0);
    LiftReed();
    DropReed();
}

void loop() 
{
    SetState(1); PushReed();
    SetState(2); DropReed();
    SetState(3); PullReed();
    SetState(4); DropReed();
}
