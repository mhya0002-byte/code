#include "splashkit.h"
#include "splashkit-arrays.h"
#include "utilities.h"

const int NO_CHOICE = -1;

struct product_data
{
	string name;
	double cost_price;
	double sale_price;
	int stock;
};

struct store_data
{
	dynamic_array<product_data> products;
	float total_sales;
	double total_profits;
};

void print_product(const product_data &product)
{
	write_line(product.name);
	write_line("Cost price: " + to_string(product.cost_price, 2));
	write_line("Sale price: " + to_string(product.sale_price, 2));
	write_line("Stock:      " + to_string(product.stock));
	write_line();
}

product_data read_product()
{
	product_data product;
	product.name = read_string("Enter product name: ");
	product.cost_price = read_double("Enter cost price: ");
	product.sale_price = read_double("Enter sale price: ");
	product.stock = read_integer("Enter stock: ");
	return product;
}

void add_product(store_data &store)
{
	product_data product = read_product();
	add(store.products, product);
	write_line(product.name + " has been added.");
	write_line();
}

void list_products(const store_data &store)
{
	for (int i = 0; i < store.products.length(); i++)
	{
		write_line(to_string(i + 1) + ": ");
		print_product(store.products.get(i));
	}
	write_line(to_string(store.products.length()) + " products total");
	write_line();
}

int find_product(const store_data &store)
{
	if (store.products.length() == 0)
	{
		write_line("Search cannot be completed, no products have been added!");
		return NO_CHOICE;
	}

	string search_term = read_string("Enter search term: ");

	dynamic_array<int> matches = {};

	for (int i = 0; i < store.products.length(); i++)
	{
		product_data product = store.products.get(i);

		if (contains(product.name, search_term))
		{
			add(matches, i);
			write_line(to_string(i + 1) + ": " + product.name);
		}
	}
	if (length(matches) == 0)
	{
		write_line("No matches were found!");
		return NO_CHOICE;
	}
	int selection = read_integer_range("Select one of the following matches: ", 1, length(store.products)) - 1;
	if (!contains(store.products[selection].name, search_term))
	{
		write_line("Invalid selection!");
		return NO_CHOICE;
	}
	return selection;
}

void sell_product(store_data &store)
{
	int index = find_product(store);
	product_data product = store.products.get(index);

	if (index == NO_CHOICE)
	{
		return;
	}
	if (product.stock == 0)
	{
		write_line("Unable to sell product with no stock!");
		return;
	}

	write_line("Amount in stock: " + to_string(product.stock));

	int sell_amount = read_integer("How many to sell? ");
	while (sell_amount < 0)
	{
		sell_amount = read_integer("How many to sell? ");
	}
	if (sell_amount == 0)
	{
		return;
	}

	double sales = product.sale_price * sell_amount;
	double profit = (product.sale_price - product.cost_price) * sell_amount;

	write_line("Sold " + to_string(sell_amount) + " of product " + product.name + ", with revenue of $" + to_string(sales, 2) + " and profit of $" + to_string(profit, 2) + ". " + to_string(product.stock - sell_amount) + " remaining in stock.");

	product.stock -= sell_amount;
	store.total_profits += profit;
	store.total_sales += sales;
}

void delete_product(store_data &store)
{
	int index = find_product(store);
	product_data product = store.products.get(index);

	if (index == NO_CHOICE)
	{
		return;
	}

	string name = store.products[index].name;
	remove(store.products, index);
	write_line("Deleted product " + name);
}

void update_product(store_data &store)
{
	int index = find_product(store);
	
	if (index == NO_CHOICE)
	{
		return;
	}

	enum update_submenu_option
	{
		UPDATE_NAME = 1,
		UPDATE_COST_PRICE = 2,
		UPDATE_SALE_PRICE = 3,
		UPDATE_STOCK = 4,
		QUIT_UPDATE = 5
	};

	write_line("Update menu: ");
	write_line("1. Update name");
	write_line("2. Update cost price");
	write_line("3. Update sale price");
	write_line("4. Update stock quantity");
	write_line("5. Quit");

	update_submenu_option option;

	option = (update_submenu_option)read_integer_range("Please choose an option: ", 1, 5);

	switch (option)
	{
	case UPDATE_NAME:
		store.products[index].name = read_string("Enter the new name: ");
		return;
	case UPDATE_COST_PRICE:
		store.products[index].cost_price = read_double("Enter the new cost price: ");
		return;
	case UPDATE_SALE_PRICE:
		store.products[index].sale_price = read_double("Enter the new sale price: ");
		return;
	case UPDATE_STOCK:
		store.products[index].stock = read_integer("Enter the new stock: ");
		return;
	case QUIT_UPDATE:
		return;
	} while (option != QUIT_UPDATE);
}

void print_status(const store_data &store)
{
	write_line("Total sales: " + to_string(store.total_sales));
	write_line("Total profit: " + to_string(store.total_profits));
	write_line("Number of products: " + to_string(length(store.products)));

	float stock_value;
}

enum menu_option
{
	ADD_PRODUCT = 1,
	DELETE_PRODUCT = 2,
	UPDATE_PRODUCT = 3,
	SELL_PRODUCT = 4,
	PRINT_STATUS = 5,
	LIST_PRODUCTS = 6,
	QUIT = 7
};

void print_main_menu()
{
	write_line("Main Menu");
	write_line("1. Add a new product");
	write_line("2. Delete a product");
	write_line("3. Update a product");
	write_line("4. Sell a product");
	write_line("5. Print status");
	write_line("6. List products");
	write_line("7. Quit");
}

int main()
{
	store_data store = {};

	add(store.products, product_data{"Eggs", 6, 10, 50});
	add(store.products, product_data{"Bread", 6, 8, 50});
	add(store.products, product_data{"Egg rolls", 10, 15, 50});
	add(store.products, product_data{"Egg salad", 7, 8, 50});

	write_line("Welcome to the product database!");

	menu_option option;
	do
	{
		print_main_menu();
		option = (menu_option)read_integer_range("Please choose an option: ", 1, 7);

		switch (option)
		{
		case ADD_PRODUCT:
			add_product(store);
			break;
		case DELETE_PRODUCT:
			delete_product(store);
			break;
		case UPDATE_PRODUCT:
			update_product(store);
			break;
		case SELL_PRODUCT:
			sell_product(store);
			break;
		case PRINT_STATUS:
			// To implement
			break;
		case LIST_PRODUCTS:
			list_products(store);
			break;
		case QUIT:
			break;
		}
	} while (option != QUIT);
	write_line("Bye!");
	return 0;
}