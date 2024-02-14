#include <gtest/gtest.h>
#include "JsonParser.h"


TEST(JsonTests, requestToJson) {
Request r;
r.type = "clear";
r.userId = "user";
nlohmann::json j = JsonParser::RequestToJson(r);

ASSERT_EQ(j["type"], "clear");
ASSERT_EQ(j["userId"], "user");
}


