#ifndef SERVER_USER_H
#define SERVER_USER_H


#include <string>
#include <list>
#include "ProductListItem.h"

class User {
public:
    std::string userId;
    std::list<ProductListItem> list;
    User( std::string userId, std::list<ProductListItem> list);
    User();
};


#endif //SERVER_USER_H
