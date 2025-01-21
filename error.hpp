#ifndef __ERROR__
#define __ERROR__

#include <iostream>
#include "global.hpp"

class errors : public std::exception
{
    public:
        errors(const std::string_view msg);
        void printError();
        std::string_view message;
};

#endif