import math

A = input("Enter the length of side A: ")
B = input("Enter the length of side B: ")
C = input("Enter the length of side C: ")

if A == "":
    A = math.sqrt((float(C)**2) - (float(B)**2))
    print(A)

elif B == "":
    B = math.sqrt((float(C)**2) - (float(A)**2))
    print(B)

elif C == "":
    C = math.sqrt((float(A)**2) + (float(B)**2))
    print(C)

else:
    print("Invalid data!")