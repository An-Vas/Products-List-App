#ifndef SERVER_REQUESTSHANDLER_H
#define SERVER_REQUESTSHANDLER_H

#include <nlohmann/json.hpp>
#include "Storage.h"
#include "Request.h"
#include "JsonParser.h"

class RequestsHandler {

    void loginRequest(Request r);
    void addProductRequest(Request r);
    void clearListRequest(Request r);

public:
    Storage storage;
    nlohmann::json handleRequest(Request r);
};


#endif //SERVER_REQUESTSHANDLER_H
