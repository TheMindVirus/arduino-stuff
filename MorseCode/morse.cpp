//Morse Code Receiver/Transmitter v0.1
// - Alastair Cota - 10/08/2020
//Note: This should actually be done by logic hardware in e.g. an FPGA,
//      not an inaccurate software implementation like this!
//Note: RX pin of one board connects to TX pin of the other board.
//      For MKR boards change RX to pin 4 and TX to pin 5.

#include "morse.h"

//Initialises the Morse Code Receiver/Transmitter
void MORSE::begin(double hertz, uint16_t rx, uint16_t tx)
{
    setFrequency(hertz);
    setPins(rx, tx);
    _ZeroBuffers();
    _MakeCharMap();
}

//Sets how fast the morse code communication takes place
void MORSE::setFrequency(double hertz = 1000.0f)
{
    _time = (uint32_t)(1000000.0f / hertz);
}

//Sets the pins for morse code communication
void MORSE::setPins(uint16_t rx, uint16_t tx)
{
    _rx = rx;
    _tx = tx;
    pinMode(_rx, INPUT);
    pinMode(_tx, OUTPUT);
    digitalWrite(_tx, LOW);
}

//Receives morse code and outputs serial data
void MORSE::receive()
{
    if(HIGH == digitalRead(_rx)) //Event
    {
        delayMicroseconds(_time / 2); //Avoid Sampling on Rising Edge 
        for(uint16_t i = 0; i < MORSE_BITS; ++i)
        {
            _input[i] = digitalRead(_rx); //Time Sensitive Buffering
            delayMicroseconds(_time); //Could be replaced with millis()
        }
        uint16_t total = 0;
        for(uint16_t i = 0; i < MORSE_BITS; ++i)
        {
            if(HIGH == _input[i]) { total += (1ul << i); } //Calculation (quick power 2 :) )
        }
        Serial.println(_charmap[total]); //Remapping
    }
}

//Transmits morse code from inputted serial data
void MORSE::transmit()
{
    if(0 < Serial.available()) //Event
    {
        char c = toUpperCase(Serial.read());
        uint16_t total = _charunmap[c]; //Remapping
        for(uint16_t i = 0; i < MORSE_BITS; ++i)
        {
            _output[i] = (bool)(total & (1ul << i)); //Calculation (quick log2 :) )
        }
        for(uint16_t i = 0; i < MORSE_BITS; ++i)
        {
            digitalWrite(_tx, _output[i]); //Time Sensitive Buffering
            delayMicroseconds(_time); //Could be replaced with millis()
        }
        digitalWrite(_tx, LOW);
        delayMicroseconds(_time * 2);
    }
}

//Initialises the input and output buffers to zero
void MORSE::_ZeroBuffers()
{
    for(uint16_t i = 0; i < MORSE_BITS; ++i)
    {
        _input[i] = 0;
        _output[i] = 0;
    }
}

//Initialises a morse code character map (AI Model!!!)
void MORSE::_MakeCharMap()
{
    for(uint16_t i = 0; i < MAP_LENGTH; ++i)
    {
        _charmap[i] = 0;
    }
    for(uint16_t i = 0; i < UNMAP_LENGTH; ++i)
    {
        _charunmap[i] = 0;
    }
    _charmap[1023] = '0'; _charunmap['0'] = 1023;
    _charmap[1021] = '1'; _charunmap['1'] = 1021;
    _charmap[1013] = '2'; _charunmap['2'] = 1013;
    _charmap[981]  = '3'; _charunmap['3'] = 981;
    _charmap[853]  = '4'; _charunmap['4'] = 853;
    _charmap[341]  = '5'; _charunmap['5'] = 341;
    _charmap[343]  = '6'; _charunmap['6'] = 343;
    _charmap[351]  = '7'; _charunmap['7'] = 351;
    _charmap[383]  = '8'; _charunmap['8'] = 383;
    _charmap[511]  = '9'; _charunmap['9'] = 511;
    _charmap[13]   = 'A'; _charunmap['A'] = 13;
    _charmap[87]   = 'B'; _charunmap['B'] = 87;
    _charmap[119]  = 'C'; _charunmap['C'] = 119;
    _charmap[23]   = 'D'; _charunmap['D'] = 23;
    _charmap[1]    = 'E'; _charunmap['E'] = 1;
    _charmap[117]  = 'F'; _charunmap['F'] = 117;
    _charmap[31]   = 'G'; _charunmap['G'] = 31;
    _charmap[85]   = 'H'; _charunmap['H'] = 85;
    _charmap[5]    = 'I'; _charunmap['I'] = 5;
    _charmap[253]  = 'J'; _charunmap['J'] = 253;
    _charmap[55]   = 'K'; _charunmap['K'] = 55;
    _charmap[93]   = 'L'; _charunmap['L'] = 93;
    _charmap[15]   = 'M'; _charunmap['M'] = 15;
    _charmap[7]    = 'N'; _charunmap['N'] = 7;
    _charmap[63]   = 'O'; _charunmap['O'] = 63;
    _charmap[125]  = 'P'; _charunmap['P'] = 125;
    _charmap[223]  = 'Q'; _charunmap['Q'] = 223;
    _charmap[29]   = 'R'; _charunmap['R'] = 29;
    _charmap[21]   = 'S'; _charunmap['S'] = 21;
    _charmap[3]    = 'T'; _charunmap['T'] = 3;
    _charmap[53]   = 'U'; _charunmap['U'] = 53;
    _charmap[213]  = 'V'; _charunmap['V'] = 213;
    _charmap[61]   = 'W'; _charunmap['W'] = 61;
    _charmap[215]  = 'X'; _charunmap['X'] = 215;
    _charmap[247]  = 'Y'; _charunmap['Y'] = 247;
    _charmap[95]   = 'Z'; _charunmap['Z'] = 95;
}
