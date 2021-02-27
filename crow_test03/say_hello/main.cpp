#include "crow_all.h"

using namespace std;
using namespace crow;

void SendFile(response &res, string contentType, string filename)
{
  ifstream in(("../public/" + filename), ifstream::in);
  if (in)
  {
    ostringstream contents;
    contents << in.rdbuf();
    in.close();
    res.set_header("Content-Type", contentType);
    res.write(contents.str());
  }
  else
  {
    res.write("Not found");
  }
  res.end();
}
void sendJavaScript(response &res, string filename)
{
  SendFile(res, "text/javascript", "js/" + filename);
}
void sendHTML(response &res, string filename)
{
  SendFile(res, "text/html", filename + ".html");
}
void sendPNG(response &res, string filename)
{
  SendFile(res, "image/png", "image/" + filename);
}
void sendStyle(response &res, string filename)
{
  SendFile(res, "text/css", "style/" + filename);
}

int main(int argc, char *argv[])
{
  crow::SimpleApp app;
  crow::mustache::set_base("./public/");
  CROW_ROUTE(app, "/")
  ([](const request &req, response &res) {
    sendHTML(res, "index");
  });

  CROW_ROUTE(app, "/<string>")
  ([](const request &req, response &res, string name = NULL) {
    sendHTML(res, "index");
  });

  CROW_ROUTE(app, "/js/<string>")
  ([](const request &req, response &res, string filename) {
    sendJavaScript(res, filename);
  });

  CROW_ROUTE(app, "/image/<string>")
  ([](const request &req, response &res, string filename) {
    sendPNG(res, filename);
  });

  CROW_ROUTE(app, "/style/<string>")
  ([](const request &req, response &res, string filename) {
    sendStyle(res, filename);
  });

  char *port = getenv("PORT");
  uint16_t iPort = static_cast<uint16_t>(port != NULL) ? stoi(port) : 8080;
  cout << "PORT = " << port << endl;
  app.port(iPort).multithreaded().run();
}
