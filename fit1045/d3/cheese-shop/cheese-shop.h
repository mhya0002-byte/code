#include "splashkit.h"
#include "splashkit-arrays.h"
#include <string>

using std::string;

struct cheese_data
{
    string name;
    double weight;
    int price_per_kg;
};

struct shop_data
{
    dynamic_array<cheese_data> cheeses;
};

cheese_data new_cheese(string name = "", double weight = 0.0, int price_per_kg = 0);

string cheese_to_string(const cheese_data &cheese, bool full_details = false);

double total_cost(const cheese_data &cheese);

double reduce_weight(cheese_data &cheese, double reduce_weight);

double increase_weight(cheese_data &cheese, double increase_weight);

void add_cheese(shop_data &shop, const cheese_data &cheese);
