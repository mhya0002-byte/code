import math

capacitors = [
0.0000001, 
0.00000001,
0.000001,
0.0000047,
0.00001,
0.000047,
0.0001
]

resistors = [
10,
100,
220,
330,
1000,
2000,
5100,
10000,
100000,
1000000
]

def time_high(r1, r2, c1):
    return math.log(2) * (r1 + r2) * c1

def time_low(r2, c1):
    return math.log(2) * r2 * c1

def frequency(r1, r2, c1):
    return 1 / (math.log(2) * (r1 + 2 * r2) * c1)

data = {}

for c1 in capacitors:
    for r1 in resistors:
        for r2 in resistors:

            freq = frequency(r1, r2, c1)
            th = time_high(r1, r2, c1)
            tl = time_low(r2, c1)

            data[c1, r1, r2] = [freq, th / (th + tl)]

results = {}

for item in data:
    if 2000 <= data[item][0] <= 4000:
        results[item] = data[item]


while len(results) > 0:

    min = list(results)[0]

    for key in results:
        if results[key][1] < results[min][1]:
            min = key
    
    print(min, results.pop(min))