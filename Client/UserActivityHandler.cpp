
#include "UserActivityHandler.h"
#include "WindowSetup.h"
#include "Request.h"
#include "JsonParser.h"

#include <memory>


UserActivityHandler::UserActivityHandler(){

    client = std::make_shared<ClientQt5>(this);
    client->setHandler(this);
}


void UserActivityHandler::handleAddProduct(std::string name, int amount, std::string userId){
    Request r;
    r.type = "product";
    r.userId = userId;
    std::list<ProductListItem> list;
    list.push_back(ProductListItem(name, amount));
    r.list = list;

    nlohmann::json j = JsonParser::RequestToJson(r);
    std::string req = to_string(j);
    client->send(QString::fromStdString(req));

};

void UserActivityHandler::handleClearList (std::string userId){

    Request r;
    r.type = "clear";
    r.userId = userId;
    nlohmann::json j = JsonParser::RequestToJson(r);
    std::string req = to_string(j);
    client->send(QString::fromStdString(req));

};



void UserActivityHandler::acceptMessage(const QString& message){
    std::cout<<"Received: " << message.toStdString() << "\n";
    Request r = JsonParser::JsonToRequest(nlohmann::json::parse(message.toStdString()));
    std::cout << r.userId << " " << r.type << "\n";


    windowSetup->acceptServerReaponce(r);
}

void UserActivityHandler::userConnect(std::string userId){
    Request r;
    r.type = "user";
    r.userId = userId;
    nlohmann::json j = JsonParser::RequestToJson(r);
    std::string req = to_string(j);
    client->send(QString::fromStdString(req));


}

void UserActivityHandler::setWindowSetup(WindowSetup * ws){
    windowSetup = ws;
}
