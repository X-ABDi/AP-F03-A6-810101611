#include "global.hpp"
#include "process.hpp"

class Get : protected process
{
    public:
        std::string pro_get (std::vector<std::string> &command_entered);
        std::string pro_get_districts(std::vector<std::string> &command_entered);
        std::string pro_get_resturans(std::vector<std::string> &command_entered);
        std::string pro_get_restdetail(std::vector<std::string> &command_entered);
        std::string pro_get_reserves(std::vector<std::string> &command_entered);
};
