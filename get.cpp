#include "get.hpp"

Get::Get(process &process_obj) : process(process_obj)
{
    std::cout << "get constructor" << std::endl;
}

std::string Get::pro_get (std::vector<std::string> &command_entered)
{
    std::string respond;
    if (!UTaste->logged_in())
        throw errors(error_message::PERMISSION_DENIED);
    if (command_entered[1] == sub_command_get::DISTRICTS)
        respond = pro_get_districts(command_entered);
    else if (command_entered[1] == sub_command_get::RESTAURANTS)
        respond = pro_get_resturans(command_entered);
    else if (command_entered[1] == sub_command_get::RESTAURANT_DETAIL)
        respond = pro_get_restdetail(command_entered); 
    else if (command_entered[1] == sub_command_get::RESERVES)
        respond = pro_get_reserves(command_entered);
    else if (command_entered[1] == sub_command_get::SHOW_BUDGET)
        respond = pro_get_budget(command_entered);    
    return respond;
}

std::string Get::pro_get_districts(std::vector<std::string> &command_entered)
{
    std::string respond;
    if (command_entered.size() == 3)
        respond = UTaste->get_district(command_entered[2]);
    else if (command_entered.size() == 2)
        respond = UTaste->get_all_districts();    
    return respond;    
}

std::string Get::pro_get_resturans(std::vector<std::string> &command_entered)
{
    std::string respond;
    if (command_entered.size() == 3)
        respond = UTaste->get_resturans(command_entered[2]); 
    else if (command_entered.size() == 2)
        respond = UTaste->get_resturans("");    
    return respond;       
}

std::string Get::pro_get_restdetail(std::vector<std::string> &command_entered)
{
    std::string respond;
    respond = UTaste->get_resturan_detail(command_entered[2]);
    return respond;
}

std::string Get::pro_get_reserves(std::vector<std::string> &command_entered)
{
    std::string respond;
    respond = UTaste->get_reserves(command_entered);
    return respond;
}

std::string Get::pro_get_budget(std::vector<std::string> &command_entered)
{
    std::string respond;
    respond = UTaste->get_budget();
    return respond;
}