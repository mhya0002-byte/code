from pymata4 import pymata4
import time
board = pymata4.Pymata4()
    
# pin setup
clear = 4
input = 5
output = 6
shift = 7
    
# pin mode configuration
board.set_pin_mode_digital_output(clear)
board.set_pin_mode_digital_output(input)
board.set_pin_mode_digital_output(output)
board.set_pin_mode_digital_output(shift)
    
# default pin states
board.digital_write(shift, 0)
board.digital_write(output, 0)


def pulse(pin):
    board.digital_write(pin, 1)
    board.digital_write(pin, 0)
    
def clear():
    board.digital_write(clear, 0)
    board.digital_write(clear, 1)
    pulse(output)

def write_register(state):
    for bit in state:

        board.digital_write(input, bit)

        # push to storage register
        pulse(shift)

    # copy storage register to display outputs
    pulse(output)

clear()

board.shutdown()