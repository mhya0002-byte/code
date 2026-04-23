from pymata4 import pymata4
import time
board = pymata4.Pymata4()
    
# VCC       5V
# QA
# INPUT
# OE        GND
# OUTPUT
# SHIFT
# CLEAR     5V
# QH'

# TL1 green yellow red = outputs a b c
# TL2 green yellow red = outputs d e f
# WL1 lights = outputs g h


# pin setup
registerInputPin = 8
registerOutputPin = 7
registerShiftPin = 6
    
# pin mode configuration
board.set_pin_mode_digital_output(registerInputPin)
board.set_pin_mode_digital_output(registerOutputPin)
board.set_pin_mode_digital_output(registerShiftPin)
    
# default pin states
board.digital_write(registerInputPin, 0)
board.digital_write(registerOutputPin, 0)
board.digital_write(registerShiftPin, 0)

pinState = [0, 0, 0, 0, 0, 0, 0, 0]

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
    pinState = [0, 0, 0, 0, 0, 0, 0, 0]
    write_register(pinState)

def set_led(index, value):
    pinState[index] = value
    write_register(pinState)

def set_colour(light, colour):
    match light:
        case 1:
            pinState[0:3] = [0, 0, 0]
            match colour:
                case "green":
                    pinState[0] = 1
                case "yellow":
                    pinState[1] = 1
                case "red":
                    pinState[2] = 1
        case 2:
            pinState[3:3] = [0, 0, 0]
            match colour:
                case "green":
                    pinState[3] = 1
                case "yellow":
                    pinState[4] = 1
                case "red":
                    pinState[5] = 1
    write_register(pinState)

clear()

time.sleep(1)

# code goes here

time.sleep(1)

clear()

board.shutdown()