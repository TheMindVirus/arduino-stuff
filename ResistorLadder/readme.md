# Resistor Ladder

The DS3502 by Analog Devices (formerly Maxim) contains a Resistor Ladder \
with 0->127 positional precision which emulates a trimpot for calibrating equipment.

![UnoWiring](/ResistorLadder/UnoWiring.png)

Adafruit's DS3502 I2C Digital 10K Potentiometer Breakout Board for Arduino \
showcases the functionality of a Digitally Controlled Analog Circuit.

![DCA](/ResistorLadder/DigitallyControlledAnalog.png)

This specific device makes use of floating gate memristor technology from EEPROM \
for persistent latched memory instead of using field effect transistors or reed relays.

![Redline](/ResistorLadder/DS3502_Redline.png)

The board is wired slightly differently from the usual trim potentiometer for audio \
in that it expects a low value to be ground and a high value to be at full i/o voltage.

![PWM](/ResistorLadder/DS3502_PWM.png)

Here it is performing a variety of different automated analog control signal types, \
using its own library for inter-integrated-circuit (I2C/Wire) to communicate with the arduino.

When breadboarding this circuit by hand, instead of a resistor ladder, all kinds of peripheral \
can be put in place of the resistor (e.g. resistors of different resistivity and density, ceramics etc...)

More Info: https://learn.adafruit.com/ds3502-i2c-potentiometer/python-circuitpython