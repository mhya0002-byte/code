# Created by: Martin Hyatt
# Date: 23 Mar 2026
# Version: 1.7

def calc_penalty(vehType, roadSpeed, speedLimit):
    """
    Calculates the speeding penalty given to a vehicle
    based on the given data.
        Parameters:
            vehType (boolean): True if the vehicle is heavy.
            roadSpeed (float): Vehicle's speed
            speedLimit (integer): Road's speed limit
        Returns a dictionary containing the overspeed (float), as well as a list containing 
        the demerit points (integer), suspension months (integer), and fines due (float).
    """

    overSpeed = roadSpeed - speedLimit

    if overSpeed < 0:
        overSpeed = 0

    penalty = {"overspeed": overSpeed, "penalties": [0, 0, 0.00]}

    if not vehType:

        if speedLimit > 100 and 10 <= penalty["overspeed"] < 25:                
                penalty["penalties"] = [0, 3, 395.00]

        else:
            if penalty["overspeed"] < 0:
                penalty["penalties"] = [0, 0, 0.00]
            elif penalty["overspeed"] < 10:
                penalty["penalties"] = [1, 0, 247.00]
            elif penalty["overspeed"] < 25:           
                penalty["penalties"] = [3, 0, 395.00]
            elif penalty["overspeed"] < 30:
                penalty["penalties"] = [0, 3, 543.00]
            elif penalty["overspeed"] < 35:
                penalty["penalties"] = [0, 3, 642.00]
            elif penalty["overspeed"] < 40:
                penalty["penalties"] = [0, 6, 741.00]
            elif penalty["overspeed"] < 45:
                penalty["penalties"] = [0, 6, 840.00]
            else:
                penalty["penalties"] = [0, 12, 988.00]

    
    else:
            
            if speedLimit > 100 and 10 <= penalty["overspeed"] < 25:                
                penalty["penalties"] = [0, 3, 740.00]

            else:
                if penalty["overspeed"] < 0:
                    penalty["penalties"] = [0, 0, 0.00]
                elif penalty["overspeed"] < 10:
                    penalty["penalties"] = [1, 0, 324.00]
                elif penalty["overspeed"] < 15:
                    penalty["penalties"] = [3, 0, 509.00]
                elif penalty["overspeed"] < 25:
                    penalty["penalties"] = [3, 0, 740.00]
                elif penalty["overspeed"] < 30:
                    penalty["penalties"] = [0, 3, 1017.00]
                elif penalty["overspeed"] < 35:
                    penalty["penalties"] = [0, 3, 1294.00]
                elif penalty["overspeed"] < 40:
                    penalty["penalties"] = [0, 6, 1572.00]
                elif penalty["overspeed"] < 45:
                    penalty["penalties"] = [0, 6, 1849.00]
                else:
                    penalty["penalties"] = [0, 12, 2127.00]
    return penalty

def main():
    """
    Receives and validates vehicle data from user's input, and neatly prints out the 
    data returned by the calc_penalty function, as well as handling restarting and quitting of the program. 
    No parameters or returns
    """
    try:
        while True:
            vehType = input("Are you driving a heavy vehicle? Enter Y/N: ")
            while not(vehType == "Y" or vehType == "N"):
                print("Enter Y or N!")
                vehType = input("Are you driving a heavy vehicle? Enter Y/N: ")
            if vehType == "Y":
                vehType = True
            else: 
                vehType = False

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

            overSpeed = result["overspeed"]
            overSpeed = f"{overSpeed:.2f}"
            print(f"Overspeed: {overSpeed} km/h")

            demerits = result["penalties"][0]
            if demerits == 0:
                print("No demerit points given")
            else: 
                print(f"{demerits} demerit points given")

            suspension = result["penalties"][1]
            if suspension == 0:
                print("No automatic license suspension given")
            else: 
                print(f"{suspension} months of automatic license suspension are given")

            fines = result["penalties"][2]
            fines = f"{fines:.2f}"
            if fines == "0.00":
                print("No fines given")
            else: 
                print(f"A ${fines} fine is given")

            restart = input("Restart? Enter Y/N: ")
            while not(restart == "Y" or restart == "N"):
                print("Enter Y or N!")
                restart = input("Restart? Enter Y/N: ")
            if restart == "N":
                print("Exiting")
                exit()
    except KeyboardInterrupt:
        print("\nUser Keyboard Interrupt - Exiting")

if __name__ == "__main__":
    main()