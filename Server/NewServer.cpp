#include "NewServer.h"

NewServer::NewServer(net::io_context &ioc, tcp::endpoint endpoint)
        : ioc_(ioc), acceptor_(ioc) {

    beast::error_code ec;

    acceptor_.open(endpoint.protocol(), ec);
    if (checkError(ec, "acceptor_.open")) return;

    acceptor_.set_option(net::socket_base::reuse_address(true), ec);
    if (checkError(ec, "acceptor_.set_option")) return;

    acceptor_.bind(endpoint, ec);
    if (checkError(ec, "acceptor_.bind")) return;

    acceptor_.listen(net::socket_base::max_listen_connections, ec);
    if (checkError(ec, "acceptor_.listen")) return;

}

bool NewServer::checkError(beast::error_code ec, std::string source) {
    if (ec) {
        std::cerr << "Error occured at " << source << ". Error: " << ec.message() << "\n";
        return true;
    }
    return false;
}

void NewServer::waitForConnection() {
    acceptor_.async_accept(
            net::make_strand(ioc_),
            beast::bind_front_handler(
                    &NewServer::startSession,
                    shared_from_this()));
}

void NewServer::startSession(beast::error_code ec, tcp::socket socket)
{
    checkError(ec, "acceptHandler");
    std::make_shared<Session>(std::move(socket), &handler)->run();

    waitForConnection();
}