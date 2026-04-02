#include "splashkit.h"
#include "utilities.h"

struct book_data
{
    string name;
    string location;
    int pages;
};

enum menu_item
{
    ENTER,
    DETAILS,
    QUIT
};

void print_menu()
{
    write_line("Menu:");
    write_line("1 - Enter book details");
    write_line("2 - Print book");
    write_line("3 - Quit");
}

void print_details(book_data book)
{
    write_line();
    write_line("Book details:");
    write_line("Title: " + book.name);
    write_line("Location: " + book.location);
    write_line("Pages: " + to_string(book.pages));
    write_line();
    
}

book_data new_book()
{
    string name = read_string("Enter the name of the book: ");
    string location = read_string("Enter book location: ");
    int pages = read_integer("Enter number of pages: ");

    book_data book;

    book = {name, location, pages};

    return book;
}

int main()
{
    book_data book;

    write_line("Book entry system:");
    write_line();

    book = new_book();

    bool quit = false;
    do
    {
        print_menu();

        int selected_number = read_integer_range("Option: ", 1, 3) - 1;

        menu_item selected_option = (menu_item)selected_number;

        switch (selected_option)
        {
        case ENTER:
            book = new_book();
            break;
        case DETAILS:
            print_details(book);
            break;
        case QUIT:
            quit = true;
            break;
        default:
            write_line("Error!");
        }
    } while (quit == false);
}