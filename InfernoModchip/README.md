# Inferno ModChip for Electric Guitars

Previously, Analog Engineers used PCB's like the one pictured below for mass production \
and to train themselves to solder barewire connections exactly to the same specification.

![screenshot1](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoModchip/screenshot1.png)

Currently, there has been a lack of that same Engineering discipline as everything gets outsourced \
to the factory to mass produce. Micro-Architectural Design and Nano-Technology has also evolved.

![screenshot2](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoModchip/screenshot2.png)

This Strawberry ModChip is intended to be made into a kit that you can solder yourself for electric guitars. \
It could be powered by a toggle from the jack or from USB-C power lines and consists of a wire mod matrix.

```
In the following screenshot we have:
 * The inside of the back of the inside of the back of the Gibson SG / Epiphone CH,
 * The inside of the back of the inside of the back of the Fender Stratocaster / Squier Affinity,
 * The inside of the back of the inside of the back of the Ibanez Gio / Jackson X
```

![screenshot3](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoModchip/screenshot3.png)

In the following Arduino Sketch, the selected pins are listed with labels for identification. \
The `pinMode()` is changed dynamically - one pin is an input and the rest are outputs for a given frame.

![IModChip](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoModchip/IModChip.png)

The output format can then be read by an Analog Signal Processor (ASP - no, not active server pages) \
to use for patching on-board Guitar Reinforcement Synthesis powered by Embedded Virtual Studio Technology [EVST].

~~**__more details on the prototype to follow...__**~~

```diff
- WARNING!: The Following Prototype is Incredibly Dangerous. Please do not try it this way at home!
```

First, I spray painted a piece of Veroboard black and while waiting for the spray paint to cure, \
I cut 9x red wire to length and also cut 2 sets of standard 9x 2.54mm headers to attach to the board.

![IMG_6013](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoModchip/IMG_6013.jpg)

It is incredibly unsafe to spray paint Veroboard and then solder it straight afterwards, <i><b><u>DO NOT ATTEMPT</u></b></i>. \
It sizzles as the solder hardens and the aroma is like a Turkish Barbecue. Please do not inhale toxic fumes.

![IMG_6014](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoModchip/IMG_6014.jpg)

While this was a difficult training challenge to attempt by hand, it could make a fun soldering game \
on mass produced PCB's. The end product could then be made interoperable with certain I2C peripherals.

![IMG_6015](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoModchip/IMG_6015.jpg)

The result is something you can use to patch and modulate audio paths which need a bit of character. \
Update: It not only works for audio, but it also works for graphics! Here is an ST7789 SPI Display using it!

![IMG_6016](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoModchip/IMG_6016.jpg)

The final version would support Audinate's Dante Real-Time Audio/MIDI Networking Protocol over ESP32 Wi-Fi. \
It has previously been tricky to get 64x64 channels at pristine quality without jitter on Wireless Networks. \
A feature which is sorely lacking on professional mixing consoles is line temperature data from instruments for pre-warming. \
This feature could be extended to consumer Audiophile-grade Sound Cards for pre-warming and reading data from Headphones.

![DanteController](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoModchip/DanteController.png)

A Dante ModChip would allow a Live Sound Engineer to control the tonal characteristics of the Electric Guitar. \
However, Artists hate that the audio pipeline gets updated and broken underneath them - They need a Custom ModChip. \
For these reasons, the main operating systems such as Windows and Linux can't be trusted for Live Sound. \
Doing so requires a conscious effort to readjust the sound quality on a different audio route. This requires a Custom ModChip.

<i>Guitar runs Linux, fails on stage due to a faulty Jack (not the plug, the Guitarist is called Jack).</i>
<i>He wiggled the cable too much and the modchip lost power, then he said,</i>
<i><b>"That's what all those capacitors were for!..."</b></i>
