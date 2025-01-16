#ifndef __ERROR__
#define __ERROR__

#include <iostream>
#include "global.hpp"

class errors : public std::exception
{
    std::string_view message;
    public:
        errors(const std::string_view msg);
        // virtual const char* what();
        void printError();
};

#endif