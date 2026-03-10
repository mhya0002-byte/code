import math

A = input("Enter the length of side A: ")
B = input("Enter the length of side B: ")
C = input("Enter the length of side C: ")

try:
    if A == "":
        A = math.sqrt((float(C)**2) - (float(B)**2))
        print(f"{A:.4f}")

    elif B == "":
        B = math.sqrt((float(C)**2) - (float(A)**2))
        print(f"{B:.4f}")

    elif C == "":
        C = math.sqrt((float(A)**2) + (float(B)**2))
        print(f"{C:.4f}")

    else:
        print("Invalid data!")

except ValueError:
    print("Invalid data!")

