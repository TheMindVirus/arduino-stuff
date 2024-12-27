#include <Adafruit_ST7735.h>

#define PIN_GND   7
#define PIN_VCC   6
#define PIN_CLK   5
#define PIN_DAT   4
#define PIN_RST   3
#define PIN_DC    2
#define PIN_CS    1
#define PIN_BL    0

#define BAUD      115200
#define INTERVAL  0 //10

#define LINE      160
#define FULL      128
#define COLS      26
#define ROWS      16
#define CHAR      8
#define TABS      4
#define ROOT      ">_: "
#define SZROOT    strlen(ROOT)
#define D(C)      (((c >= 32) && (c < 127)) ? c : 0)

int n = 0;
int pos = 0;
char c = '\0';
char* root = ROOT;
const int sz_tabs = TABS;
const int sz_root = SZROOT;
const int sz_buffer = COLS - sz_root;
const int sz_scroll = ROWS - 1;
const int sz_height = CHAR;
const int sz_width = LINE;
const int interval = INTERVAL;
char buffer[sz_buffer] = {};
char scroll[sz_scroll][sz_buffer] = {};

Adafruit_ST7735 display = Adafruit_ST7735(PIN_CS, PIN_DC, PIN_DAT, PIN_CLK, PIN_RST);

void display_root()
{
    Serial.end();
    display.fillRect(0, sz_scroll * sz_height, sz_width, sz_height, ST77XX_BLACK);
    display.setCursor(0, sz_scroll * sz_height);
    display.print(root);
    display.print(buffer);
    //display.println(buffer);
    Serial.begin(BAUD);
}

void display_flush()
{
    Serial.end();
    display.setCursor(0, 0);
    for (int i = 0; i < sz_scroll; ++i)
    {
        display.fillRect(0, i * sz_height, sz_width, sz_height, ST77XX_BLACK);
        display.setCursor(0, i * sz_height);
        display.println(scroll[i]);
    }
    Serial.begin(BAUD);
    display_root();
    Serial.end();
    Serial.begin(BAUD);
}

void display_reset()
{
    Serial.end();
    digitalWrite(PIN_GND, LOW);
    digitalWrite(PIN_VCC, HIGH);
    digitalWrite(PIN_CLK, LOW);
    digitalWrite(PIN_DAT, LOW);
    digitalWrite(PIN_RST, HIGH);
    digitalWrite(PIN_DC, LOW);
    digitalWrite(PIN_CS, LOW);
    digitalWrite(PIN_BL, HIGH);
    display.initR(INITR_GREENTAB);
    display.setRotation(3);
    display.fillScreen(ST77XX_BLACK);
    display.setTextSize(1);
    display.setTextColor(ST77XX_BLUE); //Turns out Red
    Serial.flush();
    Serial.begin(BAUD);
    Serial.println();
    display_flush();
    Serial.end();
    digitalWrite(PIN_CS, LOW);
    digitalWrite(PIN_DC, LOW);
    digitalWrite(PIN_DAT, LOW);
    digitalWrite(PIN_CLK, LOW);
    digitalWrite(PIN_RST, HIGH);
    Serial.flush();
    Serial.begin(BAUD);
    Serial.println();
    Serial.println();
}

void buffer_clear()
{
    for (int i = 0; i < sz_buffer; ++i)
    {
        buffer[i] = '\0';
    }
    pos = 0;
}

void buffer_char()
{
    if (pos < sz_buffer)
    {
        Serial.print(c);
        buffer[pos] = c;
        ++pos;
    }
}

void buffer_drop()
{
    Serial.print('\r');
    pos = 0;
}

void buffer_push()
{
    Serial.println();
    for (int j = 0; j < sz_scroll; ++j)
    {
        for (int i = 0; i < sz_buffer; ++i)
        {
            scroll[j][i] = scroll[j + 1][i];
        }
    }
    for (int i = 0; i < sz_buffer; ++i)
    {
        scroll[sz_scroll][i] = buffer[i];
    }
    buffer_clear();
    display_flush();
}

void buffer_back()
{
    if (pos > 0)
    {
        Serial.print("\b \b");
        --pos;
        buffer[pos] = '\0';
    }
}

void buffer_tabs()
{
    for (int i = 0; i < sz_tabs; ++i)
    {
        if (pos < sz_buffer)
        {
            Serial.print(' ');
            buffer[pos] = ' ';
            ++pos;
        }
    }
}

void setup()
{   
    pinMode(PIN_GND, OUTPUT);
    pinMode(PIN_VCC, OUTPUT);
    pinMode(PIN_BL, OUTPUT);
    Serial.begin(BAUD);
    display_reset();
}

void loop()
{
    n = Serial.available();
    for (int i = 0; i < n; ++i)
    {
        c = Serial.read();
        //Serial.println((int)c);
        if (0 != D(c)) { buffer_char(); }
      //if (c == '\r') { buffer_drop(); }
      //if (c == '\n') { buffer_push(); }
      //if (c == '\b') { buffer_back(); }
        if (c == '\r') { buffer_drop(); buffer_push(); }
        if (c ==  127) { buffer_back(); }
        if (c == '\t') { buffer_tabs(); }
        display_root();
    }
    delay(interval);
}
