cmake_minimum_required(VERSION 3.26)
project(ClientTesting)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Programming/CLion/Libraries/Qt/Qt5.12.12/5.12.12/mingw73_64/bin")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        WebSockets
        Test
        REQUIRED)

add_executable(ClientTesting main.cpp
        MainWindowTesting.cpp


        ../Client/WindowSetup.cpp
        ../Client/WindowSetup.h
        ../Client/UserActivityHandler.cpp
        ../Client/UserActivityHandler.h
        ../Client/ResponseHandler.cpp
        ../Client/ResponseHandler.h
        ../Client/ClientQt5.cpp
        ../Client/ClientQt5.h
        ../Client/Request.cpp
        ../Client/Request.h
        ../Client/ProductListItem.cpp
        ../Client/ProductListItem.h
        ../Client/JsonParser.cpp
        ../Client/JsonParser.h
        MainWindowTesting.cpp
        MainWindowTesting.h


)


target_link_libraries(ClientTesting
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::WebSockets
        Qt5::Test
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets Test)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()

include_directories(../Client)


set(BOOST_ROOT "C:/Programming/CLion/Libraries/boost_1_82_0/boost_1_82_0")
include_directories("C:/Programming/CLion/Libraries/boost_1_82_0/boost_1_82_0")
include_directories(${Boost_INCLUDE_DIRS})
find_package(Boost REQUIRED)
target_include_directories(ClientTesting PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(ClientTesting ${Boost_LIBRARIES})

if (MINGW)
    target_link_libraries(ClientTesting ws2_32)
    target_link_libraries(ClientTesting wsock32)
endif ()

set(JSON_INCLUDE_DIR "C:/Programming/CLion/Libraries/nlohmannJson/include")
include_directories(${JSON_INCLUDE_DIR})
add_library(json STATIC "C:/Programming/CLion/Libraries/nlohmannJson/include")
target_link_libraries(ClientTesting json)


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O2 -g")