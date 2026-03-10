while True:
    resistor = {
        "black": {
            "value": 0,
            "multi": 1,
            "tol": ""
        },
        "brown": {
            "value": 1,
            "multi": 10,
            "tol": "1%"
        },
        "red": {
            "value": 2,
            "multi": 100,
            "tol": "2%"
        },
        "orange": {
            "value": 3,
            "multi": 1000,
            "tol": "3%"
        },
        "yellow": {
            "value": 4,
            "multi": 10000,
            "tol": "4%"
        },
        "green": {
            "value": 5,
            "multi": 100000,
            "tol": "0.5%"
        },
        "blue": {
            "value": 6,
            "multi": 1000000,
            "tol": "0.25%"
        },
        "violet": {
            "value": 7,
            "multi": 10000000,
            "tol": "0.10%"
        },
        "grey": {
            "value": 8,
            "multi": 100000000,
            "tol": "0.05%"
        },
        "white": {
            "value": 9,
            "multi": 1000000000,
            "tol": ""
        },
        "gold": {
            "value": 0,
            "multi": 0.1,
            "tol": "5%"
        },
        "silver": {
            "value": 0,
            "multi": 0.01,
            "tol": "10%"
        },
        "no band": {
            "value": 0,
            "multi": 0,
            "tol": "20%"
        },
    }
        
    bands = []
    bandText = [
        "first band",
        "second band",
        "third band",
        "multiplier",
        "tolerance"
    ]
        
    # Get all color inputs
    for text in bandText:
        value = input(f"Enter the color value for the {text}: ")
        while value not in resistor:
                value = input(f"Invalid input! Enter the color value for the {text}: ")
        bands.append(value)


        
    # determine resistance
    resistance = ""
    for i in range(3): # 3 resistance value bands = range(3)
        color = bands[i]
        resistance += str(resistor[color]["value"])
        
    resistance = int(resistance)
        
    # add multiplier
    resistance *= resistor[bands[3]]["multi"]
        
    # determine tolerance
    tolerance = resistor[bands[4]]["tol"]
        
    # print result
    print(f"For a resistor with specified color bands as: {';'.join(bands)}")
    print(f"The resistance is {resistance}Ω and tolerance ±{tolerance}.")

    if input("Restart (Y/N)? ") == "N":
         quit()