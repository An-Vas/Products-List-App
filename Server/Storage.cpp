#include "Storage.h"

bool Storage::isUserInStorage(std::string userId){
;
    if (data.empty()) return false;
    std::list<User>::iterator it;
    for (it = data.begin(); it != data.end(); ++it){
        if (it->userId == userId)
            return true;
    }
    return false;
}

void Storage::addUserInStorage(std::string userId){
    std::list<ProductListItem>  products;
    User newUser (userId, products);
    data.push_back(newUser);
}

void Storage::addUProductToUser(std::string userId, ProductListItem product){
    if (data.empty()) return;
    std::list<User>::iterator it;
    for (it = data.begin(); it != data.end(); ++it){
        if (it->userId == userId){
            it->list.push_back(product);
            return;
        }
    }
}

void Storage::clearUserProductList(std::string userId){
    if (data.empty()) return;
    std::list<User>::iterator it;
    for (it = data.begin(); it != data.end(); ++it){
        if (it->userId == userId){
            it->list.clear();
            return;
        }
    }
}

std::list<ProductListItem> Storage::getAllProducts(std::string userId){
    std::list<User>::iterator it;
    for (it = data.begin(); it != data.end(); ++it){
        if (it->userId == userId){
            return it->list;
        }
    }

}


