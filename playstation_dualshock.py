text = \
"""
portal at voi to the ark - blue circle - playstation net yaroze - red circle - deep space network
bermuda triangle to mars - red triangle - playstation net yaroze - green triangle - corporate research network
end portal to ender city - green square - playstation net yaroze - pink square - nihilist goth network
meridian portal to cubes - pink cross - playstation net yaroze - blue cross - optimist technology network

one side blue circle, other side red circle, colour of the "vessel", in/out
one side red triangle, other side green triangle, colour of the "aurora", out/in
one side green square, other side pink square, colour of the "bittersweet", out/in
one side pink cross, other side blue cross, colour of the "gender", in/out

hidden meaning behind ps1 dualshock sixaxis psvr portal controller:
2 relay battons communicating across a bridge operated by sony in toon perspective
1 cylinder tower knows what the portal glyphs are and the other one doesn't
sony says to one batton, you start communicating what you mean using your language
sony says to the other batton, you select what you think was communicated at the other side
sony can additionally communicate to each batton if they were right (R2/L2) or to shift (R1/L1)
R2 should actually be R0 or R2 should actually be R1 and R1 to R0, same for L2->L0 or L2->L1 and L1->L0
only later did they then allow sony to communicate through an analog light link of which colour was red
the analog button then enabled the two battons to indicate a point of view direction each
one hat was used for positioning and the other used for aiming in most video game disc content
then sony decided the analog button should be always enabled and turned it instead into a guide button
on some controllers there was a turbo button to automatically press certain button sequences
the controller gained a touchpad for sony to be able to gesture to each relay rather than speak in binary
player id for up to four players was indicated by 4 leds of varying colour, blue for wii, red for playstation, green for xbox
the communicator relay batton gained an options button and the receiver relay batton gained a share button
the bridge also gained a small piezo speaker to announce the same message simultaneously to both battons
the red analog mode indicator was sent to the rear side of the bridge and turned blue instead of red
after heavy refactoring it was realised that what linked the two battons was a television display
the colours of the glyphs went somewhat missing in translation as it added unnecessary complexity
some of the toon-like perspective went missing in favour of an empty cold robotic shell appearance

a communication system often used in radio sync coherence testing at the wifi access point bridge

e.g:
* red circle is pressed
* dpad right is guessed
* sony bridge signals correct with either L2/R2, Analog Indicator On or Piezo Speaker Tick
* blue cross is pressed
* dpad up is guessed
* sony bridge signals incorrect with either L1/R1, Analog Indicator Off or Piezo Speaker Buzz
* nothing is pressed
* nothing is guessed
* sony bridge signals nothing with either nL1/nR1/nL2/nR2, Analog Indicator On/Off or Piezo Speaker Silence
* multiple are pressed
* multiple are guessed
* sony bridge signals confusion with any of L1/R1/L2/R2, Analog Indicator Blinking or Piezo Speaker Erroring
* power is overcharged
* recipient is panicked
* sony bridge signals grounded with internal circuitry to protect from sending power spike through user
* power is nulled or sent the wrong way
* recipient is confused
* sony bridge is unable to signal correctly or incorrectly and both sides left to their own devices
* green triangle will be pressed
* dpad up is guessed in presense
* sony bridge will be able to indicate correct or incorrect only after both have answered
* pink square has already been pressed
* all dpad buttons are guessed simultaneously
* sony bridge would normally say the guesser is correct but in certain circumstances must allow only first answer
* the same state as previous has been pressed and nothing happened in between
* the same or maybe different state as previous has been guessed and nothing or something happened in between
* sony bridge may also arbitrate the answer as invalid if stated in the conditions of the quiz quest question query
"""

import random, time, sys, traceback

def obj():
    pass

globe = obj
globe.app = obj
globe.app.counter = random.randint(4444, 999999999) #0
globe.app.bunker = { "Down": 0, "Right": 0, "Left": 0, "Up": 0, "X": 0, "Y": 0, "Z": 0 }
globe.app.bridge = { "L1": 0, "L2": 0, "R1": 0, "R2": 0, "Select": 1, "Start": 1, "Analog": 0 }
globe.app.beacon = { "Cross": 0, "Circle": 0, "Square": 0, "Triangle": 0, "X": 0, "Y": 0, "Z": 0 }

def randomise():
    global globe
    random.seed(random.random())
    random.seed(random.random())
    random.seed(random.random())
    globe.app.beacon["Cross"] = random.randint(0, 1)
    globe.app.beacon["Circle"] = random.randint(0, 1)
    globe.app.beacon["Square"] = random.randint(0, 1)
    globe.app.beacon["Triangle"] = random.randint(0, 1)
    globe.app.bunker["Down"] = random.randint(0, 1)
    globe.app.bunker["Right"] = random.randint(0, 1)
    globe.app.bunker["Left"] = random.randint(0, 1)
    globe.app.bunker["Up"] = random.randint(0, 1)
    globe.app.bunker["X"] = random.randrange(-127, 127)
    globe.app.bunker["Y"] = random.randrange(-127, 127)
    globe.app.bunker["Z"] = 1 if random.randint(0, 100) > 0 else 0
    globe.app.beacon["X"] = random.randrange(-127, 127)
    globe.app.beacon["Y"] = random.randrange(-127, 127)
    globe.app.beacon["Z"] = 1 if random.randint(0, 100) > 0 else 0
    globe.app.bridge["Select"] = 1 if random.randint(0, 10) > 0 else 0
    globe.app.bridge["Start"] = 1 if random.randint(0, 10) > 0 else 0

def process():
    global globe
    globe.app.bridge["L1"] = globe.app.bridge["L2"] = 0
    globe.app.bridge["R1"] = globe.app.bridge["R2"] = 0
    if not globe.app.bridge["Select"]:
        globe.app.bunker["Down"] = 0
        globe.app.bunker["Right"] = 0
        globe.app.bunker["Left"] = 0
        globe.app.bunker["Up"] = 0
    if not globe.app.bridge["Start"]:
        globe.app.beacon["Cross"] = 0
        globe.app.beacon["Circle"] = 0
        globe.app.beacon["Square"] = 0
        globe.app.beacon["Triangle"] = 0
    if ((globe.app.beacon["Cross"] and globe.app.bunker["Down"]) \
    and not (globe.app.beacon["Circle"] or globe.app.bunker["Right"]) \
    and not (globe.app.beacon["Square"] or globe.app.bunker["Left"]) \
    and not (globe.app.beacon["Triangle"] or globe.app.bunker["Up"])) \
    or ((globe.app.beacon["Circle"] and globe.app.bunker["Right"]) \
    and not (globe.app.beacon["Square"] or globe.app.bunker["Left"]) \
    and not (globe.app.beacon["Triangle"] or globe.app.bunker["Up"])) \
    and not (globe.app.beacon["Cross"] or globe.app.bunker["Down"]) \
    or ((globe.app.beacon["Square"] and globe.app.bunker["Left"]) \
    and not (globe.app.beacon["Triangle"] or globe.app.bunker["Up"]) \
    and not (globe.app.beacon["Cross"] or globe.app.bunker["Down"]) \
    and not (globe.app.beacon["Circle"] or globe.app.bunker["Right"])) \
    or ((globe.app.beacon["Triangle"] and globe.app.bunker["Up"]) \
    and not (globe.app.beacon["Cross"] or globe.app.bunker["Down"]) \
    and not (globe.app.beacon["Circle"] or globe.app.bunker["Right"]) \
    and not (globe.app.beacon["Square"] or globe.app.bunker["Left"])):
        globe.app.bridge["L1"] = globe.app.bridge["R1"] = 1
    if not (globe.app.beacon["Cross"] or globe.app.beacon["Circle"] \
        or globe.app.beacon["Square"] or globe.app.beacon["Triangle"]):
        globe.app.bridge["R2"] = 1
    if not (globe.app.bunker["Down"] or globe.app.bunker["Right"] \
        or globe.app.bunker["Left"] or globe.app.bunker["Up"]):
        globe.app.bridge["L2"] = 1
    if globe.app.bridge["L1"] and globe.app.bridge["R1"]:
        globe.app.bridge["Analog"] = 1
    else:
        globe.app.bridge["Analog"] = 0

def frame():
    global globe
    globe.app.counter += 1
    output = ""
    output += "[Arbiter Frame Counter]: "
    output += str(globe.app.counter)
    output += "\n"
    output += "* Dominion Sentinel Bunker: \n "
    output += str(globe.app.bunker)
    output += "\n"
    output += "* Meridian Response Bridge: \n "
    output += str(globe.app.bridge)
    output += "\n"
    output += "* Carilien Distress Beacon: \n "
    output += str(globe.app.beacon)
    output += "\n"
    print(output)
    return output

def condor():
    global globe
    return globe.app.bridge["Analog"]

def auxil(msg = ""):
    global globe
    if globe.app.bunker["Down"] or globe.app.beacon["Cross"]:
        msg += " (Down and Cross were Pressed)"
        #msg += " (Cross was Pressed and Down was Guessed)"
        return msg
    if globe.app.bunker["Right"] or globe.app.beacon["Circle"]:
        msg += " (Right and Circle were Pressed)"
        #msg += " (Circle was Pressed and Right was Guessed)"
        return msg
    if globe.app.bunker["Left"] or globe.app.beacon["Square"]:
        msg += " (Left and Square were Pressed)"
        #msg += " (Square was Pressed and Left was Guessed)"
        return msg
    if globe.app.bunker["Up"] or globe.app.beacon["Triangle"]:
        msg += " (Up and Triangle were Pressed)"
        #msg += " (Triangle was Pressed and Up was Guessed)"
        return msg
    return msg

def bud(msg = "Analog Was Set", cond = condor, aux = auxil):
    global globe
    time.sleep(1)
    if cond and cond():
        if aux:
            msg = str(aux(msg))
        raise Exception(msg)
        return msg
    return None

def exception(error):
    #print(error.with_traceback(error.__traceback__), file = sys.stderr)
    traceback.print_exception(error)
    time.sleep(10)
    print()

while True:
    try:
        randomise()
        process()
        frame()
        bud()
    except Exception as error:
        exception(error)
