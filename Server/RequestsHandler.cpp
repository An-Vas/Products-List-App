#include "RequestsHandler.h"

nlohmann::json RequestsHandler::handleRequest(Request r){
    if (r.type == "user") loginRequest(r);
    if (r.type == "product") addProductRequest(r);
    if (r.type == "clear") clearListRequest(r);

    r.list = storage.getAllProducts(r.userId);
    return JsonParser::RequestToJson(r);

}

void RequestsHandler::loginRequest(Request r){
    std::string userId = r.userId;

    storage.isUserInStorage(userId);
    if (!storage.isUserInStorage(userId))
        storage.addUserInStorage(userId);
}

void RequestsHandler::addProductRequest(Request r){
    std::string userId = r.userId;
    if (storage.isUserInStorage(userId))
        storage.addUProductToUser(userId, r.list.back());
}

void RequestsHandler::clearListRequest(Request r){
    std::string userId = r.userId;
    if (storage.isUserInStorage(userId))
        storage.clearUserProductList(userId);
}

