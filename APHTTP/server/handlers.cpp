#include "handlers.hpp"

#include <cstdlib>
#include <iostream>

Response* RandomNumberHandler::callback(Request* req, interface &manager) {
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");

    std::string randomNumber = std::to_string(std::rand() % 10 + 1);
    std::string body;

    body += "<!DOCTYPE html>";
    body += "<html lang=\"en\">";

    body += "<head>";
    body += "  <title>Random Number Page</title>";
    body += "</head>";

    body += "<body style=\"text-align: center;\">";
    body += "  <h1>AP HTTP</h1>";
    body += "  <p>A random number in [1, 10] is: " + randomNumber + "</p>";
    body += "  <p>SessionId: " + req->getSessionId() + "</p>";
    body += "</body>";

    body += "</html>";
    res->setBody(body);
    return res;
}

Response* UploadHandler::callback(Request* req, interface &manager) {
    std::string name = req->getBodyParam("file_name");
    std::string file = req->getBodyParam("file");
    utils::writeToFile(file, name);
    Response* res = Response::redirect("/");
    return res;
}

ColorHandler::ColorHandler(const std::string& filePath)
    : TemplateHandler(filePath) {}

std::map<std::string, std::string> ColorHandler::handle(Request* req) {
    std::string newName = "I am " + req->getQueryParam("name");
    std::map<std::string, std::string> context;
    context["name"] = newName;
    context["color"] = req->getQueryParam("color");
    return context;
}

Response* LoginHandler::callback(Request* req, interface &manager) {
    std::string username = req->getBodyParam("username");
    std::string password = req->getBodyParam("password");
    if (username == "root") {
        throw Server::Exception("Remote root access has been disabled.");
    }
    std::vector<std::string> commands = {std::string(main_command::POST), std::string(sub_command_post::LOGIN),username, password};
    Response* res = Response::redirect("/");
    std::string body;
    try{
    body = manager.run(commands);
    }
    catch (errors &e){
        res->setCode(e.message);
        res->setPhrase(e.message);
    }
    res->setBody(body);
    res->setSessionId("SID");
    return res;
}

Response* SignupHandler::callback(Request* req, interface &manager) {
    std::string username = req->getBodyParam("username");
    std::string password = req->getBodyParam("password");
    std::vector<std::string> commands = {std::string(main_command::POST), std::string(sub_command_post::SIGNUP),username, password};
    Response* res = Response::redirect("/");
    std::string body;
    try{
    body = manager.run(commands);
    }
    catch (errors &e){
        res->setCode(e.message);
        res->setPhrase(e.message);
    }
    res->setBody(body);
    res->setSessionId("SID");
    return res;
}

Response* ReserveHandler::callback(Request* req, interface &manager) {
    std::string name = req->getBodyParam("name");
    std::string table = req->getBodyParam("table");
    std::string start = req->getBodyParam("start");
    std::string end = req->getBodyParam("end");
    std::string foods = req->getBodyParam("food");
    std::vector<std::string> commands = {std::string(main_command::POST), std::string(sub_command_post::RESERVE), name,
                                            table, start, end, foods};
    Response* res = new Response(); 
    std::string body;
    try {
        body = manager.run(commands);
    }                                
    catch (errors &e) {
        res->setCode(e.message);
        res->setPhrase(e.message);
    }  
    res->setBody(body);
    return res;    
}

