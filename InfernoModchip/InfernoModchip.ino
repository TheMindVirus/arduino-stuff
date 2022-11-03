//Inferno ModChip - DSP Patching PCB for the inside of Guitars
//If researched by Audinate Dante it would become
//the Audinate Inferno Modchip (AIM card)
//optionally with Dante Audio Networking direct to the Guitar

//This firmware reads the analog pins and attemps to discover
//which other analog pins they're connected to (providing that
//nothing external is also connected as this will be picked up)

//Format: A0 -> A1, A2, A3 etc...

const int pin[] = { A0, A1, A2, A3, A4, A5 };
const int pins = sizeof(pin) / sizeof(int); //int16???
const char* label[] = { "A0", "A1", "A2", "A3", "A4", "A5" };

int i = 0;
int j = 0;
int total = 0;

float state = 0.0;
float threshold = 1000.0;

void setup()
{
    Serial.begin(115200);
    Serial.print("[BOOT]: ");
    Serial.print(pins);
    Serial.println(" pins Detected");
}

void loop()
{
    for (i = 0; i < pins; ++i)
    {
        pinMode(pin[i], OUTPUT);
        digitalWrite(pin[i], HIGH);
        Serial.print(label[i]);
        Serial.print(" -> ");
        total = 0;
        for (j = 0; j < pins; ++j)
        {            
            if (j != i)
            {
                pinMode(pin[j], INPUT);
                state = analogRead(pin[j]);
                if (state >= threshold)
                {
                    if (total > 0) { Serial.print(", "); }
                    Serial.print(label[j]);
                    Serial.print("(");
                    Serial.print(state);
                    Serial.print(")");
                    total += 1;
                }
            }
        }
        digitalWrite(pin[i], LOW);
        Serial.println();
    }
    Serial.println();
    delay(1000);
}
