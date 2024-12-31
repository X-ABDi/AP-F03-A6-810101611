#include "get.hpp"

std::string Get::pro_get (std::vector<std::string> &command_entered)
{
    if (command_entered[1] == sub_command_get::DISTRICTS)
        pro_get_districts(command_entered);
    else if (command_entered[1] == sub_command_get::RESTAURANTS)
        pro_get_resturans(command_entered);
    else if (command_entered[1] == sub_command_get::RESTAURANT_DETAIL)
        pro_get_restdetail(command_entered);    
}

std::string Get::pro_get_districts(std::vector<std::string> &command_entered)
{
    std::string respond;
    if (command_entered.size() == 3)
        respond = UTaste.get_district(command_entered[2]);
    else if (command_entered.size() == 2)
        respond = UTaste.get_all_districts();    
    return respond;    
}

std::string Get::pro_get_resturans(std::vector<std::string> &command_entered)
{
    std::string respond;
    if (command_entered.size() == 3)
        respond = UTaste.get_resturans(command_entered[2]); 
    else if (command_entered.size() == 2)
        respond = UTaste.get_resturans("");    
    return respond;       
}

std::string Get::pro_get_restdetail(std::vector<std::string> &command_entered)
{
    std::string respond;
    UTaste.get_resturan_detail(command_entered[2]);
}