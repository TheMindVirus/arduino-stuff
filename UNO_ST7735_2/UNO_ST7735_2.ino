const uint8_t Rcmd[] PROGMEM =
{
    0x18,
    0x11, 0x80, 0x96,
    0x11, 0x80, 0xFF,
    0xB1, 0x03, 0x01, 0x01, 0x01,
    0xB2, 0x03, 0x01, 0x01, 0x01,
    0xB3, 0x06, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0xB4, 0x01, 0x07,
    0xC0, 0x03, 0xA2, 0x02, 0x84,
    0xC1, 0x01, 0xC5,
    0xC2, 0x02, 0x0A, 0x00,
    0xC3, 0x02, 0x8A, 0x2A,
    0xC4, 0x02, 0x8A, 0xEE,
    0xC5, 0x01, 0x0E,
    0x20, 0x00,
    0x36, 0x01, 0xC8,
    0x3A, 0x01, 0x05,
    0x2A, 0x04, 0x00, 0x01, 0x00, 0xA0,
    0x2B, 0x04, 0x00, 0x02, 0x00, 0x81,
    0xE0, 0x10, 0x02, 0x1C, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2D, 0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10,
    0xE1, 0x10, 0x03, 0x1D, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D, 0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10,
    0x13, 0x80, 0x0A,
    0x29, 0x80, 0x64,
    0x36, 0x01, 0xC0,
    0x36, 0x01, 0xA0,
    0x2C, 0x00
};

void spi_write(uint8_t b)
{
    register uint8_t b1 = (uint8_t)(b & 0xFF);
    register uint8_t b2 = (uint8_t)((b >> 8) & 0xFF);
    register uint8_t b3 = PORTD;
    asm volatile
    (
        "sbrc %0, 7" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %0, 7" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %0, 6" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %0, 6" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %0, 5" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %0, 5" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %0, 4" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %0, 4" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %0, 3" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %0, 3" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %0, 2" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %0, 2" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %0, 1" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %0, 1" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %0, 0" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %0, 0" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"
        
        : "+r" (b1), "+r" (b2), "+r" (b3) :
    );
}

void send_command(uint8_t cmd, uint8_t* addr = 0, size_t na = 0)
{
     digitalWrite(6, LOW);
     digitalWrite(5, LOW);
     spi_write(cmd);
     digitalWrite(5, HIGH);
     for (size_t i = 0; i < na; ++i) { spi_write(pgm_read_byte(addr + i)); }
     digitalWrite(6, HIGH);
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

void write_pixel(uint16_t chroma = 0xF800)
{
    register uint8_t c1 = (uint8_t)(chroma & 0xFF);
    register uint8_t c2 = (uint8_t)((chroma >> 8) & 0xFF);
    register uint8_t c3 = PORTD;
    asm volatile
    ( 
        "sbrc %1, 7" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %1, 7" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %1, 6" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %1, 6" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %1, 5" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %1, 5" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %1, 4" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %1, 4" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %1, 3" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %1, 3" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %1, 2" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %1, 2" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %1, 1" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %1, 1" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %1, 0" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %1, 0" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %0, 7" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %0, 7" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %0, 6" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %0, 6" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %0, 5" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %0, 5" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %0, 4" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %0, 4" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %0, 3" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %0, 3" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %0, 2" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %0, 2" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %0, 1" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %0, 1" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"

        "sbrc %0, 0" "\n" "sbi 0x0B, 3" "\n"
        "sbrs %0, 0" "\n" "cbi 0x0B, 3" "\n"
        "sbi 0x0B,2" "\n" "cbi 0x0B, 2" "\n"
        
        : "+r" (c1), "+r" (c2), "+r" (c3) :
    );
}

void fill_screen()
{
    asm volatile("cli");
    for (size_t i = 0; i < 20480; ++i) { write_pixel(); }
    asm volatile("sei");
}

void setup()
{
    asm volatile
    (
        "ldi r16, 0b11111111" "\n" "out 0x0A, r16" "\n"
        "ldi r16, 0b10010010" "\n" "out 0x0B, r16" "\n"
        "ldi r22, 0x64" "\n" "ldi r23, 0x00" "\n" "ldi r24, 0x00" "\n" "ldi r25, 0x00" "\n" "call delay" "\n"
        "ldi r16, 0b10000010" "\n" "out 0x0B, r16" "\n"
        "ldi r22, 0x64" "\n" "ldi r23, 0x00" "\n" "ldi r24, 0x00" "\n" "ldi r25, 0x00" "\n" "call delay" "\n"
        "ldi r16, 0b11010010" "\n" "out 0x0B, r16" "\n"
        "ldi r22, 0xC8" "\n" "ldi r23, 0x00" "\n" "ldi r24, 0x00" "\n" "ldi r25, 0x00" "\n" "call delay" "\n"
        : : "p" (delay) :
    );
    start_display(Rcmd);
    digitalWrite(6, LOW);
    fill_screen();
}

void loop()
{
    //Backlight Blink PORTD in Atmega328P AVR8 Inline Assembly
    asm volatile
    (
        "sbi 0x0B, 7" "\n" "ldi r22, 0xE8" "\n" "ldi r23, 0x03" "\n" "ldi r24, 0x00" "\n" "ldi r25, 0x00" "\n" "call delay" "\n"
        "cbi 0x0B, 7" "\n" "ldi r22, 0xE8" "\n" "ldi r23, 0x03" "\n" "ldi r24, 0x00" "\n" "ldi r25, 0x00" "\n" "call delay" "\n"
        : : "p" (delay) :
    );
}
