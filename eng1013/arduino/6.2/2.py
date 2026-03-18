from pymata4 import pymata4

board = pymata4.Pymata4()

board.set_pin_mode_digital_input(3)

while True:
    try:
        if board.digital_read(3) == 1:
            print("Button is Pressed")
    except KeyboardInterrupt:
        board.shutdown()