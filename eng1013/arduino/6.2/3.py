from pymata4 import pymata4

board = pymata4.Pymata4()

board.set_pin_mode_digital_input(3)
board.set_pin_mode_digital_input(4)
board.set_pin_mode_digital_input(5)
board.set_pin_mode_digital_input(6)
board.set_pin_mode_digital_input(7)

while True:
    try:
        list = []
        for i in range(3, 8):
            if board.digital_read(i)[0]:
                list.append("S" + str(i - 2))
        if list == []:
            list = ["None are pressed!"]
        print(list)
    except KeyboardInterrupt:
        board.shutdown()