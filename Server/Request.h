#ifndef SERVER_REQUEST_H
#define SERVER_REQUEST_H


#include <string>
#include <list>
#include "ProductListItem.h"

class Request {
public:
    std::string type;
    std::string userId;
    std::list<ProductListItem> list;

};

#endif //SERVER_REQUEST_H
