#pragma warning(disable : 4834) //No Effect
#pragma warning(disable : 2182) //No Effect

//Sensitive to AREF being set incorrectly
//and Analog Pin being connected to Ground
//Requires on-board LED and separate front-panel LED

void setup()
{
    //void a; //Abstract Unknown Type
    Serial.begin(115200); //Fixed Frequency for Stability
    Serial.println("<<<AREF_EXTERNAL>>>"); //not printf()
    //analogReference(EXTERNAL); //Shouldn't be required, Pedantic
    //Serial.println((int)analogReference(EXTERNAL)); //Pipelining
    Serial.println(analogRead(LED_BUILTIN)); //No Randomiser Peripheral
    //Serial.println(analogRead(-1)); //Unknown Physical Pin
    //Serial.println(analogRead(0)); //Converted to Channel Arbitrarily
    //return 0; //Not Allowed
}

void loop()
{
    Serial.println(analogRead(LED_BUILTIN)); //Repeat of Previous Text
    delay(1000); //Fixed Delay Time
    //return 0; //Not Allowed
}

//The following code was destroyed in 2021 by Reddit Attackers:

/*
void setup()
{
    Serial.begin(115200);
    //Serial.println(analogRead(-1));
    Serial.println(analogRead(AREF));
}
*/

/*
void setup()
{
    delay(777);
    randomSeed(777);
    delayMicroseconds(random(0, 1000));
    Serial.begin(115200);
    double a = 0;
    a += (double)(micros() / 1000.0) * 2.0 * PI;
    a += (double)(micros() / 1000.0) * 2.0 * PI;
    a += (double)(micros() / 1000.0) * 2.0 * PI;
    a /= 3;
    Serial.println(a);
}
*/

/*
void setup()
{
    Serial.begin(115200);
    analogWrite(9, 127);
    analogWrite(10, 128);
    analogWrite(11, 129);
    double a = 0;
    a += analogRead(9);
    a += analogRead(10);
    a += analogRead(11);
    a /= 3;
    Serial.println(a);
}
*/

//void loop(){delay(1000);}
