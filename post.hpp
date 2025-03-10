#ifndef __POST__
#define __POST__

#include "global.hpp"
#include "process.hpp"

class Post : protected process
{
    public:
        Post(process &process_obj);
        std::string pro_post (std::vector<std::string> &command_entered);
        void pro_post_signup(std::vector<std::string> &command_entered, std::string &respond);
        void pro_post_login(std::vector<std::string> &command_entered, std::string &respond);
        void pro_post_logout(std::vector<std::string> &command_entered, std::string &respond);
        void pro_post_reserve(std::vector<std::string> &command_entered, std::string &respond);
        void pro_post_increase_budget(std::vector<std::string> &command_entered, std::string &respond);
};

#endif