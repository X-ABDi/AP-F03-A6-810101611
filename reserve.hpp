#include "global.hpp"

struct  reserves
{
    std::string table_id;
    std::string reserve_id;
    std::pair<std::string, std::string> time_interval;
    std::vector<std::pair<std::string, std::string>> foods;
};

struct rest_reserve : reserves
{
    std::string username;
};

struct user_reserve :reserves
{
    std::string resturan_name;
};
