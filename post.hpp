#include "global.hpp"
#include "process.hpp"

class Post : protected process
{
    public:
        std::string pro_post (std::vector<std::string> &command_entered);
};