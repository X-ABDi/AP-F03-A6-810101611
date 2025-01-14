#include "user.hpp"

user::user(std::string username_, std::string password_)
{
    username = username_;
    password = password_;
    reserves = new std::map<std::string, user_reserve*>;
    district = "";
    wallet = 0;
    logged_in = true;
}

user::user()
{
    reserves = new std::map<std::string, user_reserve*>;
    district = "";
    wallet = 0;
    logged_in = false;
}

user::~user()
{
    delete reserves;
}