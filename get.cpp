#include "get.hpp"
// #include "../APHTTP/utils/response.hpp"

Get::Get(process &process_obj) : process(process_obj)
{
    // std::cout << "get constructor" << std::endl;
}

std::string Get::pro_get (std::vector<std::string> &command_entered)
{
    std::string respond;
    if (!UTaste->logged_in())
        throw errors(error_message::PERMISSION_DENIED);
    if (command_entered[1] == sub_command_get::DISTRICTS)
        pro_get_districts(command_entered, respond);
    else if (command_entered[1] == sub_command_get::RESTAURANTS)
        pro_get_resturans(command_entered, respond);
    else if (command_entered[1] == sub_command_get::RESTAURANT_DETAIL)
        pro_get_restdetail(command_entered, respond); 
    else if (command_entered[1] == sub_command_get::RESERVES)
        pro_get_reserves(command_entered, respond);
    else if (command_entered[1] == sub_command_get::SHOW_BUDGET)
        pro_get_budget(command_entered, respond);    
    return respond;
}

void Get::pro_get_districts(std::vector<std::string> &command_entered, std::string &respond)
{
    if (command_entered[2] != EMPTY_STRING_VIEW)
        UTaste->get_district(command_entered[2], respond);
    else
        UTaste->get_all_districts(respond);    
}

void Get::pro_get_resturans(std::vector<std::string> &command_entered, std::string &respond)
{
    if (command_entered[2] != EMPTY_STRING_VIEW)
        UTaste->get_resturans(command_entered[2], respond); 
    else
        UTaste->get_resturans(EMPTY_STRING, respond);    
}

void Get::pro_get_restdetail(std::vector<std::string> &command_entered, std::string &respond)
{
    if (command_entered[2] == EMPTY_STRING_VIEW)
        throw errors(error_message::BAD_REQUEST);
    UTaste->get_resturan_detail(command_entered[2], respond);
}

void Get::pro_get_reserves(std::vector<std::string> &command_entered, std::string &respond)
{
    UTaste->get_reserves(command_entered, respond);
}

void Get::pro_get_budget(std::vector<std::string> &command_entered, std::string &respond)
{
    UTaste->get_budget(respond);
}