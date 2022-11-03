# Inferno ModChip for Electric Guitars

Previously, Analog Engineers used PCB's like the one pictured below for mass production \
and to train themselves to solder barewire connections exactly to the same specification.

![screenshot1](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoModchip/screenshot1.png)

Currently, there has been a lack of that same Engineering discipline as everything gets outsourced \
to the factory to mass produce. Microarchitectural Design and Nanotechnology has also evolved.

![screenshot2](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoModchip/screenshot2.png)

This ModChip is intended to be made into a kit that you can solder yourself for electric guitars. \
It could be powered by a toggle from the jack or from USB-C power lines and consists of a wire mod matrix.

![screenshot3](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoModchip/screenshot3.png)

In the following Arduino Sketch, the selected pins are listed with labels for identification. \
The `pinMode()` is changed dynamically - one pin is an input and the rest are outputs for a given frame.

![IModChip](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoModchip/IModChip.png)

The output format can then be read by an Analog Signal Processor (ASP - no, not active server pages) \
to use for patching on-board Guitar Reinforcement Synthesis powered by Embedded Virtual Studio Technology [EVST].

**__more details on the prototype to follow...__**