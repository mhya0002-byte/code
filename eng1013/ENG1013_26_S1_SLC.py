# Martin Hyatt
# Last modified 23 Mar 2026
# Version 1.0

def calc_penalty(vehType, roadSpeed, speedLimit):
    """
    Calculates the speeding penalty given to a vehicle
    based on the given data.
        Parameters:
            vehType (boolean): True if the vehicle is heavy.
            roadSpeed (float): Vehicle's speed
            speedLimit (integer): Road's speed limit
        Returns a dictionary containing the overspeed (float), 
        demerit points (integer), suspension months (integer), and fines due (float).
    """

    overSpeed = roadSpeed - speedLimit

    penalty = {"overspeed": overSpeed}

    if vehType == 0:
        if overSpeed < 0:
            penalty["demerits"] = 0
            penalty["suspension"] = 0
            penalty["fines due"] = 0
        elif overSpeed < 10:
            penalty["demerits"] = 1
            penalty["suspension"] = 0
            penalty["fines due"] = 247.00
        elif overSpeed < 25:
            if speedLimit > 100:
                penalty["demerits"] = 0
                penalty["suspension"] = 3
            else:
                penalty["demerits"] = 3
                penalty["suspension"] = 0
            penalty["fines due"] = 395.00
        elif overSpeed < 30:
            penalty["demerits"] = 0
            penalty["suspension"] = 3
            penalty["fines due"] = 543.00
        elif overSpeed < 35:
            penalty["demerits"] = 0
            penalty["suspension"] = 3
            penalty["fines due"] = 642.00
        elif overSpeed < 40:
            penalty["demerits"] = 0
            penalty["suspension"] = 6
            penalty["fines due"] = 741.00
        elif overSpeed < 45:
            penalty["demerits"] = 0
            penalty["suspension"] = 6
            penalty["fines due"] = 840.00
        else:
            penalty["demerits"] = 0
            penalty["suspension"] = 12
            penalty["fines due"] = 988.00

    
    else:
        if overSpeed < 0:
            penalty["demerits"] = 0
            penalty["suspension"] = 0
            penalty["fines due"] = 0
        elif overSpeed < 10:
            penalty["demerits"] = 1
            penalty["suspension"] = 0
            penalty["fines due"] = 324.00
        elif overSpeed < 25:
            if speedLimit > 100:
                penalty["demerits"] = 0
                penalty["suspension"] = 3
                penalty["fines due"] = 740.00
            else:
                if overSpeed < 15:
                    penalty["demerits"] = 3
                    penalty["suspension"] = 0
                    penalty["fines due"] = 509.00
                else:
                    penalty["demerits"] = 3
                    penalty["suspension"] = 0
                    penalty["fines due"] = 740.00
        elif overSpeed < 30:
            penalty["demerits"] = 0
            penalty["suspension"] = 3
            penalty["fines due"] = 1017.00
        elif overSpeed < 35:
            penalty["demerits"] = 0
            penalty["suspension"] = 3
            penalty["fines due"] = 1294.00
        elif overSpeed < 40:
            penalty["demerits"] = 0
            penalty["suspension"] = 6
            penalty["fines due"] = 1572.00
        elif overSpeed < 45:
            penalty["demerits"] = 0
            penalty["suspension"] = 6
            penalty["fines due"] = 1849.00
        else:
            penalty["demerits"] = 0
            penalty["suspension"] = 12
            penalty["fines due"] = 2127.00
    return penalty

        
       

def main():
    """
    Receives and validates vehicle data from user's input, and neatly prints out the 
    data returned by the calc_penalty function, as well as handling restarting and quitting of the program. 
    No parameters or returns
    """

    vehType = input("Are you driving a heavy vehicle? Enter Y/N: ").lower()
    while not(vehType == "y" or vehType == "n"):
        print("Enter Y or N!")
        vehType = input("Are you driving a heavy vehicle? Enter Y/N: ").lower()
    if vehType == "y":
        vehType = True
    else: vehType = False

    while True:
        try:
            speedLimit = int(input("What is the speed limit? Enter an integer in km/h: "))
        except ValueError:
            print("Enter an integer!")
        else:
            break

    while True:
        try:
            roadSpeed = float(input("What is the vehicle's speed? Enter a float in km/h: "))
        except ValueError:
            print("Enter a float!")
        else:
            break
    
    result = calc_penalty(vehType, roadSpeed, speedLimit)

    overSpeed = f"{result["overspeed"]:.2f}"
    print(f"Overspeed: {overSpeed} km/h")

    demerits = result["demerits"]
    if demerits == 0:
        print("No demerit points given")
    else: print(f"{demerits} demerit points given")

    suspension = result["suspension"]
    if suspension == 0:
        print("No automatic license suspension given")
    else: print(f"{suspension} months of automatic license suspension are given")

    fines = f"{result["fines due"]:.2f}"
    if fines == 0:
        print("No fines given")
    else: print(f"A ${fines} fine is given")


    

main()
