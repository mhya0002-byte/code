#include <stdlib.h>
#include <new>
#include <utility>
#include <string>

#include "splashkit.h"
#include "utilities.h"

using namespace std;

template <typename T>
class dynamic_array
{
private:
    T *_data;
    int _size;
    int _capacity;

    void resize(int new_capacity)
    {
        if (new_capacity < 2)
        {
            new_capacity = 2;
        }

        T *new_data = (T *)malloc(new_capacity * sizeof(T));

        if (new_data == NULL)
        {
            throw "Memory allocation failed";
        }

        for (int i = 0; i < _size; i++)
        {
            new (&new_data[i]) T(std::move(_data[i]));
            _data[i].~T();
        }

        free(_data);

        _data = new_data;
        _capacity = new_capacity;
    }

public:
    dynamic_array()
    {
        _capacity = 2;
        _size = 0;

        _data = (T *)malloc(_capacity * sizeof(T));

        if (_data == NULL)
        {
            throw "Memory allocation failed";
        }
    }

    // Disable copying
    dynamic_array(const dynamic_array &) = delete;
    dynamic_array &operator=(const dynamic_array &) = delete;

    ~dynamic_array()
    {
        for (int i = 0; i < _size; i++)
        {
            _data[i].~T();
        }

        free(_data);
        _data = NULL;
    }

    void add(const T &value)
    {
        if (_size >= _capacity)
        {
            resize(_capacity * 2);
        }

        new (&_data[_size]) T(value);

        _size++;
    }

    void remove(int index)
    {
        if (_size == 0)
        {
            throw "Cannot remove from empty list";
        }

        if (index < 0 || index >= _size)
        {
            throw "Index out of bounds";
        }

        _data[index].~T();

        for (int i = index; i < _size - 1; i++)
        {
            new (&_data[i]) T(std::move(_data[i + 1]));
            _data[i + 1].~T();
        }

        _size--;

        if (_size < _capacity / 2)
        {
            resize(_capacity / 2);
        }
    }

    T &operator[](int index)
    {
        if (index < 0 || index >= _size)
        {
            throw "Index out of bounds";
        }

        return _data[index];
    }

    int size() const
    {
        return _size;
    }

    int capacity() const
    {
        return _capacity;
    }
};

// ======================================================
// Custom Class for Complex Type Testing
// ======================================================

class person
{
private:
    string _name;

public:
    person(const string &name)
    {
        _name = name;
        write_line("Constructing person: " + _name);
    }

    ~person()
    {
        write_line("Destructing person: " + _name);
    }

    string name() const
    {
        return _name;
    }
};

// ======================================================
// Helper Test Function
// ======================================================

void print_test_result(const string &test_name, bool passed)
{
    if (passed)
    {
        write_line("[PASS] " + test_name);
    }
    else
    {
        write_line("[FAIL] " + test_name);
    }
}

// ======================================================
// Basic Usage Tests
// ======================================================

void test_basic_usage()
{
    write_line("===== BASIC USAGE TESTS =====");

    dynamic_array<int> numbers;

    numbers.add(10);
    numbers.add(20);
    numbers.add(30);

    // PASS TESTS
    print_test_result(
        "Size increases after adding elements",
        numbers.size() == 3
    );

    print_test_result(
        "Get returns correct first value",
        numbers[0] == 10
    );

    print_test_result(
        "Get returns correct third value",
        numbers[2] == 30
    );

    // FAIL TESTS
    print_test_result(
        "Incorrect size expectation",
        numbers.size() == 5
    );

    print_test_result(
        "Incorrect value expectation",
        numbers[1] == 999
    );

    write_line("");
}

// ======================================================
// Capacity Tests
// ======================================================

void test_capacity()
{
    write_line("===== CAPACITY TESTS =====");

    dynamic_array<int> numbers;

    // Initial capacity should be 2
    print_test_result(
        "Initial capacity is 2",
        numbers.capacity() == 2
    );

    numbers.add(1);
    numbers.add(2);

    // Still capacity 2
    print_test_result(
        "Capacity remains 2 before overflow",
        numbers.capacity() == 2
    );

    // This should double capacity to 4
    numbers.add(3);

    print_test_result(
        "Capacity doubles to 4",
        numbers.capacity() == 4
    );

    numbers.add(4);
    numbers.add(5);

    // Should double again to 8
    print_test_result(
        "Capacity doubles to 8",
        numbers.capacity() == 8
    );

    // Remove enough items to shrink
    numbers.remove(0);
    numbers.remove(0);
    numbers.remove(0);

    // Size now 2, capacity should shrink to 4
    print_test_result(
        "Capacity shrinks to 4",
        numbers.capacity() == 4
    );

    // FAIL TESTS
    print_test_result(
        "Incorrect capacity expectation",
        numbers.capacity() == 100
    );

    write_line("");
}

// ======================================================
// Remove Tests
// ======================================================

void test_remove()
{
    write_line("===== REMOVE TESTS =====");

    dynamic_array<int> numbers;

    numbers.add(100);
    numbers.add(200);
    numbers.add(300);

    numbers.remove(1);

    // PASS TESTS
    print_test_result(
        "Size decreases after remove",
        numbers.size() == 2
    );

    print_test_result(
        "Elements shift correctly after remove",
        numbers[1] == 300
    );

    // FAIL TEST
    print_test_result(
        "Incorrect value after remove",
        numbers[1] == 200
    );

    // Exception Test
    try
    {
        numbers.remove(10);
        write_line("[FAIL] Removing invalid index should throw");
    }
    catch (const char *error)
    {
        write_line("[PASS] Exception thrown for invalid index");
        write_line("Error: " + string(error));
    }

    write_line("");
}

// ======================================================
// Complex Type Tests
// ======================================================

void test_complex_type()
{
    write_line("===== COMPLEX TYPE TESTS =====");

    dynamic_array<string> words;

    words.add("apple");
    words.add("banana");
    words.add("cherry");

    // PASS TESTS
    print_test_result(
        "String array stores correct value",
        words[1] == "banana"
    );

    print_test_result(
        "String array size correct",
        words.size() == 3
    );

    // FAIL TEST
    print_test_result(
        "Incorrect string expectation",
        words[2] == "orange"
    );

    write_line("");

    write_line("Testing custom class:");

    dynamic_array<person> people;

    people.add(person("Alice"));
    people.add(person("Bob"));

    print_test_result(
        "Custom class size correct",
        people.size() == 2
    );

    print_test_result(
        "Custom class stores correct data",
        people[0].name() == "Alice"
    );

    // FAIL TEST
    print_test_result(
        "Incorrect custom class expectation",
        people[1].name() == "Charlie"
    );

    write_line("");
}

// ======================================================
// Empty Remove Test
// ======================================================

void test_empty_remove()
{
    write_line("===== EMPTY REMOVE TEST =====");

    dynamic_array<int> numbers;

    try
    {
        numbers.remove(0);
        write_line("[FAIL] Removing from empty list should throw");
    }
    catch (const char *error)
    {
        write_line("[PASS] Exception thrown when removing from empty list");
        write_line("Error: " + string(error));
    }

    write_line("");
}

// ======================================================
// MAIN
// ======================================================

int main()
{
    try
    {
        test_basic_usage();
        test_capacity();
        test_remove();
        test_complex_type();
        test_empty_remove();
    }
    catch (const char *error)
    {
        write_line("Unhandled Error: " + string(error));
    }

    return 0;
}