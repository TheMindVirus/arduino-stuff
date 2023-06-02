//Redline Networking Experiment - Alastair Cota @08:10 02/06/2023
//Based on Powerline Networking for Ethernet over Mains Electricty
//A 2-pin Low-Power Half-Duplex Energy+Information Cable for Chipsets

#define BAUD_RATE 115200 //9600

#define PIN_PWM_LED 3 //LED_BUILTIN is not always PWM

#define TIMEOUT 100//ms
#define TIMEOUT_2X (TIMEOUT * 2)

#define DELAY 0

#define LVL 0.5 //between HIGH and LOW (LVL|LEVEL|MEDIUM)

#define WHOLE int
#define NUMBER double

#define FULL 255 //0xFF
#define HALF 127 //0x7F
#define NONE 0   //0x00

#define VOID void
#define BOOL bool
#define TRUE true
#define FALSE false

#define IF if
#define ELSE else
#define SETUP setup
#define LOOP loop

#define NOT !
#define AND &&
#define OR ||

#define MOD %
#define END ;
#define QUERY ?
#define ALT :

#define IS =
#define MATCHES ==

#define LESS_THAN <
#define MORE_THAN >
#define LESS_EQUAL <=
#define MORE_EQUAL >=

#define DOT "."
#define SPACE " "
#define HEXMAP "0123456789ABCDEF"
#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

#define CLOCK() millis()
#define MODE(PIN, SETTING) pinMode(PIN, SETTING)
#define READ(PIN) analogRead(PIN)
#define WRITE(PIN, VALUE) analogWrite(PIN, VALUE)

#define LAUNCH(RATE) Serial.begin(RATE)
#define PRINT(DATA) Serial.print(DATA)
#define PRINT_LINE(DATA) Serial.println(DATA)

#define SLEEP(MS) delay(MS / 1000)
#define SLEEP_MS(MS) delay(MS)
#define SLEEP_US(US) delayMicroseconds(MS)

#define IN INPUT
#define OUT OUTPUT

#define LABEL "Redline" ": "

BOOL STATE IS TRUE END
BOOL LOCK IS FALSE END
WHOLE TIME IS NONE END
NUMBER LEVEL IS NONE END

VOID SETUP()
{
  LAUNCH(BAUD_RATE) END
  PRINT(NONE) END PRINT(SPACE) END PRINT_LINE(FULL) END
  MODE(PIN_PWM_LED, OUT) END
  WRITE(PIN_PWM_LED, HALF) END
}

VOID LOOP()
{
  TIME IS CLOCK() MOD TIMEOUT_2X END
  IF ((NOT LOCK) AND (TIME LESS_THAN TIMEOUT))
  {
    LEVEL IS STATE QUERY FULL ALT HALF END
    PRINT(LABEL) END PRINT_LINE(LEVEL) END
    WRITE(PIN_PWM_LED, LEVEL) END
    STATE IS NOT STATE END
    LOCK IS TRUE END
  }
  ELSE IF ((LOCK MATCHES TRUE)
  AND (TIME MORE_THAN TIMEOUT)) { LOCK IS FALSE END }
  SLEEP(DELAY) END
}
