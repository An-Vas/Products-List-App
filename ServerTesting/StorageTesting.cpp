#include <gtest/gtest.h>
#include "../Server/Storage.h"

TEST(ServerTests, addingUser) {
    Storage storage;

    User user("newuser", std::list<ProductListItem>());
    storage.addUserInStorage("newuser");


    ASSERT_EQ(storage.data.size(), 1);
    ASSERT_EQ(storage.data.back().userId, user.userId);
}

TEST(ServerTests, addingProductToUser) {
    Storage storage;

    User user("newuser", std::list<ProductListItem>());
    storage.addUserInStorage("newuser");
    storage.addUProductToUser("newuser", ProductListItem("apple", 45));

    ASSERT_EQ(storage.getAllProducts("newuser").size(), 1);
}

TEST(ServerTests, clearList) {
    Storage storage;

    User user("newuser", std::list<ProductListItem>());
    storage.addUserInStorage("newuser");
    storage.addUProductToUser("newuser", ProductListItem("apple", 45));
    storage.addUProductToUser("newuser", ProductListItem("cookies", 4005));
    storage.clearUserProductList("newuser");
    ASSERT_EQ(storage.getAllProducts("newuser").size(), 0);

}


