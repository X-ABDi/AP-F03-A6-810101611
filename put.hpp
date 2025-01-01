#ifndef __PUT__
#define __PUT__

#include "global.hpp"
#include "process.hpp"

class Put : protected process
{
    public:
        std::string pro_put (std::vector<std::string> &command_entered);
        std::string pro_put_district(std::string command_entered);
};

#endif