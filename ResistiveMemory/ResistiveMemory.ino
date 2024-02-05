//1K Resistor between pins A and B

#define A A0
#define B A5

void setup() { Serial.begin(115200); }

void loop()
{///*
    Serial.println("Charging Resistor...");
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    delay(10000);
    
    Serial.println("Reading Resistor...");
    pinMode(A, INPUT);
    pinMode(B, INPUT);
    Serial.print(analogRead(A));
    Serial.print(", ");
    Serial.print(analogRead(B));
    Serial.println();
    delay(1000);
    //*///*
    Serial.println("Discharging Resistor...");
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    delay(10000);
    
    Serial.println("Reading Resistor...");
    pinMode(A, INPUT);
    pinMode(B, INPUT);
    Serial.print(analogRead(A));
    Serial.print(", ");
    Serial.print(analogRead(B));
    Serial.println();
    delay(1000);//*/
}
