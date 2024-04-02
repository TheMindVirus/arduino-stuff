import board, analogio, pwmio

#LED = pwmio.PWMOut(board.LED, duty_cycle = 32768, frequency = 1, variable_frequency = True)
LED = pwmio.PWMOut(board.LED, duty_cycle = 65535, frequency = 1, variable_frequency = True)

AIL = analogio.AnalogIn(board.A0)
AIR = analogio.AnalogIn(board.A3) #VOLTAGE_MONITOR #ADC_VREF

AOL = pwmio.PWMOut(board.GP4, duty_cycle = 0, frequency = 320000, variable_frequency = True)
AOR = pwmio.PWMOut(board.GP7, duty_cycle = 0, frequency = 320000, variable_frequency = True)
#duty_cycle is instead full volume 0-65535 not duty_cycle 0-50

print("[_AIL]: " + str(AIL.reference_voltage) + "V")
print("[_AIR]: " + str(AIR.reference_voltage) + "V")

while True:
     AOL.duty_cycle = AIL.value; AOR.duty_cycle = AIR.value

#while True:
#    AOL.duty_cycle = AIL.value # & 0xFFFFF70 #if AIL.value > 0 else 0
#    AOR.duty_cycle = AIR.value # & 0xFFFFF70 #if AIR.value > 0 else 0
#    #AOL.duty_cycle = min(max(abs(AIL.value - 32768), 0), 65535) 
#    #AOR.duty_cycle = min(max(abs(AIR.value - 32768), 0), 65535)

"""

import board, digitalio, analogio, pwmio, audiopwmio, audiocore, audiomixer, array, time

LED = digitalio.DigitalInOut(board.LED)
LED.switch_to_output(value = True)

T = 0.001
AOL.duty_cycle = 50
AOL.frequency = 65535
#AOR.duty_cycle = 0 #50

while True:
    AOL.duty_cycle = 100 #65535
    #AOR.duty_cycle = 50
    time.sleep(T)
    AOL.duty_cycle = 0
    #AOR.duty_cycle = 0
    time.sleep(T)
"""
"""
MIN = 9999999
MAX = 0
i = 0

while True:
    LVL = (AIL.value - 32768) * 0.01
    ABS = LVL
    if LVL < 0:
        ABS = 0 #abs(LVL)
    AOL.duty_cycle = min(max(int(ABS), 0), 50)
    AOR.duty_cycle = AOL.duty_cycle
    if LVL < MIN:
        MIN = LVL
    if LVL > MAX:
        MAX = LVL
    i += 1
    if i >= 1000:
        i = 0
        print(int(MIN), int(MAX), int(LVL))
        MIN = 9999999
        MAX = 0
"""
"""
while True:
    #AOL.duty_cycle = min(max(int((AIL.value >> 8) - 100), 0), 50)
    #AOR.duty_cycle = min(max(int((AIR.value >> 8) - 100), 0), 50)
    AOL.duty_cycle = min(max(int((AIL.value / 65535) * 100), 0), 50)
    AOR.duty_cycle = AOL.duty_cycle
    print((AIL.value / 65535) * 100)
    #print(int((AIL.value >> 8) - 100))
    #print(int((AIR.value >> 7) - 200))
    #print(AOL.duty_cycle)
    #print(AOL.frequency)
"""
"""
for i in dir(board):
    print(str(i) + ": ", end = "")
    try:
        print(eval("analogio.AnalogIn(board." + i + ")"), end = "")
    except Exception as error:
        print(error, end = "")
    print()
"""

"""
import math
#length = 48000 // 440
#sine_wave = array.array("H", [0] * length)
#for i in range(length):
#    sine_wave[i] = int(math.sin(math.pi * 2 * i / length) * (2 ** 15) + 2 ** 15)
#test = audiocore.RawSample(sine_wave, sample_rate = 48000)
square_wave = array.array("H", [0] * 2)
square_wave[0] = 0 * 65535
square_wave[1] = 1 * 65535
test = audiocore.RawSample(square_wave, sample_rate = 2)

SR = 1

AEL = digitalio.DigitalInOut(board.A1)
AER = digitalio.DigitalInOut(board.A2)
AFL = digitalio.DigitalInOut(board.GP5)
AFR = digitalio.DigitalInOut(board.GP6)

AEL.direction = digitalio.Direction.INPUT #switch_to_input()
AER.direction = digitalio.Direction.INPUT #switch_to_input()
AFL.direction = digitalio.Direction.INPUT #switch_to_input()
AFR.direction = digitalio.Direction.INPUT #switch_to_input()

AIL = analogio.AnalogIn(board.A0)
AIR = analogio.AnalogIn(board.A3) #VOLTAGE_MONITOR

AOL = pwmio.PWMOut(board.GP4, duty_cycle = 50, frequency = 48000, variable_frequency = True)
AOR = pwmio.PWMOut(board.GP7, duty_cycle = 50, frequency = 48000, variable_frequency = True)

#AOL = audiopwmio.PWMAudioOut(board.GP4, quiescent_value = 0)
#AOR = audiopwmio.PWMAudioOut(board.GP7, quiescent_value = 0)

#AXL = audiomixer.Mixer(sample_rate = SR, voice_count = 1, channel_count = 1, bits_per_sample = 16, samples_signed = False)
#AXR = audiomixer.Mixer(sample_rate = SR, voice_count = 1, channel_count = 1, bits_per_sample = 16, samples_signed = False)

AZL = array.array("H", [0])
AZR = array.array("H", [0])

#AOL.play(test, loop = True)
#AOR.play(test, loop = True)
#while True:
#    pass

while True:
    AZL[0] = min(65535, AIL.value) # * 3)
    AZR[0] = min(65535, AIR.value) # * 3)
    #print(AZL[0])
    AOL.play(audiocore.RawSample(AZL), loop = True)
    AOR.play(audiocore.RawSample(AZR), loop = True)
    #AXL.voice[0].play(audiocore.RawSample(AZL, sample_rate = SR))
    #AXR.voice[0].play(audiocore.RawSample(AZR, sample_rate = SR))
    #AOL.play(AXL)
    #AOR.play(AXR)
"""

"""
__class__: Expected a Pin
__name__: Expected a Pin
A0: <AnalogIn>
A1: <AnalogIn>
A2: <AnalogIn>
A3: <AnalogIn>
GP0: Pin does not have ADC capabilities
GP1: Pin does not have ADC capabilities
GP10: Pin does not have ADC capabilities
GP11: Pin does not have ADC capabilities
GP12: Pin does not have ADC capabilities
GP13: Pin does not have ADC capabilities
GP14: Pin does not have ADC capabilities
GP15: Pin does not have ADC capabilities
GP16: Pin does not have ADC capabilities
GP17: Pin does not have ADC capabilities
GP18: Pin does not have ADC capabilities
GP19: Pin does not have ADC capabilities
GP2: Pin does not have ADC capabilities
GP20: Pin does not have ADC capabilities
GP21: Pin does not have ADC capabilities
GP22: Pin does not have ADC capabilities
GP23: Pin does not have ADC capabilities
GP24: Pin does not have ADC capabilities
GP25: LED in use
GP26: GP26_A0 in use
GP26_A0: GP26_A0 in use
GP27: GP27_A1 in use
GP27_A1: GP27_A1 in use
GP28: GP28_A2 in use
GP28_A2: GP28_A2 in use
GP3: Pin does not have ADC capabilities
GP4: Pin does not have ADC capabilities
GP5: Pin does not have ADC capabilities
GP6: Pin does not have ADC capabilities
GP7: Pin does not have ADC capabilities
GP8: Pin does not have ADC capabilities
GP9: Pin does not have ADC capabilities
LED: LED in use
SMPS_MODE: Pin does not have ADC capabilities
VBUS_SENSE: Pin does not have ADC capabilities
VOLTAGE_MONITOR: A3 in use
board_id: Expected a Pin
"""