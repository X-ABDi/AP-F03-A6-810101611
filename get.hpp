#ifndef __GET__
#define __GET__

#include "global.hpp"
#include "process.hpp"

class Get : protected process
{
    public:
        Get(process &process_obj);
        std::string pro_get (std::vector<std::string> &command_entered);
        void pro_get_districts(std::vector<std::string> &command_entered, std::string &respond);
        void pro_get_resturans(std::vector<std::string> &command_entered, std::string &respond);
        void pro_get_restdetail(std::vector<std::string> &command_entered, std::string &respond);
        void pro_get_reserves(std::vector<std::string> &command_entered, std::string &respond);
        void pro_get_budget(std::vector<std::string> &command_entered, std::string &respond);
};

#endif