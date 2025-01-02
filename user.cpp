#include "user.hpp"

user::user(std::string username_, std::string password_)
{
    username = username_;
    password = password_;
    reserves = new std::map<std::string, user_reserve*>;
    district = "";
    wallet = 0;
}

user::user()
{
    reserves = new std::map<std::string, user_reserve*>;
    district = "";
    wallet = 0;
}

user::~user()
{
    delete reserves;
}