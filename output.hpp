#ifndef __OUTPUT__
#define __OUTPUT__

#include "global.hpp"

class output
{
    std::string respond;
    public:
    output();
    output(const std::string respond);
    void set_respond(std::string);
    void monitor();
};

#endif