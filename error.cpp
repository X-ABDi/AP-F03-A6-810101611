#include "error.hpp"

errors::errors(const std::string msg)
{
    message = msg;
}

// const char* errors::what()
// {
//     return message.c_str();
// }

void errors::printError()
{
    std::cout << message << std::endl;
}