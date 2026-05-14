# This is the code for Subsystem 1, which detects the height of approaching vehicles and operates traffic lights and warning devices to prevent overheight vehicles from entering the tunnel.   
# Created by Martin Hyatt
# Created on Sat 4 April 2026
# Version 1.13

from pymata4 import pymata4
import time

board = pymata4.Pymata4()

# Ask the user to specify an overheight limit. If nothing is entered, default to 4m.
try:
    overheightLimit = int(input("Enter the overheight limit in m: "))
except ValueError:
    overheightLimit = 4

### Ultrasonic sensor initialisation
# The height in metres above the ground at which the sensors are to be placed.
sensorHeight = 10

# Declare pin numbers for the two ultrasonic sensors
us1Trig = 4
us1Echo = 5

us2Trig = 9
us2Echo = 10

board.set_pin_mode_sonar(us1Trig, us1Echo)
board.set_pin_mode_sonar(us2Trig, us2Echo)

# These lists hold the sensor data and the time at which the reading was taken. Here, they are initialised with a default height value of the sensor's height and a default timestamp of 0.
us1Data = [sensorHeight, 0]
us2Data = [sensorHeight, 0]
###

### Shift register initialisation
#   Pin connections for reference:
#
#   VCC       5V
#   QA
#   INPUT
#   OE        GND
#   OUTPUT
#   SHIFT
#   CLEAR     5V
#   QH'

# TL1 green, yellow, red = outputs a, b, c
# TL2 green, yellow, red = outputs d, e, f
# WL1 lights = outputs g, h

# Declare pin numbers for the shift register
registerInputPin = 8
registerOutputPin = 7
registerShiftPin = 6

board.set_pin_mode_digital_output(registerInputPin)
board.set_pin_mode_digital_output(registerOutputPin)
board.set_pin_mode_digital_output(registerShiftPin)
    
# Set default pin states
board.digital_write(registerInputPin, 0)
board.digital_write(registerOutputPin, 0)
board.digital_write(registerShiftPin, 0)

# This list holds the current state of the shift register and is written to the register every cycle.
registerPinState = [0, 0, 0, 0, 0, 0, 0, 0]

def pulse(pin):
    """
    Quickly pulses a pin on and off. Used to control the shift register.
        Parameters:
            pin (integer): The number of the pin to pulse
        Returns:
            Nothing
    """
    board.digital_write(pin, 1)
    board.digital_write(pin, 0)
    
def write_register(state):
    """
    Writes a given byte of data to the shift register.
        Parameters:
            state (list of 8 booleans): The 8 values to be written into the register
        Returns:
            Nothing
    """
    for bit in reversed(state):

        board.digital_write(registerInputPin, bit)

        # push to storage register
        pulse(registerShiftPin)

    # copy storage register to display outputs
    pulse(registerOutputPin)

def set_led(index, value):
    """
    Sets a single bit of the shift register state.
        Parameters:
            index (integer from 0 to 7): The index of the bit to set
            value (boolean): The value to set the bit to
        Returns:
            Nothing
    """
    registerPinState[index] = value

def set_traffic_light(light, colour):
    """
    Sets the colour of one of the two traffic lights.
        Parameters:
            light (integer from 1 to 2): The number of the traffic light to change (TL1 or TL2)
            colour (string): The colour to set the light to
        Returns:
            Nothing
    """
    match light:
        case 1:
            # Clear TL1's bits in the register
            registerPinState[0:3] = [0, 0, 0]
            match colour:
                case "green":
                    set_led(0, 1)
                case "yellow":
                    set_led(1, 1)
                case "red":
                    set_led(2, 1)
        case 2:
            # Clear TL2's bits in the register
            registerPinState[3:3] = [0, 0, 0]
            match colour:
                case "green":
                    set_led(3, 1)
                case "yellow":
                    set_led(4, 1)
                case "red":
                    set_led(5, 1)
    
def set_warning_light(state):
    """
    Controls the state of the two warning lights: Both off, one on, or other one on.
        Parameters:
            state (integer from -1 to 1): Determines the state to set the warning lights to. -1 is off, 0 is one on, 1 is other one on.
        Returns:
            Nothing
    """
    if state == -1:
        set_led(6, 0)
        set_led(7, 0)
    else:
        # Both lights are always opposite states
        set_led(6, state)
        set_led(7, 1 - state)
###

### Buzzer initialisation
buzzerLowPin = 14   # Pin A0
buzzerHighPin = 15  # Pin A1
    
board.set_pin_mode_digital_output(buzzerLowPin)
board.set_pin_mode_digital_output(buzzerHighPin)

def set_buzzer(state):
    """
    Controls the state of the buzzer: Off, low tone, or high tone.
        Parameters:
            state (integer from -1 to 1): Determines the state to set the buzzer to. -1 is off, 0 is low tone, 1 is high tone.
        Returns:
            Nothing
    """
    if state == -1:
        board.digital_write(buzzerLowPin, 0)
        board.digital_write(buzzerHighPin, 0)
    elif state == 0:
        board.digital_write(buzzerLowPin, 1)
    elif state == 1:
        board.digital_write(buzzerHighPin, 1)

# Buzzer starts off
buzzerTone = -1
set_buzzer(buzzerTone)
###

# Sets the initial state of the lights: Both traffic lights green and warning lights off.
set_traffic_light(1, "green")
set_traffic_light(2, "green")
set_warning_light(-1)

# No light patterns are active when the subsystem is started
us1CycleActive = False
us2CycleActive = False
dualCycleActive = False

# Initialise this variable to 0 to ensure comparisons are correct when the program is first run
us1LastOverheightTime = 0

# Average speed of vehicles on the highway in km/h (Arbitrarily chosen to be 100)
highwaySpeed = 100

# Distance between the 2 ultrasonic sensors in m (Specified to be 500)
sensorSpacing = 500

# Time threshold in seconds within which US1 is considered to have detected an overheight vehicle (From 1.R3)
threshold = (sensorSpacing * 3.6) / highwaySpeed

# Output this data to the console
print("Highway speed: " + str(highwaySpeed) + " km/h")
print("Sensor spacing: " + str(sensorSpacing) + " m")
print("Calculated time threshold: " + str(threshold) + " seconds")

# The amount of past values to consider when calculating the moving average
movingAverageSize = 3

# History of the ultrasonic readings, used for calculating the moving average.
us1History = []
us2History = []

loopTime = 0.2

while True:
    try:
            time.sleep(loopTime)

            # Set the buzzer to the currently active tone
            set_buzzer(buzzerTone)

            # Write the current state of the 8 lights to the register
            write_register(registerPinState)            
            
            # Read height data from the sensors
            us1Data = board.sonar_read(us1Trig)[0]
            us2Data = board.sonar_read(us2Trig)[0]
            
            # Add the data to the list of past readings for the moving average to be calculated
            us1History.append(us1Data)
            us2History.append(us2Data)

            # Keep the moving average lists at the specified length by deleting the first (oldest) value when the lists are over the specified length
            if len(us1History) > movingAverageSize:
                us1History.pop(0)
            if len(us2History) > movingAverageSize:
                us2History.pop(0)

            # Calculate the moving average
            us1Data = sum(us1History) / len(us1History)
            us2Data = sum(us2History) / len(us2History)

            # If US1 detects an overheight vehicle, print an alert to the console and begin the light pattern for US1 if it has not already started
            if (us1Data <= (sensorHeight - overheightLimit)):
                print("Overheight vehicle detected! Height: " + str(round(sensorHeight - us1Data, 2)) + "m, Time: " + time.asctime())
                us1LastOverheightTime = time.time()

                if us1CycleActive == False:
                    us1CycleActive = True

            # If US2 detects an overheight vehicle:
            if (us2Data <= (sensorHeight - overheightLimit)):
                # If US2 detects an overheight vehicle after the threshold time has passed (Assuming a different vehicle triggered US1, if any), start the pattern for both traffic lights
                if (time.time() - us1LastOverheightTime) >= threshold:
                    if dualCycleActive == False:
                        dualCycleActive = True
                        dualStartTime = time.time()

                # If US2 detects an overheight vehicle within the threshold time (Assuming same vehicle), start the pattern for only TL2
                elif us2CycleActive == False:
                    us2CycleActive = True
                    us2StartTime = time.time()

            # Set the lights to the correct colour depending on the time and the current pattern to be displayed
            if us1CycleActive:
                if time.time() < us1LastOverheightTime + 1:
                    set_traffic_light(1, "yellow")
                elif us1LastOverheightTime + 1 <= time.time() < us1LastOverheightTime + 31:
                    set_traffic_light(1, "red")
                else:
                    set_traffic_light(1, "green")
                    us1CycleActive = False

            
            elif us2CycleActive:
                if time.time() < us2StartTime + 1:
                    set_traffic_light(2, "yellow")
                elif us2StartTime + 1 <= time.time() < us2StartTime + 31:
                    set_traffic_light(2, "red")
                else:
                    set_traffic_light(2, "green")
                    us2CycleActive = False

            elif dualCycleActive:
                if time.time() < dualStartTime + 1:
                    set_traffic_light(1, "yellow")
                    set_traffic_light(2, "yellow")
                elif dualStartTime + 1 <= time.time() < dualStartTime + 31:
                    set_traffic_light(1, "red")
                    set_traffic_light(2, "red")
                else:
                    set_traffic_light(1, "green")
                    set_traffic_light(2, "green")
                    dualCycleActive = False

            # If any light pattern is currently active, flash the warning lights 4 times per second. Otherwise, turn the warning lights and buzzer off
            if us1CycleActive or us2CycleActive or dualCycleActive:
                wl1State = round(((4 * time.time()) % 2) / 2) # Swaps between 0 and 1 at 4 Hz
                set_warning_light(wl1State)
                if buzzerTone == -1:
                    buzzerTone = 0
            else:
                set_warning_light(-1)
                buzzerTone = -1
        
    except KeyboardInterrupt:
        set_buzzer(-1)
        write_register([0, 0, 0, 0, 0, 0, 0, 0]) # Clear the register
        board.shutdown()
        quit()