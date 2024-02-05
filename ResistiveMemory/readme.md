# Resistive Memory

*Disclaimer: This shouldn't work...but it did for some reason...*

Put a 1KΩ Resistor across 2 arduino uno rev3 analog pins. \
Power one side, then switch to input and read both pins. \
Switch back to output and power only the other side. \
Again, switch back to input and read both pins.

Either orientation appears to read the same for both pins. \
This might be due to an on-board feature of the arduino. \
However, different values are observed without the resistor.

![Memory](/ResistiveMemory/ResistiveMemory.png)
![Charging](/ResistiveMemory/ResistiveMemoryCharging.png)
![Discharging](/ResistiveMemory/ResistiveMemoryDischarging.png)

![ColourCode](/ResistiveMemory/4-5-6-band_resistor_colour_code.png)