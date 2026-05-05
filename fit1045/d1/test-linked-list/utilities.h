#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
using std::string;

/**
 * Read a string from the user
 *
 * @param prompt the message to show the user
 * @returns the string entered
 */
string read_string(string prompt);

/**
 * Read an integer from the user
 *
 * @param prompt the message to show the user
 * @returns the integer entered
 */
int read_integer(string prompt);

/**
 * Read a double from the user
 *
 * @param prompt the message to show the user
 * @returns the double entered
 */
double read_double(string prompt);

/**
 * Read an integer from the user, only accepting values between the bounds (bounds are interchangable)
 *
 * @param prompt the message to show the user
 * @param bound_1 the lower bound
 * @param bound_2 the upper bounds
 * @returns the integer entered
 */
int read_integer_range(string prompt, int bound_1, int bound_2);

#endif