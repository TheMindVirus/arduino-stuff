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

#define Server_StatusOK "HTTP/1.1 200 OK\r\n"

int status = Server_Idle;
byte MAC[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetServer Server(Server_localPort());
bool OneShot = true;

const char Server_Data[] PROGMEM = 
"\
<title>iomap_svg_tube_vicinity</title>\r\n\
<script>\r\n\
w = 0;\r\n\
h = 0;\r\n\
l = 0;\r\n\
pos1 = 0;\r\n\
pos2 = 0;\r\n\
pos3 = 0;\r\n\
pos4 = 0;\r\n\
content = null;\r\n\
canvas = null;\r\n\
ctx = null;\r\n\
render_scale = 4.0;\r\n\
render_blur = 0.5 / render_scale;\r\n\
line_width = 2.0;\r\n\
line_blur = 10.0;\r\n\
station_list =\r\n\
[\r\n\
    { id: \"A01\", x:  780, y:   85, name: \"Edgware\" },\r\n\
    { id: \"A02\", x:  805, y:  100, name: \"Burnt Oak\" },\r\n\
    { id: \"A03\", x:  825, y:  115, name: \"Colindale\" },\r\n\
    { id: \"A04\", x:  845, y:  130, name: \"Hendon Central\" },\r\n\
    { id: \"A05\", x:  865, y:  145, name: \"Brent Cross\" },\r\n\
    { id: \"A06\", x:  885, y:  155, name: \"Golders Green\" },\r\n\
    { id: \"A07\", x:  905, y:  170, name: \"Hampstead\" },\r\n\
    { id: \"A08\", x:  950, y:  200, name: \"Belsize Park\" },\r\n\
    { id: \"A09\", x:  970, y:  215, name: \"Chalk Farm\" },\r\n\
    { id: \"A10\", x:  990, y:  235, name: \"Camden Town\" },\r\n\
    { id: \"A11\", x:  980, y:  255, name: \"Mornington Crescent\" },\r\n\
    { id: \"A12\", x:  992, y:  288, name: \"Euston\" },\r\n\
    { id: \"A13\", x:  960, y:  315, name: \"Warren Street\" },\r\n\
    { id: \"A14\", x:  960, y:  352, name: \"Goodge Street\" },\r\n\
    { id: \"A15\", x:  960, y:  367, name: \"Tottenham Court Road\" },\r\n\
    { id: \"A16\", x:  960, y:  395, name: \"Leicester Square\" },\r\n\
    { id: \"A17\", x:  960, y:  430, name: \"Charing Cross\" },\r\n\
    { id: \"A18\", x:  960, y:  455, name: \"Embankment\" },\r\n\
    { id: \"A19\", x:  960, y:  486, name: \"Waterloo\" },\r\n\
    { id: \"A20\", x:  957, y:  590, name: \"Kennington\" },\r\n\
    { id: \"A21\", x:  943, y:  597, name: \"Oval\" },\r\n\
    { id: \"A22\", x:  928, y:  610, name: \"Stockwell\" },\r\n\
    { id: \"A23\", x:  912, y:  618, name: \"Clapham North\" },\r\n\
    { id: \"A24\", x:  890, y:  632, name: \"Clapham Common\" },\r\n\
    { id: \"A25\", x:  870, y:  645, name: \"Clapham South\" },\r\n\
    { id: \"A26\", x:  852, y:  660, name: \"Baltham\" },\r\n\
    { id: \"A27\", x:  832, y:  672, name: \"Tooting Bec\" },\r\n\
    { id: \"A28\", x:  812, y:  687, name: \"Tooting Broadway\" },\r\n\
    { id: \"A29\", x:  792, y:  700, name: \"Colliers Wood\" },\r\n\
    { id: \"A30\", x:  772, y:  712, name: \"South Wimbledon\" },\r\n\
    { id: \"A31\", x:  752, y:  730, name: \"Morden\" },\r\n\
\r\n\
    { id: \"A32\", x: 1041, y:   38, name: \"High Barnet\" },\r\n\
    { id: \"A33\", x: 1041, y:   52, name: \"Totteridge & Whetstone\" },\r\n\
    { id: \"A34\", x: 1041, y:   67, name: \"Woodside Park\" },\r\n\
    { id: \"A35\", x: 1041, y:   82, name: \"West Finchley\" },\r\n\
\r\n\
    { id: \"A36\", x: 1012, y:   75, name: \"Mill Hill East\" },\r\n\
\r\n\
    { id: \"A37\", x: 1041, y:  105, name: \"Finchley Central\" },\r\n\
    { id: \"A38\", x: 1041, y:  115, name: \"East Finchley\" },\r\n\
    { id: \"A39\", x: 1041, y:  135, name: \"Highgate\" },\r\n\
    { id: \"A40\", x: 1041, y:  150, name: \"Archway\" },\r\n\
    { id: \"A41\", x: 1041, y:  169, name: \"Tufnell Park\" },\r\n\
    { id: \"A42\", x: 1041, y:  186, name: \"Kentish Town\" },\r\n\
    { id: \"A43\", x: 1051, y:  302, name: \"King's Cross St Pancras\" },\r\n\
    { id: \"A44\", x: 1096, y:  295, name: \"Angel\" },\r\n\
    { id: \"A45\", x: 1134, y:  311, name: \"Old Street\" },\r\n\
    { id: \"A46\", x: 1134, y:  344, name: \"Moorgate\" },\r\n\
    { id: \"A47\", x: 1134, y:  397, name: \"Bank\" },\r\n\
    { id: \"A48\", x: 1134, y:  462, name: \"London Bridge\" },\r\n\
    { id: \"A49\", x: 1047, y:  530, name: \"Borough\" },\r\n\
    { id: \"A50\", x:  993, y:  565, name: \"Elephant & Castle\" },\r\n\
];\r\n\
link_list =\r\n\
[\r\n\
    { id1: \"A01\", id2: \"A02\" },\r\n\
    { id1: \"A02\", id2: \"A03\" },\r\n\
    { id1: \"A03\", id2: \"A04\" },\r\n\
    { id1: \"A04\", id2: \"A05\" },\r\n\
    { id1: \"A05\", id2: \"A06\" },\r\n\
    { id1: \"A06\", id2: \"A07\" },\r\n\
    { id1: \"A07\", id2: \"A08\" },\r\n\
    { id1: \"A08\", id2: \"A09\" },\r\n\
    { id1: \"A09\", id2: \"A10\" },\r\n\
    { id1: \"A10\", id2: \"A11\" },\r\n\
    { id1: \"A11\", id2: \"A12\" },\r\n\
    { id1: \"A12\", id2: \"A13\" },\r\n\
    { id1: \"A13\", id2: \"A14\" },\r\n\
    { id1: \"A14\", id2: \"A15\" },\r\n\
    { id1: \"A15\", id2: \"A16\" },\r\n\
    { id1: \"A16\", id2: \"A17\" },\r\n\
    { id1: \"A17\", id2: \"A18\" },\r\n\
    { id1: \"A18\", id2: \"A19\" },\r\n\
    { id1: \"A19\", id2: \"A20\" },\r\n\
    { id1: \"A20\", id2: \"A21\" },\r\n\
    { id1: \"A21\", id2: \"A22\" },\r\n\
    { id1: \"A22\", id2: \"A23\" },\r\n\
    { id1: \"A23\", id2: \"A24\" },\r\n\
    { id1: \"A24\", id2: \"A25\" },\r\n\
    { id1: \"A25\", id2: \"A26\" },\r\n\
    { id1: \"A26\", id2: \"A27\" },\r\n\
    { id1: \"A27\", id2: \"A28\" },\r\n\
    { id1: \"A28\", id2: \"A29\" },\r\n\
    { id1: \"A29\", id2: \"A30\" },\r\n\
    { id1: \"A30\", id2: \"A31\" },\r\n\
\r\n\
    { id1: \"A32\", id2: \"A33\" },\r\n\
    { id1: \"A33\", id2: \"A34\" },\r\n\
    { id1: \"A34\", id2: \"A35\" },\r\n\
    { id1: \"A35\", id2: \"A37\" },\r\n\
\r\n\
    { id1: \"A36\", id2: \"A37\" },\r\n\
\r\n\
    { id1: \"A37\", id2: \"A38\" },\r\n\
    { id1: \"A38\", id2: \"A39\" },\r\n\
    { id1: \"A39\", id2: \"A40\" },\r\n\
    { id1: \"A40\", id2: \"A41\" },\r\n\
    { id1: \"A41\", id2: \"A42\" },\r\n\
\r\n\
    { id1: \"A42\", id2: \"A10\" },\r\n\
    { id1: \"A10\", id2: \"A12\" },\r\n\
    { id1: \"A12\", id2: \"A43\" },\r\n\
\r\n\
    { id1: \"A43\", id2: \"A44\" },\r\n\
    { id1: \"A44\", id2: \"A45\" },\r\n\
    { id1: \"A45\", id2: \"A46\" },\r\n\
    { id1: \"A46\", id2: \"A47\" },\r\n\
    { id1: \"A47\", id2: \"A48\" },\r\n\
    { id1: \"A48\", id2: \"A49\" },\r\n\
    { id1: \"A49\", id2: \"A50\" },\r\n\
    { id1: \"A50\", id2: \"A20\" },\r\n\
];\r\n\
getStationIndex = function(id)\r\n\
{\r\n\
    for (var i = 0; i < station_list.length; ++i)\r\n\
    {\r\n\
        if (station_list[i].id == id) { return i; }\r\n\
    }\r\n\
}\r\n\
print = function(message, indent = 0)\r\n\
{\r\n\
    var indentation = \"\";\r\n\
    if (indent > 0)\r\n\
    {\r\n\
        for (var i = 0; i < indent - 1; ++i) { indentation += \"  \"; }\r\n\
        indentation += \"| - \";\r\n\
    }\r\n\
    console.log(indentation + \"%c\" + message, \"color: #FF5577\");\r\n\
    //Serial.println(\"[INFO]: \" + indentation + \"\033[38;5;1m\" + message + \"\033[0m\");\r\n\
    message = indentation + message;\r\n\
    var xmlhttp = new XMLHttpRequest();\r\n\
    //xmlhttp.open(\"POST\", \".\", true);\r\n\
    //xmlhttp.send(message);\r\n\
    message = message.replaceAll(\" \", \"%20\");\r\n\
    message = message.replaceAll(\"|\", \"%7C\");\r\n\
    xmlhttp.open(\"GET\", \".?msg=\" + message, false);\r\n\
    xmlhttp.send();\r\n\
    //fetch(\".\");\r\n\
}\r\n\
vicinity = function(id, level, depth = 0, prev = null)\r\n\
{\r\n\
    if (depth > level) { return; }\r\n\
    var idx = getStationIndex(id);\r\n\
    if (idx != null)\r\n\
    {\r\n\
        print(station_list[idx].name, depth);\r\n\
        for (var i = 0; i < link_list.length; ++i)\r\n\
        {\r\n\
            var id2 = null;\r\n\
            if (link_list[i].id1 == id) { id2 = link_list[i].id2; }\r\n\
            else if (link_list[i].id2 == id) { id2 = link_list[i].id1; }\r\n\
            if ((id2 != null) && (id2 != id) && (id2 != prev)) { vicinity(id2, level, depth + 1, id); }\r\n\
        }\r\n\
    }\r\n\
}\r\n\
inquire = function(id, level = 3)\r\n\
{\r\n\
    var idx = getStationIndex(id);\r\n\
    console.log(id);\r\n\
    console.log(idx);\r\n\
    vicinity(id, level);\r\n\
}\r\n\
ondragstart = function(event)\r\n\
{\r\n\
    event.preventDefault();\r\n\
    pos3 = event.clientX;\r\n\
    pos4 = event.clientY;\r\n\
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
    var style = window.getComputedStyle(content);\r\n\
    content.style.left = (parseFloat(style.left) - pos1) + \"px\";\r\n\
    content.style.top = (parseFloat(style.top) - pos2) + \"px\";\r\n\
}\r\n\
ondragstop = function()\r\n\
{\r\n\
    document.onmousemove = null;\r\n\
}\r\n\
window.onload = function()\r\n\
{\r\n\
    canvas = document.getElementsByTagName(\"canvas\")[0];\r\n\
    ctx = canvas.getContext(\"2d\");\r\n\
    content = document.getElementById(\"content\");\r\n\
    header = document.getElementById(\"header\");\r\n\
    footer = document.getElementById(\"footer\");\r\n\
    content.onmousedown = ondragstart;\r\n\
    for (var i = 0; i < station_list.length; ++i)\r\n\
    {\r\n\
        var pin = document.createElement(\"g\");\r\n\
        pin.setAttribute(\"class\", \"station\");\r\n\
        pin.setAttribute(\"id\", station_list[i].id);\r\n\
        pin.setAttribute(\"name\", station_list[i].name);\r\n\
        pin.setAttribute(\"x\", station_list[i].x);\r\n\
        pin.setAttribute(\"y\", station_list[i].y);\r\n\
\r\n\
        var ico = document.createElement(\"circle\");\r\n\
        ico.setAttribute(\"cx\", station_list[i].x);\r\n\
        ico.setAttribute(\"cy\", station_list[i].y);\r\n\
        ico.setAttribute(\"r\", \"6\");\r\n\
        ico.setAttribute(\"fill\", \"#33333333\");\r\n\
        ico.setAttribute(\"stroke\", \"#FF0040FF\");\r\n\
        ico.setAttribute(\"stroke-width\", \"1\");\r\n\
        ico.setAttribute(\"onclick\", \"inquire(\\\"\" + station_list[i].id + \"\\\");\");\r\n\
        pin.appendChild(ico);\r\n\
\r\n\
        var txt = document.createElement(\"text\");\r\n\
        txt.innerText = station_list[i].name;\r\n\
        txt.setAttribute(\"x\", station_list[i].x);\r\n\
        txt.setAttribute(\"y\", station_list[i].y - 10);\r\n\
        txt.setAttribute(\"fill\", \"#FFFFFFFF\");\r\n\
        txt.setAttribute(\"font-size\", \"6pt\");\r\n\
        txt.setAttribute(\"text-anchor\", \"middle\");\r\n\
        pin.appendChild(txt);\r\n\
\r\n\
        content.appendChild(pin);\r\n\
    }\r\n\
    content.innerHTML = content.innerHTML;\r\n\
    window.onresize();\r\n\
    setInterval(render, 0);\r\n\
}\r\n\
window.onresize = function()\r\n\
{\r\n\
    var style = window.getComputedStyle(canvas);\r\n\
    w = canvas.width = parseFloat(style.width) * render_scale;\r\n\
    h = canvas.height = parseFloat(style.height) * render_scale;\r\n\
    l = (render_scale - 1.0) * 50;\r\n\
    canvas.style.transform = \"translate(\" + l + \"%, \" + l + \"%) scale(\" + render_scale + \")\";\r\n\
}\r\n\
point = function(element, mode)\r\n\
{\r\n\
    var rect = element.getBoundingClientRect();\r\n\
    if (mode == 1) { return { x: rect.left + 6, y: rect.top + 6 }; }\r\n\
    else if (mode == 2) { return { x: rect.left + 6, y: rect.top + 6 }; }\r\n\
    else { return rect; }\r\n\
}\r\n\
render = function()\r\n\
{\r\n\
    canvas.width = canvas.width;\r\n\
    ctx.strokeStyle = \"#FF0040FF\";\r\n\
    ctx.shadowColor = ctx.strokeStyle;\r\n\
    ctx.shadowBlur = line_blur;\r\n\
    ctx.lineWidth = line_width;\r\n\
    ctx.lineCap = \"round\";\r\n\
    canvas.style.filter = \"blur(\" + render_blur + \"px)\";\r\n\
\r\n\
    for (var i = 0; i < link_list.length; ++i)\r\n\
    {\r\n\
        var a = point(document.getElementById(link_list[i].id1).children[0], 1);\r\n\
        var b = point(document.getElementById(link_list[i].id2).children[0], 2);\r\n\
        ctx.beginPath();\r\n\
        ctx.moveTo(a.x, a.y);\r\n\
        ctx.lineTo(b.x, b.y);\r\n\
        ctx.stroke();\r\n\
    }\r\n\
}\r\n\
</script>\r\n\
<style>\r\n\
* { box-sizing: border-box; margin: auto; font-family: Orbitron, Helvetica, sans-serif; user-select: none; white-space: nowrap; }\r\n\
body { background: black; color: #FF0040FF; overflow: hidden; }\r\n\
canvas { position: fixed; top: 0; left: 0; width: 100%; height: 100%; z-index: 9999; image-rendering: pixelated; }\r\n\
#content { position: fixed; top: 12vh; left: 0; width: 100%; height: 100%; z-index: 9999; }\r\n\
#header { position: fixed; resize: none; background: #000000AF; width: 100%; height: 12vh; padding-top: 0px; padding-bottom: 130px; text-align: center; z-index: 9999; border-bottom: thin gray solid; font-size: 42pt; top: -20px; }\r\n\
#footer { position: fixed; resize: none; background: #000000AF; width: 100%; height: 12vh; padding-top: 5px; padding-bottom: 30px; text-align: center; z-index: 9999; border-top: thin gray solid; bottom: 0; text-align: left; overflow-y: scroll; }\r\n\
</style>\r\n\
<canvas></canvas>\r\n\
<svg id=\"content\" xmlns=\"http://www.w3.org/2000/svg\" overflow=\"visible\"></svg>\r\n\
<div id=\"header\"><h1>[VK_IOMAP_TUBE_VICINITY]</h1></div>\r\n\
<div id=\"footer\"><h1 align=\"left\">VK - VULKAN GRAPHICS ENGINE PIPELINE</h1><h1 align=\"center\">IOMAP - INPUT-OUTPUT MAPPING DIAGRAM</h1><h1 align=\"right\">TUBE-VICINITY - NEAREST STATIONS</h1></div>\r\n\r\n\
";

const size_t Server_DataLength = sizeof(Server_Data);

char* Server_Headers()
{
    char buffer[255] = "\0"; //Null Terminators required only here for strcat
    char* headers = "\0";
    strcat(headers, Server_StatusOK
"\
Content-Type: text/html\r\n\
Content-Length: \
");
    itoa(Server_DataLength, buffer, 10);
    strcat(headers, buffer);
    strcat(headers,
"\
\r\n\
Access-Control-Allow-Origin: *\r\n\
\r\n\
");
    return headers;
}

const int Server_BufferLength = 255;
char Server_Buffer[Server_BufferLength] = {};
size_t Server_BufferOffset = 0;

void Server_BufferClear()
{
    for (size_t i = 0; i < Server_BufferLength; ++i)
    {
        Server_Buffer[i] = "\0";
    }
    Server_BufferOffset = 0;
}

void setup()
{
    Serial.begin(115200);
    Serial.print("[INFO]: ");
    Serial.println("iomap_svg_tube_vicinity");
    Server_BufferClear();
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
        //Serial.print("[INFO]: ");
        //Serial.print("Client: ");
        //Serial.print(Server_remoteIP());
        //Serial.print(":");
        //Serial.println(Server_remotePort());
        while (Client.connected())
        {
            while (Client.available())
            {
                Server_Buffer[Server_BufferOffset] = Client.read();
                if (Server_BufferOffset < Server_BufferLength) { Server_BufferOffset += 1; }
                else { break; }
            }
            char* ptr = strtok(Server_Buffer, '\n');
            while (ptr != nullptr)
            {
                if ((ptr[0] == 'G')
                &&  (ptr[1] == 'E')
                &&  (ptr[2] == 'T'))
                {
                    if (ptr[5] == ' ')
                    {
                        //Serial.println(Server_Buffer);
                        Client.println(Server_Headers());
                        for (size_t i = 0; i < Server_DataLength; ++i)
                        {
                            Client.print((char)pgm_read_byte(&(Server_Data[i])));
                        }
                    }
                    else
                    {
                        //Serial.println(Server_Buffer);
                        String msg = String(ptr + 10);
                        msg = msg.substring(0, msg.indexOf(" "));
                        msg.replace("\r", "");
                        msg.replace("%20", " ");
                        msg.replace("%27", "'");
                        msg.replace("%7C", "|");
                        Serial.println(msg);
                        Client.print(Server_StatusOK);
                    }
                }
                ptr = strtok(nullptr, '\n');
            }
            Server_BufferClear();
            break;
        }
        delay(10);
        Client.stop();
    }
}
