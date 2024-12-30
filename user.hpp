#include "global.hpp"
#include "reserve.hpp"


class user{
    std::string username;
    std::string password;
    std::vector<user_reserve*>* reserves;
    std::string district;
    public:
        user(std::string, std::string);

    friend class software;    
};