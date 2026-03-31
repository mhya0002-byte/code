#include "splashkit.h"

const int MINUTES_PER_HOUR = 60;

int main()
{
    string name;
    double distance, time, speed, remaining_distance, time_to_destination, total_distance, total_time;
    string user_input;

    write("What is your name? ");
    name = read_line();

    write_line();
    write_line("Hi " + name + ".");
    write_line();

    write("How far have you travelled so far? Enter km: ");
    user_input = read_line();
    distance = to_double(user_input);

    write("How long has it taken? Enter minutes: ");
    user_input = read_line();
    time = to_double(user_input);

    speed = distance / (time / MINUTES_PER_HOUR);
    write_line();
    write_line("Your average speed is " + to_string(speed, 2) + " km/h.");
    write_line();

    write_line("How far do you have left to go? Enter km: ");
    user_input = read_line();
    remaining_distance = to_double(user_input);

    time_to_destination = remaining_distance / speed * MINUTES_PER_HOUR;

    write_line("You will take another " + to_string(time_to_destination, 2) + " minutes to reach your destination.");

    total_distance = distance + remaining_distance;
    total_time = time + time_to_destination;

    write_line("Total distance will be " + to_string(total_distance, 2) + " km.");
    write_line("Total time will be " + to_string(total_time, 2) + " mins.");
}