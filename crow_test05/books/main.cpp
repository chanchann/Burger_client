#include "include/crow_all.h"
#include "include/HTTPRequest.hpp"
#include "jsoncons/json.hpp"
#include <string>
#include <vector>

using namespace std;
using namespace crow;
using namespace jsoncons;
using namespace crow::mustache;

void getView(response &res, const string &filename, context& x)
{
  res.set_header("Content-Type", "text/html");
  auto text = load("../../public/templates/" + filename + ".html").render(x);
  res.write(text);
  res.end();
}

void sendFile(response &res, string filename, string contentType)
{
  ifstream in("../public/" + filename, ifstream::in);
  if(in)
  {
    ostringstream contents;
    contents << in.rdbuf();
    in.close();
    res.set_header("Content-Type", contentType);
    res.write(contents.str());
  }
  else
  {
    res.code = 404;
    res.write("Not found!");
  }
  res.end();
}

void sendHtml(response &res, string filename)
{
  sendFile(res, filename + ".html", "text/html");
}

void sendImage(response &res, string filename)
{
  sendFile(res, "images/" + filename, "image/jpeg");
}

void sendScript(response &res, string filename)
{
  sendFile(res, "scripts/" + filename, "text/javascript");
}

void sendStyle(response &res, string filename)
{
  sendFile(res, "styles/" + filename, "text/css");
}

void notFound(response &res, const string &message)
{
  res.code = 404;
  res.write(message + ": Not Found");
  res.end();
}

int main(int argc, char* argv[])
{
  crow::SimpleApp app;
  CROW_ROUTE(app, "/styles/<string>")
    ([](const request &req, response &res, string filename)
      {
        sendStyle(res, filename);
      }
    );

  CROW_ROUTE(app, "/scripts/<string>")
    ([](const request &req, response &res, string filename)
      {
        sendScript(res, filename);
      }
    );

  CROW_ROUTE(app, "/images/<string>")
  ([](const request &req, response &res, string filename)
    {
      sendImage(res, filename);
    }
  );

  CROW_ROUTE(app, "/q")
  ([](const request& req, response& res){
    auto category = req.url_params.get("category");
    ostringstream os1;
    /*
     YOU CAN GET YOUR API KEY FROM HERE : 
     https://developer.nytimes.com/docs/books-product/1/overview
    */
    const string api_key = "YOUR API KEY";
    const string fixed_path = "http://api.nytimes.com/svc/books/v3/lists/current/";
    if(category != "")
    {
      os1 << fixed_path << category << ".json?api-key=" << api_key;
    }
    else
    {
      os1 << fixed_path << "hardcover-nonfiction.json?api-key=" << api_key;
    }
    http::Request request(os1.str());
    const http::Response response = request.send("GET");

    jsoncons::json json_response;
    json_response = jsoncons::json::parse(string(response.body.begin(), response.body.end()));

    if(json_response["status"].as<string>() != "OK")
    {
      sendHtml(res, "error");
    }

    vector<crow::json::rvalue> books;
    books.reserve(json_response["num_results"].as<int>());
    int i = 0;
    for(auto& book : json_response["results"]["books"].array_range())
    {
      books.push_back(json::load(json_response["results"]["books"][i++].as<string>()));
    }
    vector<crow::json::rvalue> list_info;
    ostringstream os2;
    os2 << "{\"list_name\": " << json_response["results"]["list_name"] << "}";
    list_info.push_back(json::load(os2.str()));

    crow::json::wvalue dto;
    dto["books"] = books;
    dto["list_info"] = list_info;
    getView(res, "response", dto);
  });

  CROW_ROUTE(app, "/about-this-website")
  ([](const request& req, response& res)
  {
    sendHtml(res, "about-this-website");
  });

  CROW_ROUTE(app, "/about-the-developer")
  ([](const request& req, response& res)
  {
    sendHtml(res, "about-the-developer");
  });

  CROW_ROUTE(app, "/contact-the-developer")
  ([](const request& req, response& res)
  {
    sendHtml(res, "contact-the-developer");
  });

  CROW_ROUTE(app, "/")
  ([](const request& req, response& res)
  {
    sendHtml(res, "index");
  });

  char* port = getenv("PORT");
  uint16_t iPort = static_cast<uint16_t>(port != NULL ? stoi(port): 18080);
  cout << "PORT = " << iPort << "\n";
  app.port(iPort).multithreaded().run();
}
