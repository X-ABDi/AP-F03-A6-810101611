#include "error.hpp"

errors::errors(const std::string msg)
{
    message = msg;
}

const char* errors::what()
{
    return message.c_str();
}

void errors::printError()
{
    std::cout << message << std::endl;
}

// void errors::notFound()
// {
//     throw std::runtime_error(NOT_FOUND);
// }

// void errors::badRequest()
// {
//     throw std::runtime_error(BAD_REQUEST);
// }

// void errors::permissionDenied()
// {
//     throw std::runtime_error(PERMISSION_DENIED);
// }

// void errors::stringCorrupt()
// {
//     throw std::runtime_error(STRING_CORRUPTED);
// }