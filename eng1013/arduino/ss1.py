from pymata4 import pymata4
import time

board = pymata4.Pymata4()

try:
    overheight_limit = int(input("Enter the overheight limit in m: "))
except ValueError:
    overheight_limit = 4

us1_trig    = 2
us1_echo    = 3
tl1_green   = 4
tl1_yellow  = 5
tl1_red     = 6

us2_trig    = 7
us2_echo    = 8
tl2_green   = 9
tl2_yellow  = 10
tl2_red     = 11

output_pins = [tl1_green, tl1_yellow, tl1_red, tl2_green, tl2_yellow, tl2_red]

for pin in output_pins:
    board.set_pin_mode_digital_output(pin)

board.set_pin_mode_sonar(us1_trig, us1_echo)

board.set_pin_mode_sonar(us2_trig, us2_echo)

pollInterval = 0.25
lastPollTime = time.time()
thisPollTime = lastPollTime

us1_data = [10, 0]
us2_data = [10, 0]

def TL1Off():
    for i in range(3):
        board.digital_pin_write(output_pins[i], 0)

def TL2Off():
    for i in range(3, 6):
        board.digital_pin_write(output_pins[i], 0)

def zeroOutputs():
    TL1Off()
    TL2Off()

zeroOutputs()

def setColour(light, colour):
    
    if light == 1:
        TL1Off()
        if colour == "green":
            board.digital_pin_write(tl1_green, 1)
        elif colour == "yellow":
            board.digital_pin_write(tl1_yellow, 1)
        elif colour == "red":
            board.digital_pin_write(tl1_red, 1)
    elif light == 2:
        TL2Off()
        if colour == "green":
            board.digital_pin_write(tl2_green, 1)
        elif colour == "yellow":
            board.digital_pin_write(tl2_yellow, 1)
        elif colour == "red":
            board.digital_pin_write(tl2_red, 1)

setColour(1, "green")
setColour(2, "green")

us1CycleActive = False
us2CycleActive = False
dualCycleActive = False

us1StartTime = 0

threshold = 5

try:
    while True:

        thisPollTime = time.time()
        if thisPollTime - lastPollTime >= pollInterval:
            us1_data = board.sonar_read(us1_trig)
            us2_data = board.sonar_read(us2_trig)
            lastPollTime = thisPollTime
            if (us1_data[0] <= (10 - overheight_limit)):
                print("Overheight vehicle detected! Height: " + str(10 - us1_data[0]) + " Time: " + time.asctime())

                if us1CycleActive == False:
                    us1CycleActive = True
                    us1StartTime = time.time()

            if (us2_data[0] <= (10 - overheight_limit)):
                if (time.time() - us1StartTime) >= threshold:
                    if dualCycleActive == False:
                        dualCycleActive = True
                        dualStartTime = time.time()

                elif us2CycleActive == False:
                    us2CycleActive = True
                    us2StartTime = time.time()

            if us1CycleActive == True:
                if time.time() < us1StartTime + 1:
                    setColour(1, "yellow")
                if time.time() >= us1StartTime + 1:
                    setColour(1, "red")
                if time.time() >= us1StartTime + 6:
                    setColour(1, "green")
                    us1CycleActive = False
            
            if us2CycleActive == True:
                if time.time() < us2StartTime + 1:
                    setColour(2, "yellow")
                if time.time() >= us2StartTime + 1:
                    setColour(2, "red")
                if time.time() >= us2StartTime + 6:
                    setColour(2, "green")
                    us2CycleActive = False

            if dualCycleActive == True:
                if time.time() < dualStartTime + 1:
                    setColour(1, "yellow")
                    setColour(2, "yellow")
                if time.time() >= dualStartTime + 1:
                    setColour(1, "red")
                    setColour(2, "red")
                if time.time() >= dualStartTime + 6:
                    setColour(1, "green")
                    setColour(2, "green")
                    dualCycleActive = False

                
        time.sleep(0.001)
        
except KeyboardInterrupt:
    time.sleep(1)
    zeroOutputs()
    time.sleep(1)
    board.shutdown()
    time.sleep(1)
    exit()
    