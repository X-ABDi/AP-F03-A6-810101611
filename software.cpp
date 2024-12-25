#include "software.hpp"

void software::resturan_init (std::vector<std::string> rest_prop)
{
    resturan *new_resturan = new resturan;
    new_resturan->name = rest_prop[0];
    new_resturan->restrict = rest_prop[1];
    restricts.set_resturans(rest_prop[1], rest_prop[0]);
    new_resturan->set_menu(rest_prop[2]);
    new_resturan->working_time.first = stoi(rest_prop[3]);
    new_resturan->working_time.second = stoi(rest_prop[4]);
    new_resturan->set_tables(rest_prop[5]);
}

void software::restrict_init (std::vector<std::string> rest_prop)
{
    restrict *new_restrict = new restrict;
    new_restrict->set_neighbors(rest_prop);
}