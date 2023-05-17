#include <Ethernet.h>

#define Server_AppName "W3BIOS"

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
<title>W3BIOS</title>\r\n\
<script>\r\n\
tab=0;\r\n\
idx=0;\r\n\
window.onload=function(e)\r\n\
{\r\n\
console.log(e);\r\n\
topbar=document.getElementById(\"tabs\");\r\n\
content=document.getElementById(\"content\");\r\n\
upperbox=document.getElementById(\"upperbox\");\r\n\
lowerbox=document.getElementById(\"lowerbox\");\r\n\
draw_bios();\r\n\
}\r\n\
document.onkeydown=function(e)\r\n\
{\r\n\
console.log(e);\r\n\
szi=content.children.length;\r\n\
szt=topbar.children.length;\r\n\
if(e.key==\"ArrowLeft\"){tab-=1;if(tab<0){tab=szt-1;}tab%=szt;}\r\n\
if(e.key==\"ArrowRight\"){tab+=1;tab%=szt;}\r\n\
if(e.key==\"ArrowUp\"){idx-=1;if(idx<0){idx=szi-1;}idx%=szi;}\r\n\
if(e.key==\"ArrowDown\"){idx+=1;idx%=szi;}\r\n\
for(var i=0;i<szi;++i){if(i==idx){content.children[i].setAttribute(\"select\",null);}else{try{content.children[i].removeAttribute(\"select\");}catch(e){}}}\r\n\
for(var t=0;t<szt;++t){if(t==tab){topbar.children[t].setAttribute(\"select\",null);}else{try{topbar.children[t].removeAttribute(\"select\");}catch(e){}}}\r\n\
}\r\n\
draw_bios=function(e)\r\n\
{\r\n\
content.innerHTML=\"\"\r\n\
+\"<h2>BIOS Information</h2>\"\r\n\
+\"<h2>BIOS Vendor<span value>Arduino SRL/LLC/Inc.</span></h2>\"\r\n\
+\"<h2>Version<span value>0.0.0000.</span></h2>\"\r\n\
+\"<h2>GOP Version<span value>UEFI Graphics</span></h2>\"\r\n\
+\"<h2>EC Version<span value>Explaining Computers</span></h2>\"\r\n\
+\"</br></br>\"\r\n\
+\"<h2>Processor Information<span value>Atmel(TM) ATMEGA328P(TM)</span></h2>\"\r\n\
+\"<h2>_<span value>UNO(TM) R3(TM)</span></h2>\"\r\n\
+\"<h2>_<span value><span red>DeepSleep(TM) EdgeCase(TM)</span></span></h2>\"\r\n\
+\"<h2>_<span value>XTAL @ 16MHz</span></h2>\"\r\n\
+\"</br></br>\"\r\n\
+\"<h2>Memory Information</h2>\"\r\n\
+\"<h2>Total Memory<span value>LotsOfKB</span>\"\r\n\
+\"</br></br>\"\r\n\
+\"<h2>System Information</h2>\"\r\n\
+\"<h2>Serial Number<span value>0123456789ABCDEF</span>\"\r\n\
+\"</br></br>\"\r\n\
+\"<h2><span white>System Date</span><span value blue>[Sat <span white>00</span>/00/0000]</span></h2>\"\r\n\
+\"<h2><span blue>System Time<span value>[00:00:00]</span></span>\"\r\n\
+\"</br></br>\"\r\n\
+\"<h2>Access Level<span value red>Edge</span></h2>\"\r\n\
+\"</br></br>\"\r\n\
+\"<h2>Return to slof</h2>\"\r\n\
+\"\";\r\n\
upperbox.innerHTML=\"\"\r\n\
+\"<h2>Set the Date. Use Tab to</h2>\"\r\n\
+\"<h2>switch between Date elements.</h2>\"\r\n\
+\"<h2>Default Ranges:</h2>\"\r\n\
+\"<h2>Year: 2023-2077</h2>\"\r\n\
+\"<h2>Months: 0-11</h2>\"\r\n\
+\"<h2>Days: dependent on month</h2>\"\r\n\
+\"<h2>_____ 28 | 29 | 30 | 31</h2>\"\r\n\
+\"\";\r\n\
lowerbox.innerHTML=\"\"\r\n\
+\"<h2>&#x1F87A;&#x1F878;: Select Tab</h2>\"\r\n\
+\"<h2>&#x1F879;&#x1F87B;: Select Item</h2>\"\r\n\
+\"<h2>Enter: Select</h2>\"\r\n\
+\"<h2>+/-: Change Opt.</h2>\"\r\n\
+\"<h2>F1: General Help</h2>\"\r\n\
+\"<h2>F9: Last Known Good</h2>\"\r\n\
+\"<h2>F10: Save & Exit</h2>\"\r\n\
+\"<h2>ESC: Exit Without Saving</h2>\"\r\n\
+\"\";\r\n\
}\r\n\
</script>\r\n\
<style>\r\n\
* { box-sizing: border-box; margin: auto; font-family: courier, monospace, sans-serif; overflow: hidden; }\r\n\
body { background: #006468; }\r\n\
span[red] { color: #FF0033; text-shadow: 0 0 10px white; filter: saturate(9001%); }\r\n\
span[blue] { color: #0000AA; }\r\n\
span[white] { color: #999999; }\r\n\
span[yellow] { color: yellow; }\r\n\
span[value] { position: absolute; left: 500px; }\r\n\
#topbar { text-align: center; color: white; }\r\n\
#tabs { text-align: left; padding: 10px; }\r\n\
#tabs > * { display: inline-block; float: left; padding-top: 5px; padding-left: 10px; padding-right: 10px; }\r\n\
#tabs > *[select] { background: #AAAAAA; color: black; }\r\n\
#tabs > *:not([select]) { color: yellow; }\r\n\
#container { position: fixed; top: 80px; left: 10px; width: calc(100% - 20px); height: calc(100% - 125px); border: 10px #17a1a5 solid; padding: 5px; }\r\n\
#content { position: absolute; top: 8px; left: 8px; width: calc(50% - 8px); height: calc(100% - 16px); padding: 30px; background: #ffffcc; }\r\n\
#upperbox { position: absolute; top: 8px; left: calc(50% + 8px); width: calc(50% - 16px); height: calc(50% - 8px); padding: 30px; background: #ffffcc; color: #0000AA; }\r\n\
#lowerbox { position: absolute; top: calc(50% + 8px); left: calc(50% + 8px); width: calc(50% - 16px); height: calc(50% - 16px); padding: 30px; background: #ffffcc; color: #0000AA; }\r\n\
#ribbon { position: fixed; bottom: 5px; width: 100%; text-align: center; color: white; }\r\n\
#content > *[select] { color: #999999; }\r\n\
</style>\r\n\
<div id=\"topbar\">\r\n\
<h1>Arduino Setup Utility - IETF (V) 2023 - W3BIOS [Pre-Alpha, Debug]</h1>\r\n\
<div id=\"tabs\">\r\n\
<div id=\"tab1\" class=\"tab\" select><h2>Main</h2></div>\r\n\
<div id=\"tab2\" class=\"tab\"><h2>Advanced</h2></div>\r\n\
<div id=\"tab3\" class=\"tab\"><h2>Boot</h2></div>\r\n\
<div id=\"tab4\" class=\"tab\"><h2>Security</h2></div>\r\n\
<div id=\"tab5\" class=\"tab\"><h2>Save & Exit</h2></div>\r\n\
<div id=\"tab6\" class=\"tab\" style=\"float: right;\"><h2>(V)</h2></div>\r\n\
</div></div>\r\n\
<div id=\"container\">\r\n\
<div id=\"page1\" class=\"page\">\r\n\
<div id=\"content\"></div>\r\n\
<div id=\"upperbox\"></div>\r\n\
<div id=\"lowerbox\"></div>\r\n\
</div></div>\r\n\
<div id=\"ribbon\">\r\n\
<h1>Version 0.00.0000. - (V) 2023 - Arduino, IETF</h1>\r\n\
</div>\r\n\
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
    Serial.println(Server_AppName);
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
