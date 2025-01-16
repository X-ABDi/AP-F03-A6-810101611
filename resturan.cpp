#include "resturan.hpp"

// resturan::resturan() 
// {
//     food_discount = false;
//     last_reserve_id = 0;
// }

// resturan::~resturan()
// {
// }

void resturan::set_menu (std::string raw_menu)
{
    std::regex re(";"); 
    std::sregex_token_iterator it(raw_menu.begin(), raw_menu.end(), re, -1);
    std::sregex_token_iterator end;
    
    std::vector<std::string> tokens;
    for (; it != end; ++it) {
        tokens.push_back(it->str());
    }
    for (auto i : tokens)
    {
        size_t pos = i.find(":");
        menu[i.substr(0, pos)].first = std::stof(i.substr(pos+1));
    }
}

void resturan::set_tables (std::string table_number)
{
    for (int i=0; i<stoi(table_number); i++)
    {
        table* new_table = new table;
        new_table->table_id = i+1;
        new_table->reserved = false;
    }
}

void resturan::set_total_dis(std::string total_dis_prop)
{
    if (total_dis_prop == NONE)
    {
        // std::cout << "total discount success" << std::endl;
        return;
    }
    std::stringstream ss = std::stringstream();
    ss << total_dis_prop;
    std::string type;
    getline(ss, type, SEMI_COLON);
    std::string minimum;
    getline(ss, minimum, SEMI_COLON);
    std::string value;
    getline(ss, value, SEMI_COLON);
    total_dis.set_properties(type, minimum, value);
    // std::cout << "total discount success" << std::endl;
}

void resturan::set_first_dis (std::string first_dis_prop)
{
    if (first_dis_prop == NONE)
    {
        // std::cout << "first discount success" << std::endl;
        return;
    }    
    std::stringstream ss = std::stringstream();
    ss << first_dis_prop;
    std::string type;
    getline(ss, type, SEMI_COLON);
    std::string value;
    getline(ss, value, SEMI_COLON);
    first_dis.set_properties(type, value, EMPTY_STRING);
    // std::cout << "first discount success" << std::endl;
}

std::vector<std::string> parse_food_discount (std::string food_dis_prop)
{  
    // std::cout << "parse food discount" << std::endl;
    std::vector<std::string> every_food;
    std::string food;
    std::stringstream ss = std::stringstream();
    ss << food_dis_prop;
    while (getline(ss, food, '|'))
    {
        // std::cout << food << std::endl;
        every_food.push_back(food);
    }
    return every_food;    
}

void resturan::put_in_menu (specific_food_discount* food_dis)
{
    menu[food_dis->get_food_name()].second = food_dis;
}

void resturan::set_food_dis (std::string food_dis_prop)
{
    if (food_dis_prop == NONE)
    {    
        food_discount = false;
        // std::cout << "food dis success" <<std::endl;
        return;
    }
    food_discount = true;
    std::vector<std::string> every_food;
    every_food = parse_food_discount (food_dis_prop);
    std::string type;
    std::string food_name;
    std::string value;
    std::stringstream ss = std::stringstream();
    for (auto i : every_food)
    {
        ss << i;
        getline(ss, type, SEMI_COLON);
        getline(ss, food_name, COLON_CHAR);
        getline(ss, value);
        specific_food_discount* new_food_dis = new specific_food_discount;
        new_food_dis->set_properties(type, food_name, value);
        put_in_menu(new_food_dis);
    }
    // std::cout << "food dis success" <<std::endl;
}

void resturan::get_discounts_detail(std::string &respond)
{
    if (total_dis.type != EMPTY_STRING_VIEW)
    {
        respond += output_get::RESTURAN_ORDER_DISCOUNT;
        respond += total_dis.type;
        respond += output_common::COMMA;
        respond += std::to_string(total_dis.minimum_total);
        respond += output_common::COMMA;
        respond += std::to_string(total_dis.value);
        respond += output_common::NEW_LINE;
    }
    if (food_discount == true)
    {
        respond += output_get::RESTURAN_ITEM_DISCOUNT;
        for (auto i : menu)
        {
            if (i.second.second->type != EMPTY_STRING_VIEW)
            {
                respond += i.first;
                respond += output_common::PARANTHESE_OPEN;
                respond += i.second.second->type;
                respond += output_common::COLON;
                respond += std::to_string(i.second.second->value);
                respond += output_common::COMMA;
            }
        }
        respond = respond.substr(0, respond.length()-2);
        respond += output_common::NEW_LINE;
    }
    if (first_dis.type != EMPTY_STRING_VIEW)
    {
        respond += output_get::RESTURAN_FIRST_DISCOUNT;
        respond += first_dis.type;
        respond += output_common::COMMA;
        respond += std::to_string(first_dis.value);
        respond += output_common::NEW_LINE;
    }
}
