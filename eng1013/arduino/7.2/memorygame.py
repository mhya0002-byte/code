from pymata4 import pymata4
import random, time

board = pymata4.Pymata4()

input_pins = [3, 4, 5, 6, 7]

output_pins = [8, 9, 10, 11, 12]

for pin in input_pins:
    board.set_pin_mode_digital_input(pin)

for pin in output_pins:
    board.set_pin_mode_digital_output(pin)

def generate_sequence(length):
    sequence = []
    for i in range(length):
        sequence.append(random.randint(0, 4))
    return sequence

def flash_led(pin):
    sleep_time = 0.25
    board.digital_pin_write(output_pins[pin], 1)
    time.sleep(sleep_time)
    board.digital_pin_write(output_pins[pin], 0)
    time.sleep(sleep_time)

sequence_length = 4

sequence = generate_sequence(sequence_length)

#for i in sequence:
#    flash_led(i)

pollInterval = 0
lastPollTime = time.time()
thisPollTime = lastPollTime

input = [[0, 0] for pin in input_pins]

try: 

    while True:

        thisPollTime = time.time()
        
        if thisPollTime - lastPollTime >= pollInterval:
            for pin in input_pins:
                button_number = input_pins.index(pin)
                input[button_number][0] = input[button_number][1]
                input[button_number][1] = board.digital_read(pin)[0]
                if input[button_number] == [1, 0]:
                    print(str(button_number) + " pressed")
                
            lastPollTime = thisPollTime
            #time.sleep(0.1)
        
        
            
        
except KeyboardInterrupt:
    for pin in output_pins:
        board.digital_pin_write(pin, 0)
    board.shutdown()
    time.sleep(0.5)
    exit()