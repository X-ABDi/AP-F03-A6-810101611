#ifndef __PUT__
#define __PUT__

#include "global.hpp"
#include "process.hpp"

class Put : protected process
{
    public:
        Put(process &process_obj);
        std::string pro_put (std::vector<std::string> &command_entered);
        void pro_put_district(std::string command_entered, std::string &respond);
};

#endif