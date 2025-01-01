#ifndef __RESERVE__
#define __RESERVE__

#include "global.hpp"

struct  reserves
{
    std::string table_id;
    std::string reserve_id;
    std::pair<std::string, std::string> time_interval;
    std::map<std::string, std::pair<std::string, int>> foods;
};

struct rest_reserve : reserves
{
    std::string username;
    friend class software;
};

struct user_reserve :reserves
{
    std::string resturan_name;
    friend class software;
};

#endif