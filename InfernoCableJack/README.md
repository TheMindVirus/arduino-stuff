# Inferno Cable Jack for Electric Guitars and Modular Synths

This is a quick instructional sequence to make a custom 1m (5) 1/4" M/M Audio Jack
using 9x 1m cuts of red wire, some Neutrik NP3X-B 6.35mm TRS connectors and some cable ties.

```diff
- WARNING!: The Following Prototype is Incredibly Dangerous. Please do not try it this way at home!
```

~~**__more details on the prototype to follow...__**~~

Making a guitar cable can be tricker to actually pull off than it sounds. \
There are a lot of minor things to look out for during the process.

![IMG_6589.JPG](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoCableJack/IMG_6589.JPG)

This will require a soldering iron and I also required a tip change on mine. \
Soldering on the cables first is the first mistake - the rubber gaskets need to go on first.

![IMG_6592.JPG](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoCableJack/IMG_6592.JPG)

The next mistake is thinking that because the gaskets had to go on first, \
the metal shield also needed to go on first which it doesn't - otherwise some desoldering is needed.

![IMG_6594.JPG](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoCableJack/IMG_6594.JPG)

Each cable has to be cut exactly to length before any work on the connectors is done. \
Even after that, the resulting thread may still end up like a wiry mess if not done correctly.

![IMG_6595.JPG](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoCableJack/IMG_6595.JPG)

One minor gripe is that the cable strands have no shielding on them, usually made out of foil. \
If each of the 9 strands aren't shielded then the cable will be subject to electromagnetic interference.

![IMG_6597.JPG](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoCableJack/IMG_6597.JPG)

Pre-tinning the connectors before attaching the cables is highly recommended so that \
the process doesn't end up requiring 3 lots of hands or alien clamps to hold things in place.

![IMG_6599.JPG](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoCableJack/IMG_6599.JPG)

On this specific Neutrik NP3X-B Connector, the lower and middle connectors don't have holes. \
These are the ones that need pre-tinning. Your experience and mileage with connectors may vary.

![IMG_6601.JPG](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoCableJack/IMG_6601.JPG)

Make sure the cable has the 2 rubber gaskets back to back and solder one side first. \
Label the other side with tape and sharpie to keep track of the cable ID of groups of 3 strands.

![IMG_6602.JPG](https://github.com/TheMindVirus/arduino-stuff/blob/main/InfernoCableJack/IMG_6602.JPG)

Finish Soldering the other end, make sure the contacts are isolated from each other, \
screw on the metal housing and optionally add cable ties and twists along the length of the cable.

The resulting cable should ideally look something like what's pictured in the previous photos. \
It will need signal and soak testing and maybe also some light verification and certification \
before it can then be used with any professional audio equipment. It also makes a handy spare \
in case of emergency on stage as and when it's required for Y-splitting etc. etc. etc.

<i>Guitar runs Linux, fails on stage due to a faulty Chip (not the hardware, the Bassist is called Chip).</i>
<i>He bodged an intended fix on the motherboard, then he said,</i>
<i><b>"Why didn't the machinists just get it right in the first place!..."</b></i>
