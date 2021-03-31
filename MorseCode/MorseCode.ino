//Morse Code Receiver/Transmitter v0.1
// - Alastair Cota - 10/08/2020
//Note: This should actually be done by logic hardware in e.g. an FPGA,
//      not an inaccurate software implementation like this!
//Note: RX pin of one board connects to TX pin of the other board.
//      For MKR boards change RX to pin 4 and TX to pin 5.

#include "morse.h"

MORSE Morse;

void setup()
{
    Serial.begin(115200);
    Serial.println("__Morse_Code__");
    Serial.println("Booting...");
    Morse.begin(1000);
    Serial.println("Done!");
}

void loop()
{
    Morse.receive();
    Morse.transmit();
}
