
#include <gtest/gtest.h>
#include "../Server/RequestsHandler.h"
#include "Request.h"

TEST(RequestsHandlerTests, userRequest) {

    RequestsHandler handler;
    Request r;
    r.type = "user";
    r.userId = "id";
    handler.handleRequest(r);

    ASSERT_EQ(handler.storage.data.size(), 1);
    ASSERT_EQ(handler.storage.data.back().userId, "id");

}
TEST(RequestsHandlerTests, productRequest) {

    RequestsHandler handler;
    Request r;
    r.type = "product";
    r.userId = "id";
    r.list.push_back(ProductListItem("apple", 5676));

    handler.handleRequest(r);

    ASSERT_EQ(handler.storage.data.size(), 1);
    ASSERT_EQ(handler.storage.data.back().list.back().amount, 5676);
    ASSERT_EQ(handler.storage.data.back().list.back().name, "apple");

}

TEST(RequestsHandlerTests, clearRequest) {

    RequestsHandler handler;
    Request r;
    r.type = "clear";
    r.userId = "id";
    r.list.push_back(ProductListItem("apple", 5676));
    r.list.push_back(ProductListItem("smth", 123));

    handler.handleRequest(r);

    ASSERT_EQ(handler.storage.data.back().list.size(), 0);

}
