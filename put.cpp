#include "put.hpp"

std::string Put::pro_put (std::vector<std::string> &command_entered)
{
    if (!UTaste.logged_in())
        throw errors(error_message::PERMISSION_DENIED);
    std::string respond;
    if (command_entered[1] == sub_command_put::MY_DISTRICT)
        respond = pro_put_district(command_entered[2]);
    return respond;
}

std::string Put::pro_put_district(std::string district_name)
{
    std::string respond;
    UTaste.set_district(district_name);
    return OK;
}