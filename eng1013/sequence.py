def generate_magic_sequence(start, increment, limit):

    try:
        start = int(str(start))
    except ValueError:
        return None
        
    try:
        increment = int(str(increment))
    except ValueError:
        return None
        
    try:
        limit = int(str(limit))
    except ValueError:
        return None

    if not(start >= 1):
        return None

    if not(1 <= increment <= 10):
        return None

    if not(3 <= limit <= 99):
        return None
    
    sequence = []

    sequence.append(start ** 5)

    for i in range(limit - 1):
        last_number_in_sequence = sequence[-1]
        last_digit = last_number_in_sequence % 10
        sequence.append((last_digit + increment) ** 5)

    return(sequence)

print(generate_magic_sequence(3, 2, 5))