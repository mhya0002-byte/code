def read_grade_list(max_list_length):
    grades = []
    while True:

        if len(grades) == max_list_length:
            break

        grade_input = input("Input a grade out of 100 or press Enter to finish: ")

        try:
            grade_input = int(grade_input)

        except ValueError:
            if grade_input == "":
                break

            else:
                print("Input is not an integer!")

        else:
            if not(0 <= grade_input <= 100):
                print("Input is not within the range of 0-100!")

            else:
                grades.append(grade_input)
            
    return grades

def average(list):
    return sum(list) / len(list)

def count_over_threshold(grades, threshold):
    count = 0
    for grade in grades:
        if grade >= threshold:
            count += 1
    return count

def main():
    grades = read_grade_list(20)

    average_grade = average(grades)
    average_grade = round(average_grade, 2)

    pass_rate = (count_over_threshold(grades, 50) / len(grades)) * 100
    pass_rate = round(pass_rate, 2)

    high_distinction_count = count_over_threshold(grades, 80)

    print("Average grade: " + str(average_grade) + "/100")
    print("Pass rate: " + str(pass_rate) + "%")
    print("Number of high distinctions: " + str(high_distinction_count))

if __name__ == "__main__":
    main()