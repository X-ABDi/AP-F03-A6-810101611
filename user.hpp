#include "global.hpp"
#include "reserve.hpp"


class user{
    std::string username;
    std::string password;
    std::map<std::string, user_reserve*>* reserves;
    std::string district;
    bool logged_in;
    public:
        user(std::string, std::string);

    friend class software;    
};