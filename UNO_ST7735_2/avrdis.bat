@echo off
set SKETCH=UNO_ST7735_2
set PATH=%PATH%;%PROGRAMFILES(X86)%/Arduino/hardware/tools/avr/bin/
avr-objcopy -I ihex -O elf32-avr %SKETCH%.ino.standard.hex %SKETCH%.elf
avr-objdump -D %SKETCH%.elf > %SKETCH%.txt
rem pause