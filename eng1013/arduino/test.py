from pymata4 import pymata4
import time

board = pymata4.Pymata4()

board.set_pin_mode_digital_output(13)

while True:
    try:
        board.digital_write(13, 1)
        time.sleep(1)
        board.digital_write(13, 0)
        time.sleep(1)
    except KeyboardInterrupt:
        board.shutdown()
    