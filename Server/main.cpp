#include "NewServer.h"

int main() {
    setlocale(LC_ALL, "Russian");
    boost::asio::io_context ioc;
    std::make_shared<NewServer>(ioc, boost::asio::ip::tcp::endpoint{tcp::v4(), 8080})->waitForConnection();
    ioc.run();

    return EXIT_SUCCESS;

}
