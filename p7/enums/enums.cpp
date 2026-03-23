#include "splashkit.h"
#include "utilities.h"

enum day
{
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
};

string to_string(day d)
{
    switch (d)
    {
        case SUNDAY:
            return "Sunday";
        case MONDAY:
            return "Monday";    
        case TUESDAY:
            return "Tuesday";    
        case WEDNESDAY:
            return "Wednesday";    
        case THURSDAY:
            return "Thursday";    
        case FRIDAY:
            return "Friday";    
        case SATURDAY:
            return "Saturday";    
        default:
            return "Invalid day";    
    }
}

int main()
{
    // Enum variable declaration
    day today;

    // Assigning a value to the enum variable
    today = WEDNESDAY;

    // Print the value of today
    write_line("Today is " + to_string(today));

    return 0;
}