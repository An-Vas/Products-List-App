#ifndef SERVER_PRODUCTLISTITEM_H
#define SERVER_PRODUCTLISTITEM_H

#include <string>

class ProductListItem {
public:
    std::string name;
    int amount;
    ProductListItem(std::string name, int amount);
    ProductListItem();
};


#endif //SERVER_PRODUCTLISTITEM_H
