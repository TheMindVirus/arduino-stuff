//Morse Code Receiver/Transmitter v0.1
// - Alastair Cota - 10/08/2020
//Note: This should actually be done by logic hardware in e.g. an FPGA,
//      not an inaccurate software implementation like this!
//Note: RX pin of one board connects to TX pin of the other board.
//      For MKR boards change RX to pin 4 and TX to pin 5.

#include <Arduino.h>

#define MORSE_BITS   10

#define MAP_LENGTH     1024
#define UNMAP_LENGTH   256

class MORSE
{
public:
    void begin(double hertz = 1000.0f, uint16_t rx = 2, uint16_t tx = 3);
    void setFrequency(double hertz = 1000.0f);
    void setPins(uint16_t rx = 2, uint16_t tx = 3);
    void receive();
    void transmit();

private:
    uint16_t _rx;
    uint16_t _tx;
    uint32_t _time;
    volatile bool _input[MORSE_BITS];
    volatile bool _output[MORSE_BITS];
    char _charmap[MAP_LENGTH];
    uint16_t _charunmap[UNMAP_LENGTH];
    
    void _ZeroBuffers();
    void _MakeCharMap();
};

/*
char charmap[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
bool morse[chars][limit] =
[
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1], //0 (1023)
    [1, 0, 1, 1, 1, 1, 1, 1, 1, 1], //1 (1021)
    [1, 0, 1, 0, 1, 1, 1, 1, 1, 1], //2 (1013)
    [1, 0, 1, 0, 1, 0, 1, 1, 1, 1], //3 (981)
    [1, 0, 1, 0, 1, 0, 1, 0, 1, 1], //4 (853)
    [1, 0, 1, 0, 1, 0, 1, 0, 1, 0], //5 (341)
    [1, 1, 1, 0, 1, 0, 1, 0, 1, 0], //6 (343)
    [1, 1, 1, 1, 1, 0, 1, 0, 1, 0], //7 (351)
    [1, 1, 1, 1, 1, 1, 1, 0, 1, 0], //8 (383)
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 0], //9 (511)
    [1, 0, 1, 1, 0, 0, 0, 0, 0, 0], //A (13)
    [1, 1, 1, 0, 1, 0, 1, 0, 0, 0], //B (87)
    [1, 1, 1, 0, 1, 1, 1, 0, 0, 0], //C (119)
    [1, 1, 1, 0, 1, 0, 0, 0, 0, 0], //D (23)
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0], //E (1)
    [1, 0, 1, 0, 1, 1, 1, 0, 0, 0], //F (117)
    [1, 1, 1, 1, 1, 0, 0, 0, 0, 0], //G (31)
    [1, 0, 1, 0, 1, 0, 1, 0, 0, 0], //H (85)
    [1, 0, 1, 0, 0, 0, 0, 0, 0, 0], //I (5)
    [1, 0, 1, 1, 1, 1, 1, 1, 0, 0], //J (253)
    [1, 1, 1, 0, 1, 1, 0, 0, 0, 0], //K (55)
    [1, 0, 1, 1, 1, 0, 1, 0, 0, 0], //L (93)
    [1, 1, 1, 1, 0, 0, 0, 0, 0, 0], //M (15)
    [1, 1, 1, 0, 0, 0, 0, 0, 0, 0], //N (7)
    [1, 1, 1, 1, 1, 1, 0, 0, 0, 0], //O (63)
    [1, 0, 1, 1, 1, 1, 1, 0, 0, 0], //P (125)
    [1, 1, 1, 1, 1, 0, 1, 1, 0, 0], //Q (223)
    [1, 0, 1, 1, 1, 0, 0, 0, 0, 0], //R (29)
    [1, 0, 1, 0, 1, 0, 0, 0, 0, 0], //S (21)
    [1, 1, 0, 0, 0, 0, 0, 0, 0, 0], //T (3)
    [1, 0, 1, 0, 1, 1, 0, 0, 0, 0], //U (53)
    [1, 0, 1, 0, 1, 0, 1, 1, 0, 0], //V (213)
    [1, 0, 1, 1, 1, 1, 0, 0, 0, 0], //W (61)
    [1, 1, 1, 0, 1, 0, 1, 1, 0, 0], //X (215)
    [1, 1, 1, 0, 1, 1, 1, 1, 0, 0], //Y (247)
    [1, 1, 1, 1, 1, 0, 1, 0, 0, 0]  //Z (95)
]; //TODO Make Hashing Table
*/
