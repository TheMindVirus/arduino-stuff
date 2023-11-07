#include <Ethernet.h>

#define Server_localIP() Ethernet.localIP()
#define Server_localPort() 80 //DNS?
#define Server_remoteIP() Client.remoteIP()
#define Server_remotePort() Client.localPort()

#define Server_Idle            0
#define Server_RenewError      1
#define Server_RenewSuccess    2
#define Server_RebindError     3
#define Server_RebindSuccess   4
#define Server_InitSuccess     5

int status = Server_Idle;
byte MAC[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//IPAddress IP = { 192, 168, 1, 177 }; //DHCP?
EthernetServer Server(Server_localPort());
//EthernetClient Client();
bool BlankLine = true;
char TempChar = '\0';
bool OneShot = true;

const char Server_Data[] PROGMEM = 
"\
<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"100%\" height=\"100%\" style=\"background: #113\">\r\n\
\r\n\
<defs>\r\n\
  <filter id=\"blur\">\r\n\
    <feGaussianBlur stdDeviation=\"1.5\" />\r\n\
  </filter>\r\n\
</defs>\r\n\
\r\n\
<g id=\"Private\" fill=\"none\" stroke=\"#2DB7AD\" stroke-width=\"3\" stroke-linejoin=\"round\" stroke-linecap=\"round\">\r\n\
  <use href=\"#path-Disney\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Disney\" d=\"M1280,600,l50,0,s10,0,10,10,l0,20,s0,10,-10,10,s5,0,-5,0,l-50,-15,s-5,-2,-5,-10,l0,-5,s0,-10,10,-10\"/>\r\n\
  <use href=\"#path-Seibu-Yurakucho\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Seibu-Yurakucho\" d=\"M230,140,l-25,25,s-10,10,-20,10,l-96,0,s-10,0,-20,-10,l-10,-10\"/>\r\n\
  <use href=\"#path-Seibu-Ikebukuro\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Seibu-Ikebukuro\" d=\"M290,181,l-265,0\"/>\r\n\
  <use href=\"#path-Seibu-Shinjuku\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Seibu-Shinjuku\" d=\"M25,234,l20,0,s10,0,20,10,l10,10,s10,10,20,10,l130,0,s10,0,20,10,l15,15,s10,10,10,20,l0,120\"/>\r\n\
  <use href=\"#path-Tobu\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Tobu\" d=\"M290,181,l0,-20,s0,-10,-10,-20,l-45,-45,s-10,-10,-20,-10,l-135,0,s-10,0,-20,10\"/>\r\n\
  <use href=\"#path-Keio\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Keio\" d=\"M250,481,l-20,0,s-10,0,-20,10,l-10,10,s-10,10,-20,10,l-155,0\"/>\r\n\
  <use href=\"#path-Yoyogi\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Yoyogi\" d=\"M250,481,s-10,0,-20,10,l-20,20,s-10,10,-20,10,l-50,0,s-10,0,-20,-10,M250,481,l-117,117\"/>\r\n\
  <use href=\"#path-Odakyu\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Odakyu\" d=\"M175,600,l-150,0\"/>\r\n\
  <use href=\"#path-Inokashira\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Inokashira\" d=\"M255,640,l-75,0,s-10,0,-20,-10,l-135,-135\"/>\r\n\
  <use href=\"#path-Denentoshi\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Denentoshi\" d=\"M255,650,l-230,0\"/>\r\n\
  <use href=\"#path-Toyoko\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Toyoko\" d=\"M255,660,l-10,0,s-10,0,-20,10,l-30,30,s-10,10,-20,10,l-50,0,s-10,0,-20,10,l-15,15,s-10,10,-20,10,l-40,0\"/>\r\n\
  <use href=\"#path-Meguro\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Meguro\" d=\"M195,760,l-165,0\"/>\r\n\
  <use href=\"#path-Ikegami\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Ikegami\" d=\"M295,840,l-65,0,s-10,0,-20,-10,l-45,-45,s-10,-10,-20,-10,l-115,0\"/>\r\n\
  <use href=\"#path-Oimachi\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Oimachi\" d=\"M50,650,l202,202,s10,10,20,10,l100,0,s10,0,20,-10\"/>\r\n\
  <use href=\"#path-Rinkai\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Rinkai\" d=\"M377,862,l450,0,s10,0,20,-10,l50,-50,s10,-10,20,-10,l100,0,s10,0,20,-10,l150,-150,s10,-10,20,-10,l5,0,s10,0,20,-10,l25,-25\"/>\r\n\
  <use href=\"#path-Yurikamome\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Yurikamome\" d=\"M880,750,l0,40,s0,10,-10,10,l0,0,s-10,0,-10,-10,l0,0,s0,-10,10,-10,l175,0,s10,0,20,-10,l75,-75,s10,-10,10,-20,l0,-85\"/>\r\n\
  <use href=\"#path-Keikyu\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Keikyu\" d=\"M20,925,l350,0,s10,0,20,-10,l90,-90,M404,905,l10,10,s10,10,20,10,l200,0\"/>\r\n\
  <use href=\"#path-Monorail\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Monorail\" d=\"M635,935,s10,0,10,-10,l0,0,s0,-10,-10,-10,l-30,0,s-10,0,-20,10,l-0,0,s-10,10,-20,10,l-100,0,s-10,0,-10,-10,s0,-10,10,-20,l25,-25,s10,-10,20,-10,l210,0,s10,0,20,-10,l60,-60,s10,-10,10,-20,l0,-5\"/>\r\n\
  <use href=\"#path-Rapid\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Rapid\" d=\"M1320,300,l42,-42\"/>\r\n\
  <use href=\"#path-Keisei\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Keisei\" d=\"M820,180,l-32,-32,s-10,-10,-10,-20,l0,-76,l250,0,s10,0,20,10,l42,42,s10,10,20,10,l190,0,s10,0,20,-10,l10,-10,s10,-10,10,-20,l0,-22\"/>\r\n\
  <use href=\"#path-Oshiage\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Oshiage\" d=\"M1055,123,l250,0,s10,0,20,10,l5,5,s10,10,10,20,l0,30\"/>\r\n\
  <use href=\"#path-Tsukuba\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Tsukuba\" d=\"M850,320,l42,-42,s10,-10,10,-20,l0,-215,s0,-10,10,-10,l80,0,s10,0,20,10,l80,80,s10,10,20,10,l110,0,s10,0,20,-10,l30,-30,s10,-10,20,-10,l51,0,s10,0,10,-10,l0,-21\"/>\r\n\
  <use href=\"#path-Skytree\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Skytree\" stroke-width=\"7\" d=\"M1010,150,l42,-42M1052,108,l-35,-35,l0,-57\"/>\r\n\
  <use href=\"#path-Saitama\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Saitama\" d=\"M400,38,l-10,0,s-10,0,-20,-10,l-10,-10\"/>\r\n\
</g>\r\n\
<g id=\"Nippori\" fill=\"none\" stroke=\"#CC4492\" stroke-width=\"3\" stroke-linejoin=\"round\" stroke-linecap=\"round\">\r\n\
  <use href=\"#path-Nippori\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Nippori\" d=\"M777,111,l-77,-77,s-5,-5,-5,-10,s0,-10,10,-10,l120,0\"/>\r\n\
</g>\r\n\
<g id=\"Arakawa\" fill=\"none\" stroke=\"#CF7C3C\" stroke-width=\"3\" stroke-linejoin=\"round\" stroke-linecap=\"round\">\r\n\
  <use href=\"#path-Arakawa\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Arakawa\" d=\"M320,290,l0,-10,s0,-10,10,-20,l50,-50,s10,-10,10,-20,l0,-10,s0,-10,10,-20,l50,-50,s10,-10,20,-10,l15,0,s10,0,20,-10,l50,-50,s10,-10,20,-10,l170,0,s10,0,20,10,l25,25\"/>\r\n\
</g>\r\n\
<g id=\"Japanrail\" fill=\"none\" stroke=\"#B9B9B9\" stroke-width=\"3\" stroke-linejoin=\"round\" stroke-linecap=\"round\">\r\n\
  <use href=\"#path-Keiyo\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Keiyo\" stroke-width=\"2\" d=\"M835,530,l350,0,s10,0,20,10,l38,38,s10,10,20,10,l100,0\"/>\r\n\
  <use href=\"#path-Joban\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Joban\" d=\"M350,20,l42,42,s10,10,20,10,l800,0,s10,0,20,-10,l42,-42,M350,20,l35,35,s10,10,10,20,l0,55\"/>\r\n\
  <use href=\"#path-Keihin\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Keihin\" d=\"M20,900,l250,0,s10,0,20,-10,l40,-40\"/>\r\n\
  <use href=\"#path-Narita\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Narita\" d=\"M1285,130,s10,0,20,10,s10,10,10,20,l0,230,s0,10,10,20,l42,42,l0,-400\"/>\r\n\
  <use href=\"#path-Sobu\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Sobu\" stroke-width=\"2\" d=\"M1111,265,l-50,0,s-10,0,-20,10,l-95,95,s-10,10,-20,10,l-50,0,s-10,0,-20,10,l-25,25,s-20,0,-20,-20,l0,-45,s0,-10,-10,-20,s-10,0,-20,-10\"/>\r\n\
  <use href=\"#path-Chuo\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Chuo\" d=\"M25,300,l117,0,s10,0,20,10,l20,20,s10,10,20,10,l10,0,s10,0,20,10,l20,20,s10,10,10,20,l0,130,s0,20,20,20,l75,0,s10,0,20,-10,l200,-200,s10,-10,20,-10,l450,0,s10,0,20,-10,l170,-170,s10,-10,20,-10,l25,0\"/>\r\n\
</g>\r\n\
\r\n\
<g id=\"Yamanote\" fill=\"none\" stroke=\"#7FB15A\" stroke-width=\"6\" stroke-linejoin=\"round\" stroke-linecap=\"round\">\r\n\
  <use href=\"#path-Yamanote\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Yamanote\" d=\"M320,850,l403,0,s10,0,20,-10,l80,-80,s10,-10,10,-20,l0,-550,s0,-10,-10,-20,l-100,-100,s-20,-20,-40,0,l-50,50,s-10,10,-20,10,l-270,0,s-10,0,-20,10,l-60,60,s-10,10,-10,20,l0,570,s0,10,10,20,l30,30,s10,10,20,10,l5,0\"/>\r\n\
</g>\r\n\
\r\n\
<g id=\"Asakusa\" fill=\"none\" stroke=\"#ED6C64\" stroke-width=\"9\" stroke-linejoin=\"round\" stroke-linecap=\"round\">\r\n\
  <use href=\"#path-Asakusa\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Asakusa\" d=\"M75,825,l620,0,s10,0,20,-10l60,-60,s10,-10,20,-10,l100,0,s10,0,20,-10,l60,-60,s10,-10,10,-20,l0,-450,s0,-10,10,-20,l60,-60\"/>\r\n\
</g>\r\n\
<g id=\"Mita\" fill=\"none\" stroke=\"#006AB7\" stroke-width=\"9\" stroke-linejoin=\"round\" stroke-linecap=\"round\">\r\n\
  <use href=\"#path-Mita\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Mita\" d=\"M75,25,l150,0,s10,0,20,10l50,50,s10,10,20,10,l100,0,s10,0,20,10,l150,150,s10,10,10,20,l0,100,s0,10,10,20,l50,50,s10,10,10,20,l0,50,s0,10,10,20,l70,70,s10,10,10,20,l0,70,s0,10,-10,20,l-80,80,s-10,10,-20,10,l-80,0,s-10,0,-20,-10,l-25,-25,s-10,-10,-20,-10,l-300,0\"/>\r\n\
</g>\r\n\
<g id=\"Shinjuku\" fill=\"none\" stroke=\"#7AB728\" stroke-width=\"9\" stroke-linejoin=\"round\" stroke-linecap=\"round\">\r\n\
  <use href=\"#path-Shinjuku\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Shinjuku\" d=\"M250,480,l50,0,s10,0,20,-10,l75,-75,s10,-10,20,-10,l50,0,s10,0,20,10,l20,20,s10,10,20,10,l20,0,s20,0,20,-20,l0,-35,s0,-20,20,-20,l500,0,s10,0,20,-10,l170,-170,s10,-10,10,-20,l0,-20\"/>\r\n\
</g>\r\n\
<g id=\"Odeo\" fill=\"none\" stroke=\"#DB006E\" stroke-width=\"9\" stroke-linejoin=\"round\" stroke-linecap=\"round\">\r\n\
  <use href=\"#path-Odeo\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Odeo\" d=\"M40,150,l140,140,s10,10,10,20,l0,120,s0,20,20,20,l7,0,s20,0,20,20,l0,60,s0,20,20,20,l150,0,s10,0,20,10,l50,50,s10,10,10,20,l0,50,s0,10,10,20,l50,50,s10,10,20,10,l444,0,s10,0,20,-10,l50,-50,s10,-10,10,-20,l0,-380,s0,-10,-10,-20,l-70,-70,s-10,-10,-20,-10,l-370,0,s-10,0,-20,10,l-120,120,s-10,10,-20,10,l-125,0,s-10,0,-20,10,l-75,75,s-10,10,-20,10,s-10,0,-10,10\"/>\r\n\
</g>\r\n\
<g id=\"Ginza\" fill=\"none\" stroke=\"#FF9500\" stroke-width=\"9\" stroke-linejoin=\"round\" stroke-linecap=\"round\">\r\n\
  <use href=\"#path-Ginza\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Ginza\" d=\"M1005,160,l-165,0,s-20,0,-20,20,l0,190,s0,10,10,20,l70,70,s10,10,10,20,l0,190,s0,10,-10,20,l-30,30,s-10,10,-20,10,l-200,0,s-10,0,-20,-10,l-35,-35,s-10,-10,-10,-20,l0,-53,s0,-10,-10,-20,l-40,-40,s-10,-10,-20,-10,l-50,0,s-10,0,-20,10,l-90,90,s-10,10,-20,10,l-70,0\"/>\r\n\
</g>\r\n\
<g id=\"Marunouchi\" fill=\"none\" stroke=\"#F72E36\" stroke-width=\"9\" stroke-linejoin=\"round\" stroke-linecap=\"round\">\r\n\
  <use href=\"#path-Marunouchi\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Marunouchi\" d=\"M300,180,l160,0,s10,0,20,10l40,40,s10,10,20,10,l100,0,s10,0,20,10,l50,50,s10,10,10,20,l0,160,s0,20,20,20,l50,0,s10,0,20,10,l50,50,s10,10,10,20,l0,45,s0,10,-10,20,l-15,15,s-10,10,-20,10,l-140,0,s-10,0,-20,-10,l-200,-200,s-10,-10,-20,-10,l-80,0,s-10,0,-20,-10,l-20,-20,s-10,-10,-20,-10,l-240,0,m120,0,s-10,0,-20,-10,l-90,-90\"/>\r\n\
</g>\r\n\
<g id=\"Hibiya\" fill=\"none\" stroke=\"#B5B5AD\" stroke-width=\"9\" stroke-linejoin=\"round\" stroke-linecap=\"round\">\r\n\
  <use href=\"#path-Hibiya\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Hibiya\" d=\"M150,700,l500,0,s10,0,20,-10,l50,-50,s10,-10,20,-10,l245,0,s10,0,20,-10,l10,-10,s10,-10,10,-20,l0,-160,s0,-10,-10,-20,l-10,-10,s-10,-10,-20,-10,l-90,0,s-10,0,-20,-10,l-20,-20,s-10,-10,-10,-20,l0,-200,s0,-10,10,-20,l50,-50,s10,-10,20,-10,l80,0\"/>\r\n\
</g>\r\n\
<g id=\"Tozai\" fill=\"none\" stroke=\"#009BC0\" stroke-width=\"9\" stroke-linejoin=\"round\" stroke-linecap=\"round\">\r\n\
  <use href=\"#path-Tozai\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Tozai\" d=\"M150,300,l300,0,s10,0,20,10l150,150,s10,10,20,10,l500,0,s10,0,20,-10,l160,-160\"/>\r\n\
</g>\r\n\
<g id=\"Chiyoda\" fill=\"none\" stroke=\"#00BB85\" stroke-width=\"9\" stroke-linejoin=\"round\" stroke-linecap=\"round\">\r\n\
  <use href=\"#path-Chiyoda\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Chiyoda\" d=\"M180,600,l100,0,s10,0,20,10l35,35,s10,10,20,10,l400,0,s20,0,20,-20,l0,-10,s0,-10,-10,-20,l-76,-76,s-10,-10,-10,-20,l0,-400,s0,-10,10,-20,l35,-35,s10,-10,20,-10,l400,0,s10,0,20,-10,l15,-15\"/>\r\n\
</g>\r\n\
<g id=\"Yurakucho\" fill=\"none\" stroke=\"#C1A570\" stroke-width=\"9\" stroke-linejoin=\"round\" stroke-linecap=\"round\">\r\n\
  <use href=\"#path-Yurakucho\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Yurakucho\" d=\"M50,113,l150,0,s10,0,20,10,l100,100,s10,10,20,10,l90,0,s10,0,20,10,l69,69,s20,20,0,40,l-35,35,s-20,20,0,40,l150,150,s10,10,20,10,l600,0\"/>\r\n\
</g>\r\n\
<g id=\"Hanzoman\" fill=\"none\" stroke=\"#8F76D7\" stroke-width=\"9\" stroke-linejoin=\"round\" stroke-linecap=\"round\">\r\n\
  <use href=\"#path-Hanzoman\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Hanzoman\" d=\"M280,640,l50,0,s10,0,20,-10,l90,-90,s10,-10,20,-10,l55,0,s10,0,20,-10,l33,-33,s10,-10,10,-20,l0,-85,s-5,-25,20,-20,l10,0,s25,-5,20,20,l0,5,s0,10,10,20,l40,40,s10,10,20,10,l50,0,s10,0,20,-10,l10,-10,s10,-10,20,-10,l270,0,s10,0,20,-10,l50,-50,s10,-10,10,-20,l0,-135,s0,-10,-10,-20,l-75,-75\"/>\r\n\
</g>\r\n\
<g id=\"Namboku\" fill=\"none\" stroke=\"#00AD9B\" stroke-width=\"9\" stroke-linejoin=\"round\" stroke-linecap=\"round\">\r\n\
  <use href=\"#path-Namboku\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Namboku\" d=\"M200,745,l340,0,s10,0,20,-10l30,-30,s10,-10,10,-20,l0,-101,s0,-10,-10,-20,l-111,-111,s-20,-20,0,-40,l50,-50,s10,-10,10,-20,l0,-250,s0,-10,-10,-20,l-25,-25,s-10,-10,-20,-10,l-80,0\"/>\r\n\
</g>\r\n\
<g id=\"Fukutoshin\" fill=\"none\" stroke=\"#9D5E30\" stroke-width=\"9\" stroke-linejoin=\"round\" stroke-linecap=\"round\">\r\n\
  <use href=\"#path-Fukutoshin\" filter=\"url(#blur)\"/>\r\n\
  <path id=\"path-Fukutoshin\" d=\"M50,100,l155,0,s10,0,20,10,l70,70,s10,10,10,20,l0,150,s0,10,10,20,l30,30,s10,10,10,20,l0,25,s0,10,-10,20,l-50,50,s-10,10,-10,20,l0,75,s0,10,-10,20,l-10,10\"/>\r\n\
</g>\r\n\
\r\n\
</svg>\r\n\
";

const size_t Server_DataLength = sizeof(Server_Data);

char* Server_Headers()
{
    char buffer[255] = "\0"; //Null Terminators required only here for strcat
    char* headers = "\0";
    strcat(headers,
"\
HTTP/1.1 200 OK\r\n\
Content-Type: text/html\r\n\
Content-Length: \
");
    itoa(Server_DataLength, buffer, 10);
    strcat(headers, buffer);
    strcat(headers,
"\
\r\n\
Connection: close\r\n\
Refresh: 5\r\n\
\r\n\
");
    return headers;
}

void setup()
{
    Serial.begin(115200);
    Serial.print("[INFO]: ");
    Serial.println("iomap_keio_chubu");
    //Serial.println(Server_ResponseText());
    //Serial.println("[CKPT]");
    //Ethernet.begin(MAC, IP);
    Ethernet.begin(MAC);
    Server.begin();
    OneShot = true;
}

void loop()
{
    status = Ethernet.maintain() + (OneShot ? Server_InitSuccess : 0);
    switch (status)
    {
        case (Server_InitSuccess): OneShot = false;
        case (Server_RenewSuccess):
        case (Server_RebindSuccess):
        {
            Serial.print("[INFO]: ");
            Serial.print("Server: ");
            Serial.print(Server_localIP());
            Serial.print(":");
            Serial.println(Server_localPort());
        }
        break;
        case (Server_RenewError):
        case (Server_RebindError):
        {
            Serial.print("[WARN]: ");
            Serial.print("Server: ");
            Serial.println("Error");
        }
        break;
        case (Server_Idle):
        default:
        {
            //Serial.println(status);
        }
        break;
    }
    
    EthernetClient Client = Server.available();
    if (Client)
    {
        BlankLine = true;
        Serial.print("[INFO]: ");
        Serial.print("Client: ");
        Serial.print(Server_remoteIP());
        Serial.print(":");
        Serial.println(Server_remotePort());
        while (Client.connected())
        {
            if (Client.available())
            {
                TempChar = Client.read();
                if ((TempChar == '\n') && (BlankLine))
                {
                    Client.println(Server_Headers());
                    for (size_t i = 0; i < Server_DataLength; ++i)
                    {
                        Client.print((char)pgm_read_byte(&(Server_Data[i])));
                    }
                    break;
                }
                if (TempChar == '\n') { BlankLine = true; }
                else if (TempChar != '\r') { BlankLine = false; }
            }
        }
        delay(10);
        Client.stop();
    }
}
