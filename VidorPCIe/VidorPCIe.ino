#include "VidorPeripherals.h"
//#include "VidorGraphics.h"
#include "VidorPCIe.h"

bool blink_state = false;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    
    Serial.begin(115200);
    while (!Serial);
    Serial.println("[SAMD]: MKR Vidor 4000");
    
    Serial.println("[SAMD]: Starting FPGA...");
    FPGA.begin();
    Serial.print("[SAMD]: FPGA Version: ");
    Serial.println(FPGA.version(), HEX);
    Serial.print("[SAMD]: FPGA Config: ");
    FPGA.printConfig();
    
    FPGA.pinMode(33, OUTPUT); //A0
    pinMode(A0, INPUT);
    FPGA.digitalWrite(33, HIGH);
    Serial.print("[SAMD]: FPGA Status: ");
    Serial.println(digitalRead(A0) == HIGH ? "Online" : "Offline");

    Serial.println("[SAMD]: Initialising FPGA Interfaces");
    WireFPGA1.begin();
    SPIFPGA1.begin();
    SerialFPGA1.begin(115200);
    while (!SerialFPGA1);
    //I2C? PCM? USIM? USB?
    
    Serial.println("[SAMD]: Resetting PCIe Bus");
    FPGA.pinMode(PEX_RST, OUTPUT);
    FPGA.digitalWrite(PEX_RST, HIGH);
    delay(100);
    FPGA.digitalWrite(PEX_RST, LOW);
    //Maybe also PCI Express Pin 1 as well as 22?

    Serial.println("[SAMD]: Reconfiguring PCIe Bus Pins");
    for (size_t i = 0; i < PEX_IO_COUNT; ++i)
    {
        FPGA.pinMode(PEX_IO_PINS[i], INPUT);
    }

    Serial.println("[SAMD]: Reading PCIe Bus Pins");
    for (size_t i = 0; i < PEX_IO_COUNT; ++i)
    {
        Serial.print("[SAMD]: ");
        Serial.print(PEX_IO_LABELS[i]);
        Serial.print(" = ");
        Serial.println(FPGA.digitalRead(PEX_IO_PINS[i]));
    }

    //TODO: Query [NINA]: for extra 2 PCIe Bus Pins
    //Serial.println("[SAMD]: Querying NINA for PCIe Bus Pins");

    Serial.println("[SAMD]: Shutting Down FPGA");
    FPGA.end();

    Serial.println("[SAMD]: Run Blink!");
}

void loop()
{
    if (millis() % 1000 > 100)
    {
        digitalWrite(LED_BUILTIN, (blink_state) ? HIGH : LOW);
        blink_state = !blink_state;
    }
}
