#include "splashkit.h"
#include "splashkit-arrays.h"
#include "utilities.h"

dynamic_array<int> read_grade_list(int max_list_length)
{
    dynamic_array<int> grades;
    while (true)
    {
        if (length(grades) >= max_list_length)
        {
            break;
        }

        string grade_input = read_string("Input a grade out of 100 or press Enter to finish: ");

        if (grade_input == "")
        {
            break;
        }

        if (!is_integer(grade_input))
        {
            write_line("Input is not an integer!");
        }
        else
        {
            int integer_grade_input = to_integer(grade_input);
            if (0 <= integer_grade_input and integer_grade_input <= 100)
            {
                grades.add(integer_grade_input);
            }
            else
            {
                write_line("Input is not within the range of 0-100!");
            }
        }
    }
    return grades;
}

double sum(dynamic_array<int> list)
{
    int sum = 0;
    for (int i = 0; i < length(list); i++)
    {
        sum += list.get(i);
    }
    return sum;
}

double average(dynamic_array<int> list)
{
    return (sum(list) / length(list));
}

double count_over_threshold(dynamic_array<int> list, int threshold)
{
    double count = 0;
    for (int i = 0; i < length(list); i++)
    {
        int grade = list.get(i);
        if (grade >= threshold)
        {
            count++;
        }
    }
    return count;
}

int main()
{
    dynamic_array<int> grades = read_grade_list(20);

    double average_grade = average(grades);
    string string_average_grade = to_string(average_grade, 2);

    double pass_rate = ((count_over_threshold(grades, 50) / length(grades)) * 100);
    string string_pass_rate = to_string(pass_rate, 2);

    int high_distinction_count = count_over_threshold(grades, 80);
    string string_high_distinction_count = to_string(high_distinction_count);

    write_line("Average grade: " + string_average_grade + "/100");
    write_line("Pass rate: " + string_pass_rate + "%");
    write_line("Number of high distinctions: " + string_high_distinction_count);

    return 0;
}