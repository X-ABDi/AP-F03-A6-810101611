#include "global.hpp"
#include "process.hpp"

class Get : protected process
{
    public:
        std::string pro_get (std::vector<std::string> &command_entered);
};
