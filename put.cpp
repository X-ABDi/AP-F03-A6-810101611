#include "put.hpp"

Put::Put(process &process_obj) : process(process_obj)
{
    std::cout << "put constructor" << std::endl;
}

std::string Put::pro_put (std::vector<std::string> &command_entered)
{
    if (!UTaste->logged_in())
        throw errors(error_message::PERMISSION_DENIED);
    std::string respond;
    if (command_entered[1] == sub_command_put::MY_DISTRICT)
        pro_put_district(command_entered[2], respond);
    return respond;
}

void Put::pro_put_district(std::string district_name, std::string &respond)
{
    UTaste->set_district(district_name);
    respond = OK;
}