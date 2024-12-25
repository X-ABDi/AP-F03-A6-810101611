#include "global.hpp"
#include "process.hpp"

class Put : protected process
{
    public:
        std::string pro_put (std::vector<std::string> &command_entered);
};