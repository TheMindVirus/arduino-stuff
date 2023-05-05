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
<!DOCTYPE html>\r\n\
<html>\r\n\
<head>\r\n\
<title>iomap</title>\r\n\
<script>\r\n\
div_img = \"data:image/png;base64,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\";\r\n\
drag_element = null;\r\n\
canvas = null;\r\n\
ctx = null;\r\n\
w = 0;\r\n\
h = 0;\r\n\
pos1 = 0;\r\n\
pos2 = 0;\r\n\
pos3 = 0;\r\n\
pos4 = 0;\r\n\
line_width = 2.0;\r\n\
line_blur = 10.0;\r\n\
render_scale = 4.0;\r\n\
render_blur = 0.5 / render_scale;\r\n\
drive_list =\r\n\
[\r\n\
  { id: \"A1\", name: \"Watchdog Timer\",      x: 100, y: 100, value: 0.99 },\r\n\
  { id: \"A2\", name: \"Watchdog Oscillator\", x: 100, y: 200, value: 0.77 },\r\n\
  { id: \"A3\", name: \"Oscillator Circuits\", x: 100, y: 300, value: 0.55 },\r\n\
  { id: \"A4\", name: \"Clock Generation\",    x: 100, y: 400, value: 0.33 },\r\n\
  { id: \"A5\", name: \"EEPROM\",              x: 100, y: 500, value: 0.11 },\r\n\
  { id: \"A6\", name: \"8-bit T/C 0\",         x: 100, y: 600, value: 0.50 },\r\n\
  { id: \"A7\", name: \"8-bit T/C 2\",         x: 100, y: 700, value: 0.50 },\r\n\
  { id: \"A8\", name: \"USART 0\",             x: 100, y: 800, value: 0.50 },\r\n\
  { id: \"A9\", name: \"PORT D (8)\",          x: 100, y: 900, value: 0.50 },\r\n\
  { id: \"B1\", name: \"Power Supervision\",   x: 400, y: 100, value: 0.99 },\r\n\
  { id: \"B2\", name: \"POR/BOD and RESET\",   x: 400, y: 200, value: 0.88 },\r\n\
  { id: \"B3\", name: \"Flash\",               x: 400, y: 300, value: 0.77 },\r\n\
  { id: \"B4\", name: \"AVR CPU\",             x: 550, y: 400, value: 0.66 },\r\n\
  { id: \"B5\", name: \"16-bit T/C 1\",        x: 400, y: 500, value: 0.55 },\r\n\
  { id: \"B6\", name: \"Analog Comparator\",   x: 400, y: 600, value: 0.44 },\r\n\
  { id: \"B7\", name: \"SPI\",                 x: 400, y: 700, value: 0.33 },\r\n\
  { id: \"B8\", name: \"PORT B (8)\",          x: 400, y: 800, value: 0.22 },\r\n\
  { id: \"C1\", name: \"debugWIRE\",           x: 700, y: 100, value: 0.99 },\r\n\
  { id: \"C2\", name: \"Program Logic\",       x: 700, y: 200, value: 0.88 },\r\n\
  { id: \"C3\", name: \"SRAM\",                x: 700, y: 300, value: 0.77 },\r\n\
  { id: \"C4\", name: \"A/D Converter\",       x: 700, y: 400, value: 0.66 },\r\n\
  { id: \"C5\", name: \"Internal Bandgap\",    x: 700, y: 500, value: 0.55 },\r\n\
  { id: \"C6\", name: \"TWI\",                 x: 700, y: 600, value: 0.44 },\r\n\
  { id: \"C7\", name: \"PORT C (7)\",          x: 700, y: 700, value: 0.33 },\r\n\
  { id: \"D1\", name: \"DATA-BUS\",            x: 400, y: 400, value: 1.00 },\r\n\
];\r\n\
cable_list =\r\n\
[\r\n\
  { id1: \"A1\", id2: \"B1\" }, { id1: \"A2\", id2: \"A1\" }, { id1: \"A2\", id2: \"A3\" }, { id1: \"A3\", id2: \"A4\" },\r\n\
  { id1: \"B1\", id2: \"B2\" }, { id1: \"C1\", id2: \"C2\" }, { id1: \"A9\", id2: \"A3\" }, { id1: \"B8\", id2: \"A3\" },\r\n\
  { id1: \"B8\", id2: \"A4\" }, { id1: \"C7\", id2: \"B1\" }, { id1: \"C7\", id2: \"B2\" }, { id1: \"C7\", id2: \"C1\" },\r\n\
  { id1: \"B3\", id2: \"B4\" }, { id1: \"C3\", id2: \"B4\" }, { id1: \"B4\", id2: \"D1\" }, { id1: \"A5\", id2: \"D1\" },\r\n\
  { id1: \"A6\", id2: \"D1\" }, { id1: \"A7\", id2: \"D1\" }, { id1: \"A8\", id2: \"D1\" }, { id1: \"A9\", id2: \"D1\" },\r\n\
  { id1: \"B5\", id2: \"D1\" }, { id1: \"B7\", id2: \"D1\" }, { id1: \"B8\", id2: \"D1\" }, { id1: \"C4\", id2: \"D1\" },\r\n\
  { id1: \"C6\", id2: \"D1\" }, { id1: \"C7\", id2: \"D1\" }, { id1: \"B7\", id2: \"D1\" }, { id1: \"A8\", id2: \"A9\" },\r\n\
  { id1: \"A9\", id2: \"B6\" }, { id1: \"C7\", id2: \"C4\" }, { id1: \"C6\", id2: \"C5\" }, { id1: \"C6\", id2: \"B6\" },\r\n\
  { id1: \"B7\", id2: \"B8\" }, { id1: \"C6\", id2: \"C7\" }, { id1: \"B5\", id2: \"B8\" }, { id1: \"A9\", id2: \"B5\" },\r\n\
  { id1: \"A7\", id2: \"B5\" }, { id1: \"A7\", id2: \"B8\" }, { id1: \"A6\", id2: \"A9\" }\r\n\
];\r\n\
window.onload = function()\r\n\
{\r\n\
  canvas = document.getElementsByTagName(\"canvas\")[0];\r\n\
  ctx = canvas.getContext(\"2d\");\r\n\
  content = document.getElementById(\"content\");\r\n\
  header = document.getElementById(\"header\");\r\n\
  footer = document.getElementById(\"footer\");\r\n\
  content.onmousedown = ondragstart;\r\n\
  for (var i = 0; i < drive_list.length; ++i)\r\n\
  {\r\n\
    var div = document.createElement(\"div\");\r\n\
    div.className = \"stage\";\r\n\
    div.id = drive_list[i].id;\r\n\
    div.name = drive_list[i].name;\r\n\
    div.style.left = drive_list[i].x + \"px\";\r\n\
    div.style.top = drive_list[i].y + \"px\";\r\n\
    div.onmousedown = ondragstart;\r\n\
    var img = document.createElement(\"img\");\r\n\
    img.src = div_img; img.alt = \"\";\r\n\
    div.appendChild(img);\r\n\
    var bar = document.createElement(\"progress\");\r\n\
    bar.style.width = \"100%\";\r\n\
    bar.style.accentColor = \"#FF0033FF\";\r\n\
    bar.style.position = \"absolute\";\r\n\
    bar.value = drive_list[i].value;\r\n\
    bar.style.top = \"27px\";\r\n\
    bar.style.left = \"0px\";\r\n\
    div.appendChild(bar);\r\n\
    var map = document.createElement(\"p\");\r\n\
    map.innerText = drive_list[i].name;\r\n\
    map.style.position = \"absolute\";\r\n\
    map.style.textAlign = \"center\";\r\n\
    map.style.color = \"#FFFFFFFF\";\r\n\
    map.style.top = \"42px\";\r\n\
    div.appendChild(map);\r\n\
    content.appendChild(div);\r\n\
  }\r\n\
  window.onresize();\r\n\
  setInterval(render, 0);\r\n\
}\r\n\
window.onresize = function()\r\n\
{\r\n\
  var style = window.getComputedStyle(canvas);\r\n\
  w = canvas.width = parseFloat(style.width) * render_scale;\r\n\
  h = canvas.height = parseFloat(style.height) * render_scale;\r\n\
  p = (render_scale - 1.0) * 50;\r\n\
  canvas.style.transform = \"translate(\" + p + \"%, \" + p + \"%) scale(\" + render_scale + \")\";\r\n\
}\r\n\
ondragstart = function(event)\r\n\
{\r\n\
  event.preventDefault();\r\n\
  pos3 = event.clientX;\r\n\
  pos4 = event.clientY;\r\n\
  drag_element = event.target;\r\n\
  document.onmousemove = ondragmove;\r\n\
  document.onmouseup = ondragstop;\r\n\
}\r\n\
ondragmove = function(event)\r\n\
{\r\n\
  event.preventDefault();\r\n\
  pos1 = pos3 - event.clientX;\r\n\
  pos2 = pos4 - event.clientY;\r\n\
  pos3 = event.clientX;\r\n\
  pos4 = event.clientY;\r\n\
  drag_element.style.left = (drag_element.offsetLeft - pos1) + \"px\";\r\n\
  drag_element.style.top = (drag_element.offsetTop - pos2) + \"px\";\r\n\
}\r\n\
ondragstop = function()\r\n\
{\r\n\
  document.onmousemove = null;\r\n\
  document.onmouseup = null;\r\n\
}\r\n\
point = function(element, mode)\r\n\
{\r\n\
  var rect = element.getBoundingClientRect();\r\n\
  if (mode == 1) { return { x: rect.right + 5, y: rect.top + 10 }; }\r\n\
  else if (mode == 2) { return { x: rect.left - 5, y: rect.top + 10 }; }\r\n\
  else { return rect; }\r\n\
}\r\n\
interpolate = function(pos, cx, cy) { return { x: pos.x + cx, y: pos.y + cy }; }\r\n\
render = function()\r\n\
{\r\n\
  ctx.fillStyle = \"#000000FF\";\r\n\
  ctx.fillRect(0, 0, w, h);\r\n\
  ctx.strokeStyle = \"#FF0040FF\";\r\n\
  ctx.shadowColor = \"#FF0040FF\";\r\n\
  ctx.shadowBlur = line_blur;\r\n\
  ctx.lineWidth = line_width;\r\n\
  ctx.lineCap = \"round\";\r\n\
  canvas.style.filter = \"blur(\" + render_blur + \"px)\";\r\n\
  for (var i = 0; i < cable_list.length; ++i)\r\n\
  {\r\n\
    var pt1 = point(document.getElementById(cable_list[i].id1), 1);\r\n\
    var pt2 = point(document.getElementById(cable_list[i].id2), 2);\r\n\
    var pta = interpolate(pt1,  50, 0);\r\n\
    var ptb = interpolate(pt2, -50, 0);\r\n\
    ctx.beginPath();\r\n\
    ctx.moveTo(pt1.x, pt1.y);\r\n\
    ctx.bezierCurveTo(pta.x, pta.y, ptb.x, ptb.y, pt2.x, pt2.y);\r\n\
    ctx.stroke();\r\n\
  }\r\n\
}\r\n\
</script>\r\n\
<style>\r\n\
* { box-sizing: border-box; margin: auto; font-family: Orbitron, Helvetica, sans-serif; user-select: none; white-space: nowrap; }\r\n\
body { background: black; color: #FF0033FF; overflow: hidden; }\r\n\
canvas { position: fixed; top: 0; left: 0; width: 100%; height: 100%; z-index: 9999; image-rendering: pixelated; }\r\n\
#content { position: fixed; top: 0; left: 0; width: 100%; height: 100%; z-index: 9999; }\r\n\
#header { position: fixed; resize: none; background: #000000AF; width: 100%; height: 100px; padding-top: 30px; padding-bottom: 30px; text-align: center; z-index: 9999; border-bottom: thin gray solid; }\r\n\
#footer { position: fixed; resize: none; background: #000000AF; width: 100%; height: 100px; padding-top: 30px; padding-bottom: 30px; text-align: center; z-index: 9999; border-top: thin gray solid; bottom: 0; text-align: left; padding-left: 5vw; overflow-y: scroll; }\r\n\
.stage { position: absolute; width: content; height: content; text-align: text-top; }\r\n\
.stage > * { pointer-events: none; }\r\n\
</style>\r\n\
</head>\r\n\
<body>\r\n\
<canvas></canvas>\r\n\
<div id=\"content\"></div>\r\n\
<div id=\"header\"><h1>ARDUINO UNO ATMEGA328P</h1></div>\r\n\
<div id=\"footer\"><h2>IOMAP____8-BIT MICROCONTROLLER____MONO_CHIP_VIEW</h2></div>\r\n\
</body>\r\n\
</html>\r\n\
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
    Serial.println("iomap_arduino");
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
