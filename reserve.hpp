#ifndef __RESERVE__
#define __RESERVE__

#include "global.hpp"

struct  reserves
{
    std::string table_id;
    int reserve_id;
    std::pair<int, int> time_interval;
    std::map<std::string, std::pair<int, int>> foods;
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