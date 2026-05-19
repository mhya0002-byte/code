#include "cheese-shop.h"
#include <format>

using std::format;

cheese_data new_cheese(string name, double weight, int price_per_kg)
{
    cheese_data cheese;

    cheese.name = name;
    cheese.weight = weight;
    cheese.price_per_kg = price_per_kg;

    return cheese;
}

double total_cost(const cheese_data &cheese)
{
    return cheese.weight * cheese.price_per_kg / 100.0;
}

string cheese_to_string(const cheese_data &cheese, bool full_details)
{
    if (full_details)
    {
        return format("{}: {:.2f} kg, ${:.2f}/kg, ${:.2f} total",
                      cheese.name,
                      cheese.weight,
                      cheese.price_per_kg / 100.0,
                      total_cost(cheese));
    }
    else
    {
        return cheese.name;
    }
}

double reduce_weight(cheese_data &cheese, double reduce_weight)
{
    if (reduce_weight >= 0)
    {
        if (reduce_weight > cheese.weight)
        {
            reduce_weight = cheese.weight;
        }

        cheese.weight -= reduce_weight;

        return reduce_weight;
    }
    else
    {
        return 0;
    }
}

double increase_weight(cheese_data &cheese, double increase_weight)
{
    if (increase_weight >= 0)
    {
        cheese.weight += increase_weight;

        return increase_weight;
    }
    else
    {
        return 0;
    }
}

void add_cheese(shop_data &shop, const cheese_data &cheese)
{
    shop.cheeses.add(cheese);
}