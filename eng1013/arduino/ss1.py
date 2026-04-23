from pymata4 import pymata4
import time

board = pymata4.Pymata4()

try:
    overheightLimit = int(input("Enter the overheight limit in m: "))
except ValueError:
    overheightLimit = 4

### Ultrasonic sensor initialisation
sensorHeight = 10

us1Trig         = 2
us1Echo         = 3

us2Trig         = 7
us2Echo         = 8

board.set_pin_mode_sonar(us1Trig, us1Echo)
board.set_pin_mode_sonar(us2Trig, us2Echo)

us1Data = [sensorHeight, 0]
us2Data = [sensorHeight, 0]
###

### Shift register initialisation
#   VCC       5V
#   QA
#   INPUT
#   OE        GND
#   OUTPUT
#   SHIFT
#   CLEAR     5V
#   QH'

# TL1 green yellow red = outputs a b c
# TL2 green yellow red = outputs d e f
# WL1 lights = outputs g h

registerInputPin = 8
registerOutputPin = 7
registerShiftPin = 6
    
board.set_pin_mode_digital_output(registerInputPin)
board.set_pin_mode_digital_output(registerOutputPin)
board.set_pin_mode_digital_output(registerShiftPin)
    
# default pin states
board.digital_write(registerInputPin, 0)
board.digital_write(registerOutputPin, 0)
board.digital_write(registerShiftPin, 0)

registerPinState = [0, 0, 0, 0, 0, 0, 0, 0]

def pulse(pin):
    board.digital_write(pin, 1)
    board.digital_write(pin, 0)
    
def write_register(state):
    for bit in reversed(state):

        board.digital_write(registerInputPin, bit)

        # push to storage register
        pulse(registerShiftPin)

    # copy storage register to display outputs
    pulse(registerOutputPin)

def clear():
    registerPinState = [0, 0, 0, 0, 0, 0, 0, 0]
    write_register(registerPinState)

def set_led(index, value):
    registerPinState[index] = value
    write_register(registerPinState)

def set_traffic_light(light, colour):
    match light:
        case 1:
            registerPinState[0:3] = [0, 0, 0]
            match colour:
                case "green":
                    registerPinState[0] = 1
                case "yellow":
                    registerPinState[1] = 1
                case "red":
                    registerPinState[2] = 1
        case 2:
            registerPinState[3:3] = [0, 0, 0]
            match colour:
                case "green":
                    registerPinState[3] = 1
                case "yellow":
                    registerPinState[4] = 1
                case "red":
                    registerPinState[5] = 1
    write_register(registerPinState)

def set_warning_light(state):
    if state == "off":
        set_led(6, 0)
        set_led(7, 0)
    else:
        set_led(6, state)
        set_led(7, 1 - state)
###

clear()

set_traffic_light(1, "green")
set_traffic_light(2, "green")

us1CycleActive = False
us2CycleActive = False
dualCycleActive = False

us1StartTime = 0

threshold = 5

movingAverageSize = 3

us1History = []
us2History = []

pollInterval = 0.25
lastPollTime = time.time()
thisPollTime = lastPollTime

try:
    while True:
        thisPollTime = time.time()

        if thisPollTime - lastPollTime >= pollInterval:
            us1Data = board.sonar_read(us1Trig)[0]
            us2Data = board.sonar_read(us2Trig)[0]
            
            us1History.append(us1Data)
            us2History.append(us2Data)

            if len(us1History) > movingAverageSize:
                us1History.pop(0)

            if len(us2History) > movingAverageSize:
                us2History.pop(0)

            us1Data = sum(us1History) / len(us1History)
            us2Data = sum(us2History) / len(us2History)

            lastPollTime = thisPollTime

            if (us1Data <= (sensorHeight - overheightLimit)):
                print("Overheight vehicle detected! Height: " + str(round(sensorHeight - us1Data, 2)) + "m, Time: " + time.asctime())

                if us1CycleActive == False:
                    us1CycleActive = True
                    us1StartTime = time.time()

            if (us2Data <= (sensorHeight - overheightLimit)):
                if (time.time() - us1StartTime) >= threshold:
                    if dualCycleActive == False:
                        dualCycleActive = True
                        dualStartTime = time.time()

                elif us2CycleActive == False:
                    us2CycleActive = True
                    us2StartTime = time.time()

            if us1CycleActive:
                if time.time() < us1StartTime + 1:
                    set_traffic_light(1, "yellow")
                if time.time() >= us1StartTime + 1:
                    set_traffic_light(1, "red")
                if time.time() >= us1StartTime + 6:
                    set_traffic_light(1, "green")
                    us1CycleActive = False
            
            if us2CycleActive:
                if time.time() < us2StartTime + 1:
                    set_traffic_light(2, "yellow")
                if time.time() >= us2StartTime + 1:
                    set_traffic_light(2, "red")
                if time.time() >= us2StartTime + 6:
                    set_traffic_light(2, "green")
                    us2CycleActive = False

            if dualCycleActive:
                if time.time() < dualStartTime + 1:
                    set_traffic_light(1, "yellow")
                    set_traffic_light(2, "yellow")
                if time.time() >= dualStartTime + 1:
                    set_traffic_light(1, "red")
                    set_traffic_light(2, "red")
                if time.time() >= dualStartTime + 6:
                    set_traffic_light(1, "green")
                    set_traffic_light(2, "green")
                    dualCycleActive = False

            if us1CycleActive or us2CycleActive or dualCycleActive:
                wl1State = round(((4 * time.time()) % 2) / 2)
                set_warning_light(wl1State)
            else:
                set_warning_light("off")

                
        time.sleep(0.001)
        
except KeyboardInterrupt:
    time.sleep(1)
    clear()
    time.sleep(1)
    board.shutdown()
    time.sleep(1)
    exit()
    