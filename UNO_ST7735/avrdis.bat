@echo on
rem Export Compiled Binary Manually in Arduino->Sketch
@echo off
set SKETCH=UNO_ST7735
set PATH=%PATH%;%PROGRAMFILES(X86)%/Arduino/hardware/tools/avr/bin/
@echo on
avr-objcopy -I ihex -O elf32-avr %SKETCH%.ino.standard.hex %SKETCH%.elf
avr-objdump -D %SKETCH%.elf > %SKETCH%.txt
@echo off
pause