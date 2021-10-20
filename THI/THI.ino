#include "./SparkFunDMXMod/src/SparkFunDMX.h"
#include "./SparkFunDMXMod/src/SparkFunDMX.cpp"
//Add Tinker.it DMX Shield, Jump A0 to Pin3

const char* MAGIC = "THI";
const size_t MAGIC_LEN = strlen(MAGIC);
const size_t DMX_MAX = 6; //512;
//"THICCCCCCCCCCCC" is a valid command for dim white

String data = "";
String cmd = "";
size_t len = 0;
size_t ptr = 0;
size_t cha = 0;
SparkFunDMX DMX;

const String charmap = "0123456789ABCDEF";
int HEX2INT(String hexstr)
{
  int val = 0;
  char c = '\0';
  int idx = 0;
  hexstr.toUpperCase();
  size_t len2 = hexstr.length();
  for (size_t i = 1; i <= len2; ++i)
  {
    c = (char)(hexstr[i - 1]);
    idx = charmap.indexOf(c);
    if (idx >= 0)
    {
      val += idx << (4 * (len2 - i));
    }
  }
  return val;
}

void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(10);
  DMX.initWrite(DMX_MAX);
}

void loop()
{
  cmd = Serial.readStringUntil('\n');
  cmd.replace('\r', '\0');
  len = cmd.length();
  if (len > 0)
  {
    if (0 == strncmp(cmd.c_str(), MAGIC, MAGIC_LEN))
    {
      for (size_t i = 1; i < (len - MAGIC_LEN); i += 2)
      {
        cha = (i + 1) / 2;
        if (cha <= (DMX_MAX + 1))
        {
          ptr = MAGIC_LEN + i;
          data = cmd.substring(ptr - 1, ptr + 1);
          DMX.write(cha, HEX2INT(data) & 0xFF);
          Serial.println(HEX2INT(data) & 0xFF);
        }
      }
    }
    Serial.println(cmd);
  }
  DMX.update();
}
