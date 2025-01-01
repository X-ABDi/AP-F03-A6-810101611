#ifndef __POST__
#define __POST__

#include "global.hpp"
#include "process.hpp"

class Post : protected process
{
    public:
        std::string pro_post (std::vector<std::string> &command_entered);
        std::string pro_post_signup(std::vector<std::string> &command_entered);
        std::string pro_post_login(std::vector<std::string> &command_entered);
        std::string pro_post_logout(std::vector<std::string> &command_entered);
        std::string pro_post_reserve(std::vector<std::string> &command_entered);
};

#endif