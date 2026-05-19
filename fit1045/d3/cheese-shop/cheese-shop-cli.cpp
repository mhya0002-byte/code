#include "splashkit.h"
#include "utilities.h"
#include "cheese-shop.h"

void print_cheese(const cheese_data &cheese, bool full_details = true)
{
    write_line(cheese_to_string(cheese, full_details));
}

cheese_data read_cheese()
{
    cheese_data cheese = new_cheese(read_string("Name: "), read_double("Weight: "), read_integer("Price per kg: "));

    return cheese;
}

void handle_add_cheese(shop_data &shop)
{
    cheese_data new_cheese = read_cheese();
    add_cheese(shop, new_cheese);
}

void print_cheese_list(const shop_data &shop, bool index = false)
{
    int print_index = 0;

    for (int i = 0; i < shop.cheeses.length(); i++)
    {
        if (index)
        {
            print_index = i + 1;
            write(to_string(print_index) + ": ");
        }
        print_cheese(shop.cheeses.get(i), true);
        write_line();
    }
}

void print_stock_list(const shop_data &shop)
{
    write_line();
    write_line("Stock list:");
    print_cheese_list(shop);
    write_line("End stock list");
    write_line();
}

int select_cheese(const shop_data &shop)
{
    write_line("0: Select none");
    print_cheese_list(shop, true);
    int selection = read_integer("Select option: ");
    return selection - 1;
}

void edit_cheese(cheese_data &cheese)
{
    string new_name = read_string("New name (Enter -1 to keep original): ");
    if (new_name != "-1")
    {
        cheese.name = new_name;
    }
    double new_weight = read_double("New weight (Enter -1 to keep original): ");
    if (new_weight != -1)
    {
        cheese.weight = new_weight;
    }
    int new_price = read_integer("New price/kg (Enter -1 to keep original): ");
    if (new_price != -1)
    {
        cheese.price_per_kg = new_price;
    }
}

void handle_edit_cheese(shop_data &shop)
{
    int edit_index = select_cheese(shop);
    if (edit_index != -1)
    {
        edit_cheese(shop.cheeses.get(edit_index));
    }
}

void delete_cheese(shop_data &shop, int index)
{
    shop.cheeses.remove(index);
}

void handle_delete_cheese(shop_data &shop)
{
    int delete_index = select_cheese(shop);
    delete_cheese(shop, delete_index);
}

enum main_menu_option
{
    EXIT_MAIN_MENU,
    ADD_CHEESE_MENU,
    EDIT_CHEESE_MENU,
    DELETE_CHEESE_MENU,
    PRINT_STOCK_LIST_MENU
};

main_menu_option read_main_menu()
{
    int option_number = read_integer_range("Enter a menu option: ", 0, 4);

    return (main_menu_option)option_number;
}

int main()
{
    shop_data shop;

    main_menu_option choice;

    do
    {
        write_line();
        write_line("0. Exit");
        write_line("1. Add cheese");
        write_line("2. Edit cheese");
        write_line("3. Delete cheese");
        write_line("4. Print cheese list");

        choice = read_main_menu();

        switch (choice)
        {
        case EXIT_MAIN_MENU:
            write_line("Exiting");
            break;

        case ADD_CHEESE_MENU:
            handle_add_cheese(shop);
            break;

        case EDIT_CHEESE_MENU:
            handle_edit_cheese(shop);
            break;

        case DELETE_CHEESE_MENU:
            handle_delete_cheese(shop);
            break;

        case PRINT_STOCK_LIST_MENU:
            print_stock_list(shop);
            break;
        }
    } while (choice != EXIT_MAIN_MENU);

    return 0;
}