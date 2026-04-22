from pymata4 import pymata4
import time
board = pymata4.Pymata4()
    
# pin setup
srclr = 4
ser = 5
rclk = 6
srclk = 7
    
# pin mode configuration
board.set_pin_mode_digital_output(srclr)
board.set_pin_mode_digital_output(ser)
board.set_pin_mode_digital_output(rclk)
board.set_pin_mode_digital_output(srclk)
    
# default pin states
board.digital_write(srclk, 0)
board.digital_write(rclk, 0)


def pulse(pin):
    board.digital_write(pin, 1)
    board.digital_write(pin, 0)
    
def clear():
    board.digital_write(srclr, 0)
    board.digital_write(srclr, 1)
    pulse(rclk)

def write_register(state):
    for bit in state:

        board.digital_write(ser, bit)

        # push to storage register
        pulse(srclk)

    # copy storage register to display outputs
    pulse(rclk)

clear()

board.shutdown()