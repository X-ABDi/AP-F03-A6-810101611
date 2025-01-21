#include "main.hpp"

void mapServerPaths(Server& server) {
    server.setNotFoundErrPage("../APHTTP/static/404.html");
    server.get("/", new ShowPage("../APHTTP/static/home.html"));
    server.get("/home.png", new ShowImage("../APHTTP/static/home.png"));
    server.get("/signup", new ShowPage("../APHTTP/static/signup.html"));
    server.post("/signup", new SignupHandler());
    server.get("/login", new ShowPage("../APHTTP/static/logincss.html"));
    server.post("/login", new LoginHandler());
    server.get("/reserve", new ShowPage("../APHTTP/static/reserve.html"));
    server.post("/reserve", new ReserveHandler());
    server.get("/restaurant_detail", new ShowPage("../APHTTP/static/restaurant_detail.html"));
    server.post("/restaurant_detail", new restaurantDetailHandler());
    server.get("/reserves", new ShowPage("../APHTTP/static/reserves.html"));
    server.post("/reserves", new ReservesHandler());
}

int main (int argc, char *argv[])
{
    interface manager;
    manager.initi(argv);
    int port = std::stoi(argv[1]);
    Server server(port);
    mapServerPaths(server);
    std::cout << "Server running on port: " << port << std::endl;
    server.run(manager);
}