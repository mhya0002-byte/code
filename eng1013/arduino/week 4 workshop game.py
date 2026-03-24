from pymata4 import pymata4
import time, random

board = pymata4.Pymata4()

board.set_pin_mode_digital_output(8)
board.set_pin_mode_digital_input(3)

pollInterval = 0.1
lastPollTime = time.time()
thisPollTime = lastPollTime


try:
    while True:
        input("Press enter to play")
        #time.sleep(random.randint(3, 5))
        board.digital_pin_write(8, 1)

        result = 0

        while True:
            thisPollTime = time.time()
            if thisPollTime - lastPollTime >= pollInterval:
                result = board.digital_read(3)[0]
                print(result)
                lastPollTime = thisPollTime
                if result == 1:
                    board.digital_pin_write(8, 0)
                    break
            time.sleep(0.001)
            
                
        
    
        

except KeyboardInterrupt:
    board.shutdown()
    time.sleep(0.5)
    exit()