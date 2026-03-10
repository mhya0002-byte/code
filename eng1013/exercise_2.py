try:
    period = int(input("What is the rental period (Days)? "))
except ValueError:
    print("Invalid data!")
    quit()

size = input("What is the locker size (S/M/L)? ")

if not(size == "S" or size == "M" or size == "L"):
    print("Invalid data!")
    quit()

discount = 1

daily_prices = {"S": 1.38, "M": 4.15, "L": 10.68}

if period >= 180:
    discount = 0.95

price = daily_prices[size] * period * discount

print(f"The price will be ${price}")