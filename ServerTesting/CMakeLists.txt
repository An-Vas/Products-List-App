cmake_minimum_required(VERSION 3.26)
project(ServerTesting)

set(CMAKE_CXX_STANDARD 17)

add_executable(ServerTesting main.cpp

        StorageTesting.cpp
        JsonParserTesting.cpp
        RequestHandlerTesting.cpp

        ../Server/Session.cpp
        ../Server/Session.h
        ../Server/Storage.cpp
        ../Server/Storage.h
        ../Server/NewServer.cpp
        ../Server/NewServer.h
        ../Server/JsonParser.cpp
        ../Server/JsonParser.h
        ../Server/ProductListItem.cpp
        ../Server/ProductListItem.h
        ../Server/Request.cpp
        ../Server/Request.h
        ../Server/User.cpp
        ../Server/User.h
        ../Server/RequestsHandler.cpp
        ../Server/RequestsHandler.h

)


add_subdirectory(googletest)
include_directories(googletest/googletest/include)
target_link_libraries(ServerTesting gtest gtest_main)


include_directories(../Server)


if (MINGW)
    target_link_libraries(ServerTesting ws2_32)
    target_link_libraries(ServerTesting wsock32)
endif ()


set(BOOST_ROOT "C:/Programming/CLion/Libraries/boost_1_82_0/boost_1_82_0")
include_directories("C:/Programming/CLion/Libraries/boost_1_82_0/boost_1_82_0")
include_directories(${Boost_INCLUDE_DIRS})
find_package(Boost REQUIRED)
target_include_directories(ServerTesting PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(ServerTesting ${Boost_LIBRARIES})


set(JSON_INCLUDE_DIR "C:/Programming/CLion/Libraries/nlohmannJson/include")
include_directories(${JSON_INCLUDE_DIR})
add_library(json STATIC "C:/Programming/CLion/Libraries/nlohmannJson/include")
target_link_libraries(ServerTesting json)


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O2 -g")
set_target_properties(json PROPERTIES LINKER_LANGUAGE CXX)