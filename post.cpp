#include "post.hpp"

std::string Post::pro_post_signup(std::vector<std::string> &command_entered)
{
    UTaste.signup(command_entered);
    return OK;
}

std::string Post::pro_post_login(std::vector<std::string> &command_entered)
{
    
}

std::string Post::pro_post_logout(std::vector<std::string> &command_entered)
{
    if (!UTaste.logged_in())
        throw errors(error_message::PERMISSION_DENIED);

}

std::string Post::pro_post_reserve(std::vector<std::string> &command_entered)
{
    if (!UTaste.logged_in())
        throw errors(error_message::PERMISSION_DENIED);

}

std::string Post::pro_post (std::vector<std::string> &command_entered)
{
    std::string respond;
    if (command_entered[1] == sub_command_post::SIGNUP)
        respond = pro_post_signup(command_entered);
    else if (command_entered[1] == sub_command_post::LOGIN)
        respond = pro_post_login(command_entered);
    else if (command_entered[1] == sub_command_post::LOGOUT)
        respond = pro_post_logout(command_entered);
    else if (command_entered[1] == sub_command_post::RESERVE)
        respond = pro_post_reserve(command_entered);
    return respond;                
}

