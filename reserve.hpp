#include "global.hpp"

struct  reserves
{
    int table_id;
    int reserve_id;
    std::pair<int, int> time_interval;
    std::vector<std::pair<std::string, int>> foods;
};

struct rest_reserve : reserves
{
    std::string username;
};

struct user_reserve :reserves
{
    std::string resturan_name;
};
