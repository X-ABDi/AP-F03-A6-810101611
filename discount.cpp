#include "discount.hpp"

total_price_discount::total_price_discount()
{
    type = "";
    minimum_total = 0;
    value = 0;
}

first_order_discount::first_order_discount()
{
    type = "";
    value = 0;
}

specific_food_discount::specific_food_discount()
{
    type = "";
    food_name = "";
    value = 0;
}

void total_price_discount::set_properties(std::string type_, std::string min, std::string value_)
{
    type = type_;
    minimum_total = std::stof(min);
    value = std::stof(value_);
}

void first_order_discount::set_properties(std::string type_, std::string value_, std::string)
{
    type = type_;
    value = std::stof(value_);
}

void specific_food_discount::set_properties(std::string type_, std::string food_name_, std::string value_)
{
    type = type_;
    food_name = food_name_;
    value = std::stof(value_);
}

std::string specific_food_discount::get_food_name()
{
    return food_name;
}