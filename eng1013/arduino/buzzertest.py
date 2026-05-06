from pymata4 import pymata4
import time

board = pymata4.Pymata4()

board.set_pin_mode_digital_output(14)
board.set_pin_mode_digital_output(15)


while True:
    try:
        board.digital_write(14, 1)
        board.digital_write(15, 0)
        time.sleep(1)
        board.digital_write(14, 0)
        board.digital_write(15, 1)
        time.sleep(1)
    except KeyboardInterrupt:
        board.shutdown()
    