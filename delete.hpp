#ifndef __DELETE__
#define __DELETE__

#include "global.hpp"
#include "process.hpp"

class Delete : protected process
{
    public:
        std::string pro_delete (std::vector<std::string> &command_entered);
        std::string pro_delete_reserve (std::vector<std::string> &command_entered);
};

#endif