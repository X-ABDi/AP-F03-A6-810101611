#include <iostream>
#include "global.hpp"

class errors : public std::exception
{
    std::string message;
    public:
        errors(const std::string msg);
        virtual const char* what();
        void printError();
};