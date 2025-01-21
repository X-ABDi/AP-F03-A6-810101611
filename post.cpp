#include "post.hpp"

Post::Post(process &process_obj) : process(process_obj)
{
    // std::cout << "post constructor" << std::endl;
}

void Post::pro_post_signup(std::vector<std::string> &command_entered, std::string &respond)
{
    if (command_entered[2] == EMPTY_STRING_VIEW || command_entered[3] == EMPTY_STRING_VIEW)
        throw errors(error_message::BAD_REQUEST);
    UTaste->signup(command_entered);
    respond = OK_VIEW;
}

void Post::pro_post_login(std::vector<std::string> &command_entered, std::string &respond)
{
    if (command_entered[2] == EMPTY_STRING_VIEW || command_entered[3] == EMPTY_STRING_VIEW)
        throw errors(error_message::BAD_REQUEST);
    UTaste->login(command_entered);
    respond = OK_VIEW;
}

void Post::pro_post_logout(std::vector<std::string> &command_entered, std::string &respond)
{
    if (!UTaste->logged_in())
        throw errors(error_message::PERMISSION_DENIED);  
    UTaste->logout();
    respond = OK_VIEW;
}

void Post::pro_post_reserve(std::vector<std::string> &command_entered, std::string &respond)
{
    for (int i = 2; i<command_entered.size()-1; i++)
        if (command_entered[i] == EMPTY_STRING_VIEW)
            throw errors(error_message::BAD_REQUEST);
    if (!UTaste->logged_in())
        throw errors(error_message::PERMISSION_DENIED);
    UTaste->reserve(command_entered, respond);
}

void Post::pro_post_increase_budget(std::vector<std::string> &command_entered, std::string &respond)
{
    if (!UTaste->logged_in())
        throw errors(error_message::PERMISSION_DENIED);
    UTaste->increase_budget(command_entered, respond);
}

std::string Post::pro_post (std::vector<std::string> &command_entered)
{
    std::string respond;
    if (command_entered[1] == sub_command_post::SIGNUP)
        pro_post_signup(command_entered, respond);
    else if (command_entered[1] == sub_command_post::LOGIN)
        pro_post_login(command_entered, respond);
    else if (command_entered[1] == sub_command_post::LOGOUT)
        pro_post_logout(command_entered, respond);
    else if (command_entered[1] == sub_command_post::RESERVE)
        pro_post_reserve(command_entered, respond);
    else if (command_entered[1] == sub_command_post::INCREASE_BUDGET) 
        pro_post_increase_budget(command_entered, respond);   
    return respond;                
}

