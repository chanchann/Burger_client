#include "crow_all.h"

int main() {
    crow::SimpleApp app;
    crow::mustache::set_base("../frontend");
    CROW_ROUTE(app, "/")([](){
        crow::mustache::context ctx;
        return crow::mustache::load("index.html").render();
    });

    app.port(18080).multithreaded().run();
}

