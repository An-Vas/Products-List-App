
#ifndef SERVER_STORAGE_H
#define SERVER_STORAGE_H

#include <iostream>
#include "User.h"

class Storage {

public:
    std::list<User> data;

    bool isUserInStorage(std::string userId);
    void addUserInStorage(std::string userId);
    void addUProductToUser(std::string userId, ProductListItem product);
    void clearUserProductList(std::string userId);
    const std::list<ProductListItem>& getAllProducts2(std::string userId);
    std::list<ProductListItem> getAllProducts(std::string userId);

};


#endif //SERVER_STORAGE_H
