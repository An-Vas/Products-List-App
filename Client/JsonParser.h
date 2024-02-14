#ifndef CLIENT_JSONPARSER_H
#define CLIENT_JSONPARSER_H
#include <nlohmann/json.hpp>
#include <iostream>


#include "Request.h"

class JsonParser {
public:
    static nlohmann::json RequestToJson(Request r);
    static Request JsonToRequest(nlohmann::json j);
};


#endif //CLIENT_JSONPARSER_H
