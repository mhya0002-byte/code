from pymata4 import pymata4
import time

board = pymata4.Pymata4()

try:
    overheightLimit = int(input("Enter the overheight limit in m: "))
except ValueError:
    overheightLimit = 4

us1Trig    = 2
us1Echo    = 3
tl1Green   = 4
tl1Yellow  = 5
tl1Red     = 6

us2Trig    = 7
us2Echo    = 8
tl2Green   = 9
tl2Yellow  = 10
tl2Red     = 11

wl1FirstLight       = 12
wl1SecondLight       = 13

outputPins = [tl1Green, tl1Yellow, tl1Red, tl2Green, tl2Yellow, tl2Red, wl1FirstLight, wl1SecondLight]

for pin in outputPins:
    board.set_pin_mode_digital_output(pin)

board.set_pin_mode_sonar(us1Trig, us1Echo)

board.set_pin_mode_sonar(us2Trig, us2Echo)

pollInterval = 0.25
lastPollTime = time.time()
thisPollTime = lastPollTime

us1Data = [10, 0]
us2Data = [10, 0]

def tl1_off():
    for i in range(3):
        board.digital_pin_write(outputPins[i], 0)

def tl2_off():
    for i in range(3, 6):
        board.digital_pin_write(outputPins[i], 0)

def zero_outputs():
    tl1_off()
    tl2_off()
    board.digital_pin_write(wl1FirstLight, 0)
    board.digital_pin_write(wl1SecondLight, 0)

zero_outputs()

def set_colour(light, colour):
    
    if light == 1:
        tl1_off()
        if colour == "green":
            board.digital_pin_write(tl1Green, 1)
        elif colour == "yellow":
            board.digital_pin_write(tl1Yellow, 1)
        elif colour == "red":
            board.digital_pin_write(tl1Red, 1)
    elif light == 2:
        tl2_off()
        if colour == "green":
            board.digital_pin_write(tl2Green, 1)
        elif colour == "yellow":
            board.digital_pin_write(tl2Yellow, 1)
        elif colour == "red":
            board.digital_pin_write(tl2Red, 1)

set_colour(1, "green")
set_colour(2, "green")

us1CycleActive = False
us2CycleActive = False
dualCycleActive = False

us1StartTime = 0

threshold = 5

try:
    while True:

        thisPollTime = time.time()
        if thisPollTime - lastPollTime >= pollInterval:
            us1Data = board.sonar_read(us1Trig)
            us2Data = board.sonar_read(us2Trig)
            lastPollTime = thisPollTime
            if (us1Data[0] <= (10 - overheightLimit)):
                print("Overheight vehicle detected! Height: " + str(10 - us1Data[0]) + " Time: " + time.asctime())

                if us1CycleActive == False:
                    us1CycleActive = True
                    us1StartTime = time.time()

            if (us2Data[0] <= (10 - overheightLimit)):
                if (time.time() - us1StartTime) >= threshold:
                    if dualCycleActive == False:
                        dualCycleActive = True
                        dualStartTime = time.time()

                elif us2CycleActive == False:
                    us2CycleActive = True
                    us2StartTime = time.time()

            if us1CycleActive:
                if time.time() < us1StartTime + 1:
                    set_colour(1, "yellow")
                if time.time() >= us1StartTime + 1:
                    set_colour(1, "red")
                if time.time() >= us1StartTime + 6:
                    set_colour(1, "green")
                    us1CycleActive = False
            
            if us2CycleActive:
                if time.time() < us2StartTime + 1:
                    set_colour(2, "yellow")
                if time.time() >= us2StartTime + 1:
                    set_colour(2, "red")
                if time.time() >= us2StartTime + 6:
                    set_colour(2, "green")
                    us2CycleActive = False

            if dualCycleActive:
                if time.time() < dualStartTime + 1:
                    set_colour(1, "yellow")
                    set_colour(2, "yellow")
                if time.time() >= dualStartTime + 1:
                    set_colour(1, "red")
                    set_colour(2, "red")
                if time.time() >= dualStartTime + 6:
                    set_colour(1, "green")
                    set_colour(2, "green")
                    dualCycleActive = False

            if us1CycleActive or us2CycleActive or dualCycleActive:
                wl1State = round(((4 * time.time()) % 2) / 2)
                board.digital_pin_write(wl1FirstLight, wl1State)
                board.digital_pin_write(wl1SecondLight, 1 - wl1State)
            else:
                board.digital_pin_write(wl1FirstLight, 0)
                board.digital_pin_write(wl1SecondLight, 0)

                
        time.sleep(0.001)
        
except KeyboardInterrupt:
    time.sleep(1)
    zero_outputs()
    time.sleep(1)
    board.shutdown()
    time.sleep(1)
    exit()
    