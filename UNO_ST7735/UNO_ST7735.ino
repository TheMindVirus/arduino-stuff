#define ST7735_GND   0
#define ST7735_VCC   1
#define ST7735_SCL   2
#define ST7735_SDA   3
#define ST7735_RES   4
#define ST7735_DC    5
#define ST7735_CS    6
#define ST7735_BL    7

#define ST7735_WIDTH    160
#define ST7735_HEIGHT   128
#define ST7735_PIXELS   (ST7735_WIDTH * ST7735_HEIGHT)

#define ST7735_WOFF1   1
#define ST7735_HOFF1   2
#define ST7735_WOFF2   1
#define ST7735_HOFF2   2

#define ST7735_BLACK     0x0000
#define ST7735_WHITE     0xFFFF
#define ST7735_RED       0xF800
#define ST7735_GREEN     0x07E0
#define ST7735_BLUE      0x001F
#define ST7735_CYAN      0x07FF
#define ST7735_MAGENTA   0xF81F
#define ST7735_YELLOW    0xFFE0
#define ST7735_ORANGE    0xFC00

//#define ST7735_FPS   0x01, 0x2C, 0x2D
#define ST7735_FPS   0x01, 0x01, 0x01

const uint8_t Rcmd1[] PROGMEM =
{
    0x0F,
    0x11, 0x80, 0xFF,
    0xB1, 0x03, ST7735_FPS,
    0xB2, 0x03, ST7735_FPS,
    0xB3, 0x06, ST7735_FPS, ST7735_FPS,
    0xB4, 0x01, 0x07,
    0xC0, 0x03, 0xA2, 0x02, 0x84,
    0xC1, 0x01, 0xC5,
    0xC2, 0x02, 0x0A, 0x00,
    0xC3, 0x02, 0x8A, 0x2A,
    0xC4, 0x02, 0x8A, 0xEE,
    0xC5, 0x01, 0x0E,
    0x20, 0x00,
    0x36, 0x01, 0xC8,
    0x3A, 0x01, 0x05
};

const uint8_t Rcmd2[] PROGMEM =
{
    0x02,
    0x2A, 0x04, 0x00, ST7735_WOFF1, 0x00, ((ST7735_WIDTH - 1) + ST7735_WOFF2),
    0x2B, 0x04, 0x00, ST7735_HOFF1, 0x00, ((ST7735_HEIGHT - 1) + ST7735_HOFF2)
};

const uint8_t Rcmd3[] PROGMEM =
{
    0x04,
    0xE0, 0x10, 0x02, 0x1C, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2D, 0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10,
    0xE1, 0x10, 0x03, 0x1D, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D, 0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10,
    0x13, 0x80, 0x0A,
    0x29, 0x80, 0x64
};

const uint8_t R[] PROGMEM =
{
    (0x40 | 0x80 | 0x00),
    (0x80 | 0x20 | 0x00),
    (0x00 | 0x00 | 0x00),
    (0x40 | 0x20 | 0x00)
};

void spi_write(uint16_t b, size_t bits = 16)
{
    size_t l = 1 << (bits - 1);
    for (size_t i = 0; i < bits; ++i)
    {
        digitalWrite(ST7735_SDA, (b & l) ? HIGH : LOW);
        digitalWrite(ST7735_SCL, HIGH);
        digitalWrite(ST7735_SCL, LOW);
        b <<= 1;
    }
}

void send_command(uint8_t cmd, uint8_t* addr = 0, size_t na = 0)
{
     digitalWrite(ST7735_CS, LOW);
     digitalWrite(ST7735_DC, LOW);
     spi_write(cmd, 8);
     digitalWrite(ST7735_DC, HIGH);
     for (size_t i = 0; i < na; ++i) { spi_write(pgm_read_byte(addr + i), 8); }
     digitalWrite(ST7735_CS, HIGH);
}

void start_display(uint8_t* commands)
{
    size_t idx = 0;
    size_t nc = pgm_read_byte(commands + idx++);
    size_t na = 0;
    size_t ms = 0;
    uint8_t cmd = 0;
    for (size_t i = 0; i < nc; ++i)
    {
        cmd = pgm_read_byte(commands + idx++);
        na = pgm_read_byte(commands + idx++);
        ms = na & 0x80;
        na &= 0x7F;
        send_command(cmd, commands + idx, na);
        idx += na;
        if (ms)
        {
            ms = pgm_read_byte(commands + idx++);
            if (ms == 0xFF) { ms = 500; }
            delay(ms);
        }
    }
}

void rotate_display(size_t r = 0)
{
    send_command(0x36, pgm_read_byte(R + (r % 4)), 1);
}

void reset_display(size_t r = 0)
{
    digitalWrite(ST7735_SDA, LOW);
    digitalWrite(ST7735_SCL, LOW);
    digitalWrite(ST7735_RES, HIGH);
    delay(100);
    digitalWrite(ST7735_RES, LOW);
    delay(100);
    digitalWrite(ST7735_RES, HIGH);
    delay(200);
    digitalWrite(ST7735_CS, HIGH);
    start_display(Rcmd1);
    start_display(Rcmd2);
    start_display(Rcmd3);
    rotate_display(0);
    rotate_display(r);
    send_command(0x2C);
    digitalWrite(ST7735_CS, LOW);
}
/*
void write_pixel(uint16_t b = ST7735_RED)
{
    for (size_t i = 0; i < 16; ++i)
    {
        digitalWrite(ST7735_SDA, (b & 0x8000) ? HIGH : LOW);
        digitalWrite(ST7735_SCL, HIGH);
        digitalWrite(ST7735_SCL, LOW);
        b <<= 1;
    }
}
*/

/*
void write_pixel(uint16_t b = ST7735_RED)
{
    (b & 0b1000000000000000) ? (PORTD |= 0b00001000) : (PORTD &= 0b11110111);
    PORTD |= 0b00000100; PORTD &= 0b11111011;
    (b & 0b0100000000000000) ? (PORTD |= 0b00001000) : (PORTD &= 0b11110111);
    PORTD |= 0b00000100; PORTD &= 0b11111011;
    (b & 0b0010000000000000) ? (PORTD |= 0b00001000) : (PORTD &= 0b11110111);
    PORTD |= 0b00000100; PORTD &= 0b11111011;
    (b & 0b0001000000000000) ? (PORTD |= 0b00001000) : (PORTD &= 0b11110111);
    PORTD |= 0b00000100; PORTD &= 0b11111011;
    (b & 0b0000100000000000) ? (PORTD |= 0b00001000) : (PORTD &= 0b11110111);
    PORTD |= 0b00000100; PORTD &= 0b11111011;
    (b & 0b0000010000000000) ? (PORTD |= 0b00001000) : (PORTD &= 0b11110111);
    PORTD |= 0b00000100; PORTD &= 0b11111011;
    (b & 0b0000001000000000) ? (PORTD |= 0b00001000) : (PORTD &= 0b11110111);
    PORTD |= 0b00000100; PORTD &= 0b11111011;
    (b & 0b0000000100000000) ? (PORTD |= 0b00001000) : (PORTD &= 0b11110111);
    PORTD |= 0b00000100; PORTD &= 0b11111011;
    (b & 0b0000000010000000) ? (PORTD |= 0b00001000) : (PORTD &= 0b11110111);
    PORTD |= 0b00000100; PORTD &= 0b11111011;
    (b & 0b0000000001000000) ? (PORTD |= 0b00001000) : (PORTD &= 0b11110111);
    PORTD |= 0b00000100; PORTD &= 0b11111011;
    (b & 0b0000000000100000) ? (PORTD |= 0b00001000) : (PORTD &= 0b11110111);
    PORTD |= 0b00000100; PORTD &= 0b11111011;
    (b & 0b0000000000010000) ? (PORTD |= 0b00001000) : (PORTD &= 0b11110111);
    PORTD |= 0b00000100; PORTD &= 0b11111011;
    (b & 0b0000000000001000) ? (PORTD |= 0b00001000) : (PORTD &= 0b11110111);
    PORTD |= 0b00000100; PORTD &= 0b11111011;
    (b & 0b0000000000000100) ? (PORTD |= 0b00001000) : (PORTD &= 0b11110111);
    PORTD |= 0b00000100; PORTD &= 0b11111011;
    (b & 0b0000000000000010) ? (PORTD |= 0b00001000) : (PORTD &= 0b11110111);
    PORTD |= 0b00000100; PORTD &= 0b11111011;
    (b & 0b0000000000000001) ? (PORTD |= 0b00001000) : (PORTD &= 0b11110111);
    PORTD |= 0b00000100; PORTD &= 0b11111011;
}
*/

void write_pixel(uint16_t chroma = ST7735_RED)
{
    asm volatile
    (
        "in r16, 0x0B" "\n"
      
        "sbrs %0, 7" "\n" "ori r16,0b00001000" "\n"
        "sbrc %0, 7" "\n" "andi r16,0b11110111" "\n"
        "ori r16,0b00000100" "\n" "out 0x0B,r16" "\n"
        "andi r16,0b11111011" "\n" "out 0x0B,r16" "\n"

        "sbrs %0, 6" "\n" "ori r16,0b00001000" "\n"
        "sbrc %0, 6" "\n" "andi r16,0b11110111" "\n"
        "ori r16,0b00000100" "\n" "out 0x0B,r16" "\n"
        "andi r16,0b11111011" "\n" "out 0x0B,r16" "\n"

        "sbrs %0, 5" "\n" "ori r16,0b00001000" "\n"
        "sbrc %0, 5" "\n" "andi r16,0b11110111" "\n"
        "ori r16,0b00000100" "\n" "out 0x0B,r16" "\n"
        "andi r16,0b11111011" "\n" "out 0x0B,r16" "\n"

        "sbrs %0, 4" "\n" "ori r16,0b00001000" "\n"
        "sbrc %0, 4" "\n" "andi r16,0b11110111" "\n"
        "ori r16,0b00000100" "\n" "out 0x0B,r16" "\n"
        "andi r16,0b11111011" "\n" "out 0x0B,r16" "\n"

        "sbrs %0, 3" "\n" "ori r16,0b00001000" "\n"
        "sbrc %0, 3" "\n" "andi r16,0b11110111" "\n"
        "ori r16,0b00000100" "\n" "out 0x0B,r16" "\n"
        "andi r16,0b11111011" "\n" "out 0x0B,r16" "\n"

        "sbrs %0, 2" "\n" "ori r16,0b00001000" "\n"
        "sbrc %0, 2" "\n" "andi r16,0b11110111" "\n"
        "ori r16,0b00000100" "\n" "out 0x0B,r16" "\n"
        "andi r16,0b11111011" "\n" "out 0x0B,r16" "\n"

        "sbrs %0, 1" "\n" "ori r16,0b00001000" "\n"
        "sbrc %0, 1" "\n" "andi r16,0b11110111" "\n"
        "ori r16,0b00000100" "\n" "out 0x0B,r16" "\n"
        "andi r16,0b11111011" "\n" "out 0x0B,r16" "\n"

        "sbrs %0, 0" "\n" "ori r16,0b00001000" "\n"
        "sbrc %0, 0" "\n" "andi r16,0b11110111" "\n"
        "ori r16,0b00000100" "\n" "out 0x0B,r16" "\n"
        "andi r16,0b11111011" "\n" "out 0x0B,r16" "\n"

        "sbrs %1, 7" "\n" "ori r16,0b00001000" "\n"
        "sbrc %1, 7" "\n" "andi r16,0b11110111" "\n"
        "ori r16,0b00000100" "\n" "out 0x0B,r16" "\n"
        "andi r16,0b11111011" "\n" "out 0x0B,r16" "\n"

        "sbrs %1, 6" "\n" "ori r16,0b00001000" "\n"
        "sbrc %1, 6" "\n" "andi r16,0b11110111" "\n"
        "ori r16,0b00000100" "\n" "out 0x0B,r16" "\n"
        "andi r16,0b11111011" "\n" "out 0x0B,r16" "\n"

        "sbrs %1, 5" "\n" "ori r16,0b00001000" "\n"
        "sbrc %1, 5" "\n" "andi r16,0b11110111" "\n"
        "ori r16,0b00000100" "\n" "out 0x0B,r16" "\n"
        "andi r16,0b11111011" "\n" "out 0x0B,r16" "\n"

        "sbrs %1, 4" "\n" "ori r16,0b00001000" "\n"
        "sbrc %1, 4" "\n" "andi r16,0b11110111" "\n"
        "ori r16,0b00000100" "\n" "out 0x0B,r16" "\n"
        "andi r16,0b11111011" "\n" "out 0x0B,r16" "\n"

        "sbrs %1, 3" "\n" "ori r16,0b00001000" "\n"
        "sbrc %1, 3" "\n" "andi r16,0b11110111" "\n"
        "ori r16,0b00000100" "\n" "out 0x0B,r16" "\n"
        "andi r16,0b11111011" "\n" "out 0x0B,r16" "\n"

        "sbrs %1, 2" "\n" "ori r16,0b00001000" "\n"
        "sbrc %1, 2" "\n" "andi r16,0b11110111" "\n"
        "ori r16,0b00000100" "\n" "out 0x0B,r16" "\n"
        "andi r16,0b11111011" "\n" "out 0x0B,r16" "\n"

        "sbrs %1, 1" "\n" "ori r16,0b00001000" "\n"
        "sbrc %1, 1" "\n" "andi r16,0b11110111" "\n"
        "ori r16,0b00000100" "\n" "out 0x0B,r16" "\n"
        "andi r16,0b11111011" "\n" "out 0x0B,r16" "\n"

        "sbrs %1, 0" "\n" "ori r16,0b00001000" "\n"
        "sbrc %1, 0" "\n" "andi r16,0b11110111" "\n"
        "ori r16,0b00000100" "\n" "out 0x0B,r16" "\n"
        "andi r16,0b11111011" "\n" "out 0x0B,r16" "\n"
        
        : : "r" ((uint8_t)((chroma >> 8) & 0xFF)), "r" ((uint8_t)(chroma & 0xFF)) :
    );
}

void fill_screen(uint16_t b = ST7735_RED)
{
    cli();
    for (size_t i = 0; i < ST7735_PIXELS; ++i) { write_pixel(b); }
    sei();
}

void setup()
{
    Serial.begin(115200);
  
    pinMode(ST7735_GND, OUTPUT);
    pinMode(ST7735_VCC, OUTPUT);
    pinMode(ST7735_SCL, OUTPUT);
    pinMode(ST7735_SDA, OUTPUT);
    pinMode(ST7735_RES, OUTPUT);
    pinMode(ST7735_DC, OUTPUT);
    pinMode(ST7735_CS, OUTPUT);
    pinMode(ST7735_BL, OUTPUT);

    digitalWrite(ST7735_GND, LOW);
    digitalWrite(ST7735_VCC, LOW);
    digitalWrite(ST7735_SCL, LOW);
    digitalWrite(ST7735_SDA, LOW);
    digitalWrite(ST7735_RES, LOW);
    digitalWrite(ST7735_DC, LOW);
    digitalWrite(ST7735_CS, LOW);
    digitalWrite(ST7735_BL, LOW);

    //digitalWrite(ST7735_VCC, HIGH);
    //digitalWrite(ST7735_RES, HIGH);
    //digitalWrite(ST7735_BL, HIGH);

    uint8_t a = 1; //Set Backlight
    uint8_t b = 0; //Clear Backlight (Overrides Set)
    asm volatile
    (
        "ldi r16, 0"           "\n"
        "ldi r17, 0"           "\n"
        
        "cpi %2, 0"            "\n"
        "in r17, 0x3F"         "\n"
        "sbrs r17, 1"          "\n"
        "ori r16, 0b10010010"  "\n"

        "ldi r17, 0"           "\n"
        "clz"                  "\n"
        
        "cpi %3, 0"            "\n"
        "in r17, 0x3F"         "\n"
        "sbrs r17, 1"          "\n"
        "andi r16, 0b01101101" "\n"

        "ldi r17, 0"           "\n"
        "out 0x0B, r16"        "\n"
        "ldi r16, 0"           "\n"

        "mov %0, %2"           "\n"
        "mov %1, %3"           "\n"

        : "=r" (a), "=r" (b) : "r" (a), "r" (b) :
    );

    for (size_t i = 0; i < 10; ++i)
    {
        char tmp[255];
        sprintf(tmp, "Flash: 0x%02x | PROGMEM: 0x%02x | Indirect: 0x%02x",
                Rcmd1[i], pgm_read_byte(Rcmd1 + i), pgm_read_byte(Rcmd1[i]));
        Serial.println(tmp);
    }
    Serial.println();

    reset_display(1);
    fill_screen();
}

void loop()
{
    //Backlight Blink PORTD in Atmega328P AVR8 Inline Assembly
    //asm volatile("ldi r16, 0b10010010" "\n" "out 0x0B, r16");
    //delay(1000);
    //asm volatile("ldi r16, 0b00000000" "\n" "out 0x0B, r16");
    delay(1000);
}
