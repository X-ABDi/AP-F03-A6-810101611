#include "post.hpp"

std::string Post::pro_post_signup(std::vector<std::string> &command_entered)
{
    std::cout << "pro post signup" << std::endl;
    UTaste.signup(command_entered);
    return OK;
}

std::string Post::pro_post_login(std::vector<std::string> &command_entered)
{
    UTaste.login(command_entered);
    return OK;
}

std::string Post::pro_post_logout(std::vector<std::string> &command_entered)
{
    if (!UTaste.logged_in())
        throw errors(error_message::PERMISSION_DENIED);
    UTaste.logout();
    return OK;
}

std::string Post::pro_post_reserve(std::vector<std::string> &command_entered)
{
    std::string respond;
    if (!UTaste.logged_in())
        throw errors(error_message::PERMISSION_DENIED);
    respond = UTaste.reserve(command_entered);
    return respond;
}

std::string Post::pro_post_increase_budget(std::vector<std::string> &command_entered)
{
    std::string respond;
    if (!UTaste.logged_in())
        throw errors(error_message::PERMISSION_DENIED);
    respond = UTaste.increase_budget(command_entered);
    return respond;    
}

std::string Post::pro_post (std::vector<std::string> &command_entered)
{
    std::string respond;
    std::cout << command_entered[1] << std::endl;
    if (command_entered[1] == sub_command_post::SIGNUP)
        respond = pro_post_signup(command_entered);
    else if (command_entered[1] == sub_command_post::LOGIN)
        respond = pro_post_login(command_entered);
    else if (command_entered[1] == sub_command_post::LOGOUT)
        respond = pro_post_logout(command_entered);
    else if (command_entered[1] == sub_command_post::RESERVE)
        respond = pro_post_reserve(command_entered);
    else if (command_entered[1] == sub_command_post::INCREASE_BUDGET) 
        respond = pro_post_increase_budget(command_entered);   
    return respond;                
}

