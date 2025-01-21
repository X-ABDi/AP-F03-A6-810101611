#ifndef HANDLERS_HPP_INCLUDE
#define HANDLERS_HPP_INCLUDE

#include <map>
#include <string>
#include "../../global.hpp"
#include "../../interface.hpp"
#include "server.hpp"
#include "../../error.hpp"

class RandomNumberHandler : public RequestHandler {
public:
    Response* callback(Request*, interface &manager) override;
};

class UploadHandler : public RequestHandler {
public:
    Response* callback(Request*, interface &manager) override;
};

class ColorHandler : public TemplateHandler {
public:
    ColorHandler(const std::string& filePath);
    std::map<std::string, std::string> handle(Request* req) override;
};

class LoginHandler : public RequestHandler {
public:
    Response* callback(Request*, interface &manager) override;
};

class SignupHandler : public RequestHandler {
    Response* callback(Request*, interface &manager) override;
};

class ReserveHandler : public RequestHandler {
    Response* callback(Request*, interface &manager) override;
};

class restaurantDetailHandler : public RequestHandler {
    Response* callback(Request*, interface &manager) override;
};

class ReservesHandler : public RequestHandler {
    Response* callback(Request*, interface &manager) override;
};

#endif // HANDLERS_HPP_INCLUDE
