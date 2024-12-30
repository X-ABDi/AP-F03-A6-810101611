#include "global.hpp"
#include "process.hpp"

class Delete : protected process
{
    public:
        std::string pro_delete (std::vector<std::string> &command_entered);
};