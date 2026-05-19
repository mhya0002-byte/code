#include "catch_amalgamated.hpp"
#include "cheese-shop.h"

using Catch::Approx;

TEST_CASE("Cheese - Create new cheese with default values")
{
    cheese_data cheese;
    cheese = new_cheese();

    REQUIRE(cheese.name == "");
    REQUIRE(cheese.weight == 0.0);
    REQUIRE(cheese.price_per_kg == 0);
}

TEST_CASE("Cheese - Provice name, weight, and price values for new cheese")
{
    cheese_data cheese;
    cheese = new_cheese("Cheddar", 1.5, 2000);

    REQUIRE(cheese.name == "Cheddar");
    REQUIRE(cheese.weight == Approx(1.5));
    REQUIRE(cheese.price_per_kg == 2000);
}

TEST_CASE("Cheese - Convert cheese data to string")
{
    cheese_data cheese;
    cheese = new_cheese("Cheddar", 1.5, 2000);

    string result = cheese_to_string(cheese, true);
    string expected = "Cheddar: 1.50 kg, $20.00/kg, $30.00 total";

    REQUIRE(result == expected);

    result = cheese_to_string(cheese, false);
    expected = "Cheddar";

    REQUIRE(result == expected);

    cheese = new_cheese("Camembert");

    result = cheese_to_string(cheese, false);
    expected = "Camembert";

    REQUIRE(result == expected);

    result = cheese_to_string(cheese, true);
    expected = "Camembert: 0.00 kg, $0.00/kg, $0.00 total";

    REQUIRE(result == expected);
}

TEST_CASE("Cheese - Calculate total cost of cheese")
{
    cheese_data cheese;
    cheese = new_cheese("Cheddar", 1.5, 2000);

    REQUIRE(total_cost(cheese) == cheese.weight * cheese.price_per_kg / 100.0);

    cheese = new_cheese("Cheddar", 5, 1050);

    REQUIRE(total_cost(cheese) == cheese.weight * cheese.price_per_kg / 100.0);

    cheese = new_cheese("Cheddar", 0, 1050);

    REQUIRE(total_cost(cheese) == cheese.weight * cheese.price_per_kg / 100.0);

    cheese = new_cheese("Cheddar", 5, 0);

    REQUIRE(total_cost(cheese) == cheese.weight * cheese.price_per_kg / 100.0);
}

TEST_CASE("Cheese - Reduce weight of cheese")
{
    cheese_data cheese;
    cheese = new_cheese("Cheddar", 1.5, 2000);

    REQUIRE(reduce_weight(cheese, 1.3) == 1.3);
    REQUIRE(cheese.weight == Approx(0.2));

    cheese.weight = 1.5;
    REQUIRE(reduce_weight(cheese, 1.5) == 1.5);
    REQUIRE(cheese.weight == Approx(0));

    cheese.weight = 1.5;
    REQUIRE(reduce_weight(cheese, 1.7) == 1.5);
    REQUIRE(cheese.weight == Approx(0));

    cheese.weight = 1.5;
    REQUIRE(reduce_weight(cheese, -1.5) == 0);
    REQUIRE(cheese.weight == Approx(1.5));
}

TEST_CASE("Cheese - Increase weight of cheese")
{
    cheese_data cheese;
    cheese = new_cheese("Cheddar", 1.5, 2000);

    REQUIRE(increase_weight(cheese, 1.3) == 1.3);
    REQUIRE(cheese.weight == Approx(2.8));

    cheese.weight = 1.5;
    REQUIRE(increase_weight(cheese, 0) == 0);
    REQUIRE(cheese.weight == Approx(1.5));

    cheese.weight = 1.5;
    REQUIRE(increase_weight(cheese, -1.5) == 0);
    REQUIRE(cheese.weight == Approx(1.5));
}

TEST_CASE("Shop - Can add cheese to the shop")
{
    shop_data shop;

    cheese_data cheese = new_cheese("Cheddar", 1.5, 2000);
    add_cheese(shop, cheese);

    REQUIRE(shop.cheeses.length() == 1);
    REQUIRE(shop.cheeses[0].name == "Cheddar");
    REQUIRE(shop.cheeses[0].weight == Approx(1.5));
    REQUIRE(shop.cheeses[0].price_per_kg == 2000);

    // Add another cheese
    cheese = new_cheese("Gouda", 2.0, 1500);
    add_cheese(shop, cheese);

    REQUIRE(shop.cheeses.length() == 2);
    REQUIRE(shop.cheeses[1].name == "Gouda");
    REQUIRE(shop.cheeses[1].weight == Approx(2.0));
    REQUIRE(shop.cheeses[1].price_per_kg == 1500);
    // Check the first cheese again
    REQUIRE(shop.cheeses[0].name == "Cheddar");
    REQUIRE(shop.cheeses[0].weight == Approx(1.5));
    REQUIRE(shop.cheeses[0].price_per_kg == 2000);
}