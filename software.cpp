#include "software.hpp"

software::software()
{
    all_resturans = new std::map<std::string, resturan*>;
    all_users = new std::map<std::string, user*>;
}

software::~software()
{
    delete all_resturans;
    delete all_users;
}

void software::resturan_init (std::vector<std::string> rest_prop)
{
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

void software::district_init (std::vector<std::string> rest_prop)
{
    district *new_district = new district;
    new_district->set_neighbors(rest_prop);
}

std::string software::get_district(std::string district_name)
{
    std::string respond;
    respond = districts.get_district(district_name);
    return respond;
}

std::string software::get_all_districts()
{
    std::string respond;
    if (districts.district_neighbors.size() == 0)
        throw errors(error_message::EMPTY);
    respond = districts.get_all_districts();  
    return respond;
}

std::string software::get_resturans(std::string food_name)
{
    std::string respond;
    if (current_user->district == "")
        throw errors(error_message::NOT_FOUND);
    if ((*all_resturans).size() == 0)
        throw errors(error_message::EMPTY);
    std::string user_district = current_user->district;    
    respond = districts.get_resturans(user_district, food_name);  
    if (respond == "")
        throw errors(error_message::EMPTY);
    return respond;    
}