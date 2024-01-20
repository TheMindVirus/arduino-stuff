//Zener Diode Bridge Rectifier
//Now With Added Lego Pieces!

//Connect 4x Zener Diode:
//Positive Input  -> Positive Output
//Positive Output -> Negative Input
//Negative Input  -> Negative Output
//Negative Output -> Positive Input

#define PIN_ZDBR_PI   A1
#define PIN_ZDBR_PO   A2
#define PIN_ZDBR_NI   A3
#define PIN_ZDBR_NO   A4

class EDGE
{
public:
    EDGE(int t);
    bool Check(int t);
    int m_tx1 = 0;
    int m_tx2 = 0;
    int m_lock = 0;
}; EDGE Edge(1000);

EDGE::EDGE(int t = 1000)
{
    m_tx1 = t * 1;
    m_tx2 = t * 2;
    m_lock = 0;
}

bool EDGE::Check(int t)
{
    if ((!m_lock) && ((t % m_tx2) <  (m_tx1))) { m_lock = true;  return true; }
    if (( m_lock) && ((t % m_tx2) >= (m_tx1))) { m_lock = false; return true; }
    return false;
}

void setup()
{
    Serial.begin(115200); Serial.println();
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    pinMode(PIN_ZDBR_PI, OUTPUT);
    pinMode(PIN_ZDBR_NI, OUTPUT);
    pinMode(PIN_ZDBR_PO, INPUT);
    pinMode(PIN_ZDBR_NO, INPUT);
    digitalWrite(PIN_ZDBR_PI, LOW);
    digitalWrite(PIN_ZDBR_NI, LOW);
    //X = digitalRead(PIN_ZDBR_PO);
    //Y = digitalRead(PIN_ZDBR_NO);
}

int state = 0;
int zdbr_pi = 0;
int zdbr_ni = 0;
int zdbr_po = 0;
int zdbr_no = 0;

void loop()
{
    switch (state)
    {
        default:
        case (0): { zdbr_pi = LOW;  zdbr_ni = LOW;  } break;
        case (1): { zdbr_pi = HIGH; zdbr_ni = LOW;  } break;
        case (2): { zdbr_pi = HIGH; zdbr_ni = HIGH; } break;
        case (3): { zdbr_pi = LOW;  zdbr_ni = HIGH; } break;
    }
    digitalWrite(PIN_ZDBR_PI, zdbr_pi);
    digitalWrite(PIN_ZDBR_NI, zdbr_ni);
    zdbr_po = digitalRead(PIN_ZDBR_PO);
    zdbr_no = digitalRead(PIN_ZDBR_NO);
    Serial.print("PI:"); Serial.print(zdbr_pi +2); Serial.print(",");
    Serial.print("NI:"); Serial.print(zdbr_ni +4); Serial.print(",");
    Serial.print("PO:"); Serial.print(zdbr_po +6); Serial.print(",");
    Serial.print("NO:"); Serial.print(zdbr_no +8); Serial.println( );
    if (Edge.Check(millis())) { state += 1; state %= 4; } delay(100);
}
