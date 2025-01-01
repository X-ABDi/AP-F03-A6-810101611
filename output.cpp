#include "output.hpp"

output::output (const std::string respond)
{
    std::cout << respond;
}

output::output(){}

void output::set_respond(std::string message)
{
    respond = message;
}

void output::monitor ()
{
    std::cout << respond << std::endl;
}