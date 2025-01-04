#ifndef __USER__
#define __USER__

#include "global.hpp"
#include "reserve.hpp"

class user{
    std::string username;
    std::string password;
    std::map<std::string, user_reserve*>* reserves;
    std::string district;
    float wallet;
    bool logged_in;
    public:
        user(std::string, std::string);
        user();
        ~user();
    friend class software;    
};

#endif