#ifndef CLIENT_PRODUCTLISTITEM_H
#define CLIENT_PRODUCTLISTITEM_H


#include <string>

class ProductListItem {
public:
    std::string name;
    int amount;
    ProductListItem(std::string name, int amount);
};


#endif //CLIENT_PRODUCTLISTITEM_H
