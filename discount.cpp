#include "discount.hpp"

void total_price_discount::set_properties(std::string type_, std::string min, std::string value_)
{
    type = type_;
    minimum_total = std::stoi(min);
    value = std::stoi(value_);
}

void first_order_discount::set_properties(std::string type_, std::string value_, std::string)
{
    type = type_;
    value = std::stoi(value_);
}

void specific_food_discount::set_properties(std::string type_, std::string food_name_, std::string value_)
{
    type = type_;
    food_name = food_name_;
    value = std::stoi(value_);
}

std::string specific_food_discount::get_food_name()
{
    return food_name;
}