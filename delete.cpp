#include "delete.hpp"

Delete::Delete(process &process_obj) : process (process_obj)
{
    // std::cout << "delete constructor" << std::endl;
}

std::string Delete::pro_delete (std::vector<std::string> &command_entered)
{
    if (!UTaste->logged_in())
        throw errors(error_message::PERMISSION_DENIED);
    std::string respond;
    if (command_entered[1] == sub_command_delete::RESERVE)
        pro_delete_reserve (command_entered, respond);
    return respond;    
}

void Delete::pro_delete_reserve (std::vector<std::string> &command_entered, std::string &respond)
{
    UTaste->delete_reserve(command_entered);
    respond = OK_VIEW;
}