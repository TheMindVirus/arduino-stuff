#include <WiFi.h>
#include <ESPmDNS.h>
#include <AsyncUDP.h>
#include ".\SparkFunDMXMod\src\SparkFunDMX.h"
#include ".\SparkFunDMXMod\src\SparkFunDMX.cpp"
//Add Tinker.it DMX Shield, Jump A0 to Pin3

const char* HOSTNAME = "MAIXDMX512";

const uint32_t BAUD = 115200;
const char* SSID = "<SSID>";
const char* PSWD = "<PSWD>";
const uint32_t PORT = 1234;

const uint32_t TIMEOUT = 1000;

const char* MAGIC = "MAIXDMX512";
const size_t MAGIC_LEN = strlen(MAGIC);
const size_t DMX_MAX = 16; //512;
const size_t NET_MAX = 1024;

AsyncUDP UDP;
SparkFunDMX DMX;
uint8_t data[NET_MAX + 1] = {0};

void setup()
{
    Serial.begin(BAUD);
    DMX.initWrite(DMX_MAX);
    delay(TIMEOUT);
}

void loop()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.print("\n[INFO]: Reconnecting...");
        WiFi.setSleep(false);
        WiFi.begin(SSID, PSWD);
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(TIMEOUT);
            Serial.print(".");
        }
        MDNS.begin(HOSTNAME);
        Serial.println("\n[INFO]: Connected");
        Serial.print("[INFO]: Hostname: ");
        Serial.print(HOSTNAME);
        Serial.print(".local:");
        Serial.println(PORT);
        Serial.print("[INFO]: IP Address: ");
        Serial.print(WiFi.localIP());
        Serial.print(":");
        Serial.println(PORT);
    }
    if (UDP.listen(PORT))
    {
        UDP.onPacket([](AsyncUDPPacket packet)
        {
            Serial.println(packet.length());
            strncpy((char*)data, (char*)packet.data(), packet.length());
            if (0 == strncmp((char*)data, MAGIC, MAGIC_LEN))
            {
                for (size_t i = 1; i <= DMX_MAX; ++i)
                {
                    DMX.write(i, data[MAGIC_LEN + i]);
                }
            }
            Serial.println((char*)data);
        });
    }
    DMX.update();
}
