#include "software.hpp"

software::software() : current_user(std::make_shared<user>()), all_resturans(std::make_shared<std::map<std::string, resturan*>>()),
                        all_users(std::make_shared<std::map<std::string, std::shared_ptr<user>>>())
{
    // std::cout << "software constructor: " ;
    std::cout << current_user->logged_in << std::endl;
}

software::software(std::shared_ptr<software> soft_obj) 
{
    
}

software::~software()
{
}

bool software::logged_in()
{
    return current_user->logged_in;
}

void software::get_budget(std::string &respond)
{
    if (logged_in() == false)
        throw errors(error_message::PERMISSION_DENIED);
    respond = std::to_string(current_user->wallet);    
}

void software::resturan_init (std::vector<std::string> &rest_prop)
{
    // for (auto i : rest_prop)
    //     std::cout << i << std::endl;
    resturan *new_resturan = new resturan;
    new_resturan->name = rest_prop[0];
    new_resturan->district = rest_prop[1];
    new_resturan->set_menu(rest_prop[2]);
    new_resturan->working_time.first = stoi(rest_prop[3]);
    new_resturan->working_time.second = stoi(rest_prop[4]);
    new_resturan->set_tables(rest_prop[5]);
    districts.set_resturans(rest_prop[1], new_resturan);
    (*all_resturans)[new_resturan->name] = new_resturan; 
}

void software::district_init (std::vector<std::string> &dist_prop)
{
    district *new_district = new district;
    new_district->set_neighbors(dist_prop);
}

void software::discount_init (std::vector<std::string> &disc_prop)
{
    (*all_resturans)[disc_prop[0]]->set_total_dis(disc_prop[1]);
    (*all_resturans)[disc_prop[0]]->set_first_dis(disc_prop[2]);
    (*all_resturans)[disc_prop[0]]->set_food_dis(disc_prop[3]);
}

void software::set_district (std::string district_name)
{
    if (!districts.user_district_check(district_name))
        throw errors(error_message::NOT_FOUND);
    current_user->district = district_name;
}

void software::delete_reserve (std::vector<std::string> &command_entered)
{
    if ((*all_resturans).count(command_entered[2]) == 0)
        throw errors(error_message::NOT_FOUND);
    if ((*all_resturans)[command_entered[2]]->reserves.count(command_entered[3]) == 0)  
        throw errors(error_message::NOT_FOUND);
    if ((*all_resturans)[command_entered[2]]->reserves[command_entered[3]]->username != current_user->username)
        throw errors(error_message::PERMISSION_DENIED);
    current_user->wallet += (*all_resturans)[command_entered[2]]->reserves[command_entered[2]]->discount_price*discount_type::RETURN_PERCENT; 
    (*all_resturans)[command_entered[2]]->reserves.erase(command_entered[2]);
    (*current_user->reserves).erase(command_entered[3]); 
}

void software::get_district(std::string_view district_name, std::string &respond)
{
    districts.get_district(district_name, respond);
}

void software::get_all_districts(std::string &respond)
{
    if (districts.district_neighbors.size() == 0)
        throw errors(error_message::EMPTY);
    districts.get_all_districts(respond);  
}

void software::get_resturans(std::string food_name, std::string &respond)
{
    if (current_user->district == EMPTY_STRING_VIEW)
        throw errors(error_message::NOT_FOUND);
    if ((*all_resturans).size() == 0)
        throw errors(error_message::EMPTY);
    std::string_view user_district = current_user->district;    
    districts.get_resturans(user_district, food_name, respond);  
    if (respond == EMPTY_STRING_VIEW)
        throw errors(error_message::EMPTY);
}

void software::sort_reserves_by_times(resturan* my_resturan, std::pair<std::string, table *> &i, std::vector<std::pair<std::string,rest_reserve*>> &reserves)
{
    for (auto j : i.second->reseve_ids)
    {
        reserves.push_back((*my_resturan->reserves.find(j)));
    }
    sort(reserves.begin(), reserves.end(), [](std::pair<std::string, rest_reserve*> a, std::pair<std::string, rest_reserve*> b){return a.second->time_interval.first < b.second->time_interval.first;});
}

void software::resturan_detail_tables(std::string resturan_name, std::string &respond)
{
    std::vector<std::pair<std::string,rest_reserve*>> sorted_reserves;
    for (std::pair<std::string, table *> i : (*all_resturans)[resturan_name]->tables)
    {
        respond += i.first;
        respond += output_common::COLON;
        sort_reserves_by_times((*all_resturans)[resturan_name], i, sorted_reserves);
        for (auto j : sorted_reserves)
        {
            respond += output_common::PARANTHESE_OPEN;
            respond += std::to_string(j.second->time_interval.first);
            respond += output_common::HYPHEN;
            respond += std::to_string(j.second->time_interval.second);
            respond += output_common::PARANTHESE_CLOSE;
            respond += output_common::COMMA;   
        }
        respond = respond.substr(0, respond.length()-2);
        respond += output_common::NEW_LINE;
    }
}

void software::resturan_detail_discounts(std::string resturan_name, std::string &respond)
{
    (*all_resturans)[resturan_name]->get_discounts_detail(respond);
}

void software::get_resturan_detail(std::string resturan_name, std::string &respond)
{
    if ((*all_resturans).count(resturan_name) == 0)
        throw errors(error_message::NOT_FOUND);
    respond += output_get::RESTURAN_NAME;
    respond += (*all_resturans)[resturan_name]->name;
    respond += output_common::NEW_LINE;
    respond += output_get::RESTURAN_DISTRICT;
    respond += (*all_resturans)[resturan_name]->district;
    respond += output_common::NEW_LINE;
    respond += output_get::RESTURAN_TIME;
    respond += (*all_resturans)[resturan_name]->working_time.first;
    respond += output_common::HYPHEN;
    respond += (*all_resturans)[resturan_name]->working_time.second;
    respond += output_common::NEW_LINE;
    respond += output_get::RESTURAN_MENU;
    for (auto i : (*all_resturans)[resturan_name]->menu)
    {
        respond += i.first;
        respond += output_common::PARANTHESE_OPEN;
        respond += std::to_string(i.second.first);
        respond += output_common::PARANTHESE_CLOSE;
        respond += output_common::COMMA;
    }    
    respond = respond.substr(0, respond.length()-2);
    respond += output_common::NEW_LINE;
    resturan_detail_tables(resturan_name, respond);
    resturan_detail_discounts(resturan_name, respond);
}

void software::get_all_reserves(std::string &respond)
{
    for (auto i : (*current_user->reserves))
    {
        respond += i.second->reserve_id;
        respond += output_common::COLON;
        respond += i.second->resturan_name;
        respond += output_common::SPACE;
        respond += i.second->table_id;
        respond += output_common::SPACE;
        respond += i.second->time_interval.first;
        respond += output_common::HYPHEN;
        respond += i.second->time_interval.second;
        respond += output_common::SPACE;
        if (!i.second->foods.empty())
        {
            for (auto j : i.second->foods)
            {
                respond += j.first;
                respond += output_common::PARANTHESE_OPEN;
                respond += std::to_string(j.second.first);
                respond += output_common::PARANTHESE_CLOSE;
                respond += output_common::SPACE;
            }
            respond += std::to_string(i.second->raw_price);
            respond += output_common::SPACE;
            respond += std::to_string(i.second->discount_price);    
        }
        respond += output_common::NEW_LINE;
    }
}

void software::get_resturan_reserves(std::vector<std::string> &command_entered, std::string &respond)
{
    if (find_if((*current_user->reserves).begin(), (*current_user->reserves).end(), [command_entered](std::pair<std::string, user_reserve*> a){return a.second->resturan_name == command_entered[2];}) == (*current_user->reserves).end())
        throw errors(error_message::EMPTY);
    for (auto i : (*current_user->reserves))
    {
        if (i.second->resturan_name == command_entered[2])
        {
            respond += i.second->reserve_id;
            respond += output_common::COLON;
            respond += i.second->resturan_name;
            respond += output_common::SPACE;
            respond += i.second->table_id;
            respond += output_common::SPACE;
            respond += i.second->time_interval.first;
            respond += output_common::HYPHEN;
            respond += i.second->time_interval.second;
            respond += output_common::SPACE;
            if (!i.second->foods.empty())
            {
                for (auto j : i.second->foods)
                {
                    respond += j.first;
                    respond += output_common::PARANTHESE_OPEN;
                    respond += std::to_string(j.second.first);
                    respond += output_common::PARANTHESE_CLOSE;
                    respond += output_common::SPACE;
                }
                respond += std::to_string(i.second->raw_price);
                respond += output_common::SPACE;
                respond += std::to_string(i.second->discount_price);    
            }
            respond += output_common::NEW_LINE;
        }
    }
}

void software::get_resturan_one_reserve(std::vector<std::string> &command_entered, std::string &respond)
{
    if ((*all_resturans).count(command_entered[2]) == 0)
        throw errors(error_message::NOT_FOUND);
    if ((*all_resturans)[command_entered[2]]->reserves.count(command_entered[3]) == 0)
        throw errors(error_message::NOT_FOUND);
    if ((*all_resturans)[command_entered[2]]->reserves[command_entered[3]]->username != current_user->username)
        throw errors(error_message::PERMISSION_DENIED);
    respond += command_entered[3];
    respond += output_common::COLON;
    respond += command_entered[2];
    respond += output_common::SPACE;
    respond += (*all_resturans)[command_entered[2]]->reserves[command_entered[3]]->table_id;
    respond += output_common::SPACE;
    respond += (*all_resturans)[command_entered[2]]->reserves[command_entered[3]]->time_interval.first;
    respond += output_common::HYPHEN;
    respond += (*all_resturans)[command_entered[2]]->reserves[command_entered[3]]->time_interval.second;
    respond += output_common::SPACE;
    if (!(*all_resturans)[command_entered[2]]->reserves[command_entered[3]]->foods.empty())
    {
        for (auto i : (*all_resturans)[command_entered[2]]->reserves[command_entered[3]]->foods)
        {
            respond += i.first;
            respond += output_common::PARANTHESE_OPEN;
            respond += std::to_string(i.second.first);
            respond += output_common::PARANTHESE_CLOSE;
            respond += output_common::SPACE;
        }
        respond += (*all_resturans)[command_entered[2]]->reserves[command_entered[3]]->raw_price;
        respond += output_common::SPACE;
        respond += (*all_resturans)[command_entered[2]]->reserves[command_entered[3]]->discount_price;    
    }   
    respond += output_common::NEW_LINE;
}

void software::get_reserves(std::vector<std::string> &command_entered, std::string &respond)
{
    if ((*current_user->reserves).empty())
        throw errors(error_message::EMPTY);
    if (command_entered.size() == 2)
        get_all_reserves(respond);
    if (command_entered.size() == 3)
        get_resturan_reserves(command_entered, respond); 
    if (command_entered.size() == 4)
        get_resturan_one_reserve(command_entered, respond);          
}

void software::signup(std::vector<std::string> &command_entered)
{
    std::map<std::string, std::shared_ptr<user>>::iterator map_it;
    map_it = find_if((*all_users).begin(), (*all_users).end(), [command_entered](std::pair<std::string, std::shared_ptr<user>> a){return a.first == command_entered[2];});
    if (map_it != (*all_users).end())
    {
        if (map_it->second->password != command_entered[3])
            throw errors(error_message::BAD_REQUEST);
        else
        {
            if (current_user->logged_in == true)
                throw errors(error_message::PERMISSION_DENIED);
            else
            {
                current_user = map_it->second;  
                current_user->logged_in = true;
            }  
        }     
    }           
    else
    {
        std::shared_ptr<user> new_user = std::make_shared<user>(command_entered[2], command_entered[3]);
        (*all_users).insert({command_entered[2], new_user});
        current_user = new_user;
        current_user->logged_in = true;
    }
}

void software::login(std::vector<std::string> &command_entered)
{
    if (find_if((*all_users).begin(), (*all_users).end(), [command_entered](std::pair<std::string, std::shared_ptr<user>> a){return a.second->username==command_entered[2];}) == (*all_users).end())
        throw errors(error_message::NOT_FOUND);
    std::map<std::string, std::shared_ptr<user>>::iterator map_it;
    map_it = find_if((*all_users).begin(), (*all_users).end(), [command_entered](std::pair<std::string, std::shared_ptr<user>> a){return a.second->username==command_entered[2];});
    if ((*map_it).second->password != command_entered[3])
        throw errors(error_message::PERMISSION_DENIED);
    if (current_user->logged_in == true)
        throw errors(error_message::PERMISSION_DENIED);
    current_user = (*map_it).second;
    current_user->logged_in = true;            
}

void software::logout()
{
    // std::cout << "in software logout" << std::endl;
    // if (current_user->logged_in == false)
    //     throw errors(error_message::PERMISSION_DENIED);
    current_user->logged_in = false;    
}

void parse_foods(std::string foods, std::map<std::string, std::pair<float, int>> &food_vec)
{
    std::stringstream ss = std::stringstream();
    ss << foods;
    while (ss.good())
    {
        getline (ss, foods, ',');
        if (food_vec.count(foods) == 0)
            food_vec[foods] = {0, 1};
        else
            food_vec[foods].second += 1;    
    }
}

std::string calculate_price (std::map<std::string, std::pair<float, int>> &foods)
{
    float sum=0;
    for (auto i : foods)
        sum += i.second.first*i.second.second;
    return std::to_string(sum);   
}

std::string software::calculate_specific_discounts (std::map<std::string, std::pair<float, int>> &foods, std::map<std::string, resturan*>::iterator &map_it)
{
    if (map_it->second->food_discount == false)
        return ZERO_STR;
    float specific_discount=0;    
    for (auto i : foods)
    {
        if(map_it->second->menu[i.first].second->type == discount_type::AMOUNT)
            specific_discount += (map_it->second->menu[i.first].second->value)*float(i.second.second);
        else if(map_it->second->menu[i.first].second->type == discount_type::PERCENT)
            specific_discount += (map_it->second->menu[i.first].second->value*float(map_it->second->menu[i.first].first)/100)*i.second.second;
    }  
    std::string respond = "";
    respond += output_post::RESERVE_ITEM_DISCOUNT;
    respond += std::to_string(specific_discount);
    respond += output_common::NEW_LINE;
    return respond;
}

std::string software::calculate_first_discount (std::string price, std::map<std::string, resturan*>::iterator &map_it)
{
    if (map_it->second->first_dis.type == EMPTY_STRING_VIEW)
        return ZERO_STR;
    if (map_it->second->first_dis.type == discount_type::AMOUNT)
        price = map_it->second->first_dis.value;
    else if (map_it->second->first_dis.type == discount_type::PERCENT)
        price = std::to_string(std::stof(price)*float(map_it->second->first_dis.value)/100);    
    std::string respond="";
    respond += output_post::RESERVE_FIRST_DISCOUNT;
    respond += price;
    respond += output_common::NEW_LINE;
    return respond;
}

std::string software::calculate_order_discount (std::string price, std::map<std::string, resturan*>::iterator &map_it)
{
    if (map_it->second->total_dis.type == EMPTY_STRING_VIEW)
        return ZERO_STR;
    else if (map_it->second->total_dis.type == discount_type::AMOUNT)
        price = std::to_string(map_it->second->total_dis.value);
    else if (map_it->second->total_dis.type == discount_type::PERCENT)
        price = std::to_string(std::stof(price)*float(map_it->second->total_dis.value)/100);
    std::string respond = "";
    respond += output_post::RESERVE_ORDER_DISCOUNT;
    respond += price;
    respond += output_common::NEW_LINE;
    return respond;            
}

void software::set_reserve(std::vector<std::string> &command_entered, std::map<std::string, std::pair<float, int>> &foods, std::map<std::string, resturan*>::iterator &map_it, std::string &respond)
{
    rest_reserve* rest_res = new rest_reserve;
    user_reserve* user_res = new user_reserve;
    rest_res->table_id = command_entered[3];
    user_res->table_id = command_entered[3];
    rest_res->username = current_user->username;
    user_res->resturan_name = command_entered[2];
    int res_id = map_it->second->last_reserve_id;
    res_id += 1;
    map_it->second->last_reserve_id = res_id;
    rest_res->reserve_id = res_id;
    user_res->reserve_id = res_id;
    rest_res->time_interval.first = std::stoi(command_entered[4]);
    user_res->time_interval.first = std::stoi(command_entered[4]);
    rest_res->time_interval.second = std::stoi(command_entered[5]);
    user_res->time_interval.second = std::stoi(command_entered[5]);
    if (command_entered.size() == 7)
    {
        for (auto i : foods)
        {
            user_res->foods[i.first] = {i.second.first, i.second.second};
            rest_res->foods[i.first] = {i.second.first, i.second.second};
        }
    }
    (*current_user->reserves)[std::to_string(res_id)] = user_res;
    (*all_resturans)[map_it->first]->reserves[std::to_string(res_id)] = rest_res;
    respond += output_post::RESERVE_ID;
    respond += std::to_string(res_id);
    respond += output_common::NEW_LINE;
    respond += output_post::RESERVE_TABLE_1;
    respond += command_entered[3];
    respond += output_post::RESERVE_TABLE_2;
    respond += command_entered[4];
    respond += output_post::RESERVE_TABLE_3;
    respond += command_entered[5];
    respond += output_post::RESERVE_TABLE_4;
    respond += command_entered[2];
    respond += output_common::NEW_LINE;
    respond += output_post::RESERVE_ORIGINAL_PRICE;
    if (command_entered.size() == 7)
    {
        std::string price = calculate_price(foods);
        rest_res->raw_price = std::stof(price);
        user_res->raw_price = std::stof(price);
        respond += price;
        respond += output_common::NEW_LINE;
        std::string item_discount = calculate_specific_discounts(foods, map_it);
        price = std::to_string(std::stof(price) - std::stof(item_discount));
        std::string first_discount = calculate_first_discount(price,map_it);
        price = std::to_string(std::stof(price) - std::stof(first_discount));
        std::string order_discount = calculate_order_discount(price, map_it);
        price = std::to_string(std::stof(price) - std::stof(order_discount));
        respond += order_discount+item_discount+first_discount;
        respond += output_post::RESERVE_TOTAL_DISCOUNT;
        respond += std::to_string(std::stof(order_discount)+std::stof(item_discount)+std::stof(first_discount));
        respond += output_common::NEW_LINE;
        respond += output_post::RESERVE_TOTAL_PRICE;
        if (std::stof(price) < 0)
        {
            rest_res->discount_price = 0;
            user_res->discount_price = 0;
            respond += ZERO_STR;
            respond += output_common::NEW_LINE;
        }    
        else
        {
            rest_res->discount_price = std::stof(price);
            user_res->discount_price = std::stof(price);
            respond += price;
            respond += output_common::NEW_LINE; 
        }    

    }
    else
    {
        rest_res->raw_price = 0;
        user_res->raw_price = 0;
        rest_res->discount_price = 0;
        user_res->discount_price = 0;
        respond += ZERO_STR;
        respond += output_common::NEW_LINE;
    }   
    if (current_user->wallet < rest_res->discount_price)
        throw errors(error_message::BAD_REQUEST);
    else
        current_user->wallet -= rest_res->discount_price;
}

void software::reserve(std::vector<std::string> &command_entered, std::string &respond)
{
    std::map<std::string, resturan*>::iterator map_it;
    std::map<std::string, std::pair<float, int>> foods;
    map_it = find_if((*all_resturans).begin(), (*all_resturans).end(), [command_entered](std::pair<std::string, resturan*> a){return a.first==command_entered[2];});
    if (map_it == (*all_resturans).end())
        throw errors(error_message::NOT_FOUND);
    if (find_if(map_it->second->tables.begin(), map_it->second->tables.end(), [command_entered](std::pair<std::string, table*> a){return a.second->table_id==command_entered[3];}) == map_it->second->tables.end())
        throw errors(error_message::NOT_FOUND);
    if (command_entered.size() == 7)
    {
        parse_foods(command_entered[6], foods);
        std::map<std::string, std::pair<float, specific_food_discount*>>::iterator menu_it;
        for (auto i : foods)
        {
            menu_it = find_if(map_it->second->menu.begin(), map_it->second->menu.end(), [i](std::pair<std::string, std::pair<float, specific_food_discount*>> a){return a.first==i.first;});
            if (menu_it == map_it->second->menu.end())   
                throw errors(error_message::NOT_FOUND);
            else
                i.second.first = menu_it->second.first;
        }
    }  
    for (auto i : map_it->second->reserves)
    {
        if (i.second->table_id == command_entered[3])
        {
            if(i.second->time_interval.first < stoi(command_entered[4]) && i.second->time_interval.second > stoi(command_entered[4]))
                throw errors(error_message::PERMISSION_DENIED);
            else if(i.second->time_interval.first < stoi(command_entered[5]) && i.second->time_interval.second > stoi(command_entered[5]))  
                throw errors(error_message::PERMISSION_DENIED);      
        }
    } 
    for (auto i : (*current_user->reserves))
    {
        if (i.second->time_interval.first < std::stoi(command_entered[4]) && i.second->time_interval.second > std::stoi(command_entered[4]))
            throw errors(error_message::PERMISSION_DENIED);
        if (i.second->time_interval.first < std::stoi(command_entered[5]) && i.second->time_interval.second > std::stoi(command_entered[5]))
            throw errors(error_message::PERMISSION_DENIED);    
    }
    if (stoi(map_it->second->working_time.first) > stoi(command_entered[4]) || stoi(map_it->second->working_time.second) < stoi(command_entered[4]))
        throw errors(error_message::PERMISSION_DENIED);
    if (stoi(map_it->second->working_time.first) > stoi(command_entered[5]) || stoi(map_it->second->working_time.second) < stoi(command_entered[5]))
        throw errors(error_message::PERMISSION_DENIED); 
    std::string respond;
    set_reserve(command_entered, foods, map_it, respond); 
}

void software::increase_budget(std::vector<std::string> &command_entered, std::string &respond)
{
    current_user->wallet += std::stof(command_entered[2]);
    respond = OK_VIEW;
}