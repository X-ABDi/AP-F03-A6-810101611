#include "discount.hpp"

total_price_discount::total_price_discount()
{
    type = EMPTY_STRING_VIEW;
    minimum_total = ZERO;
    value = ZERO;
}

first_order_discount::first_order_discount()
{
    type = EMPTY_STRING_VIEW;
    value = ZERO;
}

specific_food_discount::specific_food_discount()
{
    type = EMPTY_STRING_VIEW;
    food_name = EMPTY_STRING_VIEW;
    value = ZERO;
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