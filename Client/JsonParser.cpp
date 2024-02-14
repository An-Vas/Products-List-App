//
// Created by user on 21.01.2024.
//

#include "JsonParser.h"
nlohmann::json JsonParser::RequestToJson(Request r){
    nlohmann::json j;
    j["type"] = r.type;
    j["userId"] = r.userId;

    for (auto& product : r.list) {
        nlohmann::json p;
        p["name"] = product.name;
        p["amount"] = product.amount;
        j["products"].push_back(p);
    }
    return j;
}

Request JsonParser::JsonToRequest(nlohmann::json j){

    Request r;

    r.type = j["type"].get<std::string>();
    r.userId = j["userId"].get<std::string>();
    if (j.contains("products"))
    {

        for (auto& product : j["products"].items()) {
            auto pr = product.value();
            ProductListItem p(pr["name"],pr["amount"]);
            r.list.push_back(p);
        }
    }

    return r;
}