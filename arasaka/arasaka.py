data = """#ifndef _ARASAKA_H_
#define _ARASAKA_H_

const uint8_t PROGMEM arasaka[] =
{
"""

#raw = [[0] * 160] * 128

raw = []
for i in range(0, 128):
    raw.append([0] * 160)

### BEGIN RENDER ###

from PIL import Image
img = Image.open("arasaka.png")
img = img.resize((160, 128))
m,n = img.size
for i in range(0, m):
    for j in range(0, n):
        r,g,b,a = img.getpixel((i, j))
        raw[j][i] = 1 if r > 64 or g > 64 or b > 64 else 0

### END RENDER ###

render = ""
for i in raw:
    render += "".join([str(j) for j in i]) + "\n"
with open("arasaka.txt", "w") as file:
    file.write(render)

#chunks = [["0x00"] * 10] * 256

chunks = []
for i in range(0, 256):
    chunks.append(["0x00"] * 10)

x = 0
y = 0
stringified = render.replace("\n", "")
for i in range(0, len(stringified), 8):
    chunks[y][x] = "0x{:02X}".format(int(stringified[i:i+8], 2))
    y += 1 if x >= 10 - 1 else 0
    x = 0 if x >= 10 - 1 else x + 1
for i in chunks:
    data += "    " + ", ".join([j for j in i]) + ",\n"

data += \
"""};

#endif//_ARASAKA_H_
"""

with open("arasaka.h", "w") as file:
    file.write(data)

print("Done!")
