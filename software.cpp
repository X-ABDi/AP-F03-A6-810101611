#include "software.hpp"

void software::resturan_init (std::vector<std::string> rest_prop)
{
    resturan *new_resturan = new resturan;
    new_resturan->name = rest_prop[0];
    new_resturan->restrict = rest_prop[1];
    districts.set_resturans(rest_prop[1], rest_prop[0]);
    new_resturan->set_menu(rest_prop[2]);
    new_resturan->working_time.first = stoi(rest_prop[3]);
    new_resturan->working_time.second = stoi(rest_prop[4]);
    new_resturan->set_tables(rest_prop[5]);
}

void software::district_init (std::vector<std::string> rest_prop)
{
    district *new_restrict = new district;
    new_restrict->set_neighbors(rest_prop);
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