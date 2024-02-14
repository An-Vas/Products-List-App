#pragma once
#ifndef SERVER_NEWSERVER_H
#define SERVER_NEWSERVER_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <iostream>
#include "Session.h"
#include "RequestsHandler.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;


class NewServer : public std::enable_shared_from_this<NewServer>{
    net::io_context& ioc_;
    tcp::acceptor acceptor_;

public:

    NewServer(net::io_context& ioc, tcp::endpoint endpoint);
    RequestsHandler handler;
    void waitForConnection();


private:
    bool checkError(beast::error_code ec, std::string source);
    void startSession(beast::error_code ec, tcp::socket socket);


};


#endif //SERVER_NEWSERVER_H
